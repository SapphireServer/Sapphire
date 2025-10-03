#ifndef IMGUI_DEFINE_MATH_OPERATORS
#define IMGUI_DEFINE_MATH_OPERATORS
#endif // IMGUI_DEFINE_MATH_OPERATORS

#include "ExdView.h"

#include <iostream>
#include <cctype>
#include <set>
#include <string>
#include <Exd/ExdData.h>
#include <Exd/Structs.h>

#include "ServerState.h"

#include "Engine/GfxApi.h"
#include "Engine/ResourceManager.h"
#include "Engine/ShaderResource.h"


#include "imgui.h"
#include <random>
#include <vector>

#include "Engine/Input.h"
#include "Engine/Service.h"
#include "Engine/Logger.h"

#include <math.h>
#include <vector>

#include <algorithm>
#include <unordered_set>
#include <glm/gtx/matrix_decompose.hpp>

#include "Application.h"

#include "Service.h"
#include <algorithm>
#include <cctype>

#include "Common.h"
#include "PreparedResultSet.h"

#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include <GL/glew.h>

#include "imgui_internal.h"
#include "Util/Paths.h"


ExdView::ExdView()
{
  memset( m_filterText, 0, sizeof( m_filterText ) );
}

ExdView::~ExdView()
{
}

void ExdView::init()
{
  auto& gameData = Engine::Service< xiv::dat::GameData >::ref();
  auto exdData = xiv::exd::ExdData( gameData );

  for( auto& cat : exdData.get_cat_names() )
  {
    m_exdFiles.push_back( cat );
  }
}

void ExdView::show()
{
  showExdSelector();

  if( !m_selectedExdFile.empty() )
  {
    showExdDetails();
  }
}

bool ExdView::passesFilter( const std::string& path ) const
{
  if( strlen( m_filterText ) == 0 )
    return true; // No filter, show everything

  std::string filterStr = m_filterText;
  std::string pathStr = path;

  // Convert both to lowercase for case-insensitive search
  std::transform( filterStr.begin(), filterStr.end(), filterStr.begin(), ::tolower );
  std::transform( pathStr.begin(), pathStr.end(), pathStr.begin(), ::tolower );

  return pathStr.find( filterStr ) != std::string::npos;
}


void ExdView::showExdSelector()
{
  if( ImGui::Begin( "EXD File Selector" ) )
  {
    // Add filter input box at the top
    ImGui::Text( "Filter:" );
    ImGui::SameLine();
    ImGui::SetNextItemWidth( -1.0f ); // Take remaining width
    if( ImGui::InputText( "##filter", m_filterText, sizeof( m_filterText ) ) )
    {
      // Filter text changed - no need to do anything special here
    }

    // Add clear button
    if( strlen( m_filterText ) > 0 )
    {
      ImGui::SameLine();
      if( ImGui::Button( "Clear" ) )
      {
        memset( m_filterText, 0, sizeof( m_filterText ) );
      }
    }

    ImGui::Separator();

    // Build a tree structure from file paths
    struct TreeNode
    {
      std::string name;
      std::map< std::string, std::unique_ptr< TreeNode > > children;
      bool isFile = false;
      bool hasFiles = false; // Track if this node represents actual files
      std::string fullPath;
    };

    TreeNode root;

    // Build the tree structure
    for( const auto& filePath : m_exdFiles )
    {
      if( !passesFilter( filePath ) )
        continue; // Skip files that don't match the filter

      TreeNode *current = &root;
      std::string path = filePath;

      // Split path by '/' and build tree
      size_t pos = 0;
      while( pos < path.length() )
      {
        size_t nextPos = path.find( '/', pos );
        std::string segment;

        if( nextPos == std::string::npos )
        {
          // Last segment (filename)
          segment = path.substr( pos );
          if( current->children.find( segment ) == current->children.end() )
          {
            current->children[ segment ] = std::make_unique< TreeNode >();
            current->children[ segment ]->name = segment;
            current->children[ segment ]->isFile = true;
            current->children[ segment ]->hasFiles = true;
            current->children[ segment ]->fullPath = filePath;
          }
          else if( !current->children[ segment ]->hasFiles )
          {
            // This was a directory, but now we found it's also a file
            current->children[ segment ]->hasFiles = true;
            current->children[ segment ]->fullPath = filePath;
          }
          break;
        }
        else
        {
          // Directory segment
          segment = path.substr( pos, nextPos - pos );
          if( current->children.find( segment ) == current->children.end() )
          {
            current->children[ segment ] = std::make_unique< TreeNode >();
            current->children[ segment ]->name = segment;
            current->children[ segment ]->isFile = false;
            current->children[ segment ]->hasFiles = false;
          }
          current = current->children[ segment ].get();
          pos = nextPos + 1;
        }
      }
    }

    // Recursive function to render tree
    std::function< void( TreeNode * ) > renderTree;
    renderTree = [&]( TreeNode *node )
    {
      // Collect all children (both directories and files) for sorting
      std::vector< std::pair< std::string, TreeNode * > > allChildren;

      for( const auto& [ name, child ] : node->children )
      {
        allChildren.emplace_back( name, child.get() );
      }

      // Sort all children alphabetically (case-insensitive)
      std::sort( allChildren.begin(), allChildren.end(),
                 []( const std::pair< std::string, TreeNode * >& a,
                     const std::pair< std::string, TreeNode * >& b )
                 {
                   std::string nameA = a.first;
                   std::string nameB = b.first;
                   std::transform( nameA.begin(), nameA.end(), nameA.begin(), ::tolower );
                   std::transform( nameB.begin(), nameB.end(), nameB.begin(), ::tolower );
                   return nameA < nameB;
                 } );

      // Render all children in sorted order
      for( const auto& [ name, child ] : allChildren )
      {
        bool hasSubdirectories = !child->children.empty();

        if( child->hasFiles && !hasSubdirectories )
        {
          // Pure file - render as selectable
          if( ImGui::Selectable( child->name.c_str() ) )
          {
            onSelectionChanged( child->fullPath );
          }
        }
        else if( hasSubdirectories && !child->hasFiles )
        {
          // Pure directory - render as tree node
          bool nodeOpen = ImGui::TreeNode( child->name.c_str() );
          if( nodeOpen )
          {
            renderTree( child );
            ImGui::TreePop();
          }
        }
        else if( hasSubdirectories && child->hasFiles )
        {
          // Both file and directory - render directory with file option
          bool nodeOpen = ImGui::TreeNode( child->name.c_str() );
          if( nodeOpen )
          {
            // First show the file option
            std::string fileLabel = child->name + " (file)";
            if( ImGui::Selectable( fileLabel.c_str() ) )
            {
              onSelectionChanged( child->fullPath );
            }
            // Then show subdirectories
            renderTree( child );
            ImGui::TreePop();
          }
        }
      }
    };

    // Render the tree starting from root
    renderTree( &root );
  }
  ImGui::End();
}

void ExdView::showExdDetails()
{
  if( !ImGui::Begin( "Exd Details" ) )
  {
    ImGui::End();
    return;
  }

  if( m_selectedExdFile.empty() )
  {
    ImGui::Text( "No EXD file selected" );
    ImGui::End();
    return;
  }

  if( !m_cachedData.isValid )
  {
    ImGui::Text( "Failed to load EXD file: %s", m_selectedExdFile.c_str() );
    if( ImGui::Button( "Retry" ) )
    {
      loadExdData();
    }
    ImGui::End();
    return;
  }

  if( m_cachedData.rows.empty() )
  {
    ImGui::Text( "No data found in selected EXD file" );
    ImGui::End();
    return;
  }

  ImGui::Text( "File: %s", m_selectedExdFile.c_str() );
  ImGui::Text( "Rows: %zu, Columns: %d", m_cachedData.rows.size(), m_cachedData.columnCount - 1 );
  ImGui::Separator();
  // Display configuration
  static int maxRowsToDisplay = 5000;
  ImGui::SetNextItemWidth( 200 );
  if( ImGui::SliderInt( "Max Rows", &maxRowsToDisplay, 10, 20000 ) )
  {
    // User changed the display limit
  }

  // Create table with cached data
  const char *tableId = "ExdDataTable";
  if( ImGui::BeginTable( tableId, m_cachedData.columnCount,
                         ImGuiTableFlags_Borders | ImGuiTableFlags_RowBg |
                         ImGuiTableFlags_ScrollX | ImGuiTableFlags_ScrollY |
                         ImGuiTableFlags_Resizable | ImGuiTableFlags_SizingFixedFit ) )
  {
    // Setup columns
    ImGui::TableSetupColumn( "Row ID", ImGuiTableColumnFlags_WidthFixed, 80.0f );

    for( int col = 0; col < m_cachedData.columnCount - 1; ++col )
    {
      std::string colName = "Col " + std::to_string( col );

      // Calculate a reasonable minimum width based on content
      float minWidth = 60.0f; // Base minimum width

      // Sample some rows to estimate content width
      float maxContentWidth = 0.0f;
      int sampleCount = 0;
      const int maxSamples = 50; // Limit sampling for performance

      for( const auto& [rowId, fields] : m_cachedData.rows )
      {
        if( sampleCount >= maxSamples ) break;

        if( col < static_cast<int>(fields.size()) )
        {
          const auto& field = fields[col];

          // Convert variant to string for width calculation
          std::string cellValue;
          std::visit( [&cellValue]( const auto& value )
          {
            using T = std::decay_t< decltype(value) >;
            if constexpr( std::is_same_v< T, std::string > )
            {
              cellValue = value.empty() ? " " : value;
            }
            else if constexpr( std::is_same_v< T, bool > )
            {
              cellValue = value ? "true" : "false";
            }
            else if constexpr( std::is_floating_point_v< T > )
            {
              char buffer[ 32 ];
              snprintf( buffer, sizeof( buffer ), "%.6g", static_cast< double >( value ) );
              cellValue = buffer;
            }
            else if constexpr( std::is_integral_v< T > )
            {
              cellValue = std::to_string( value );
            }
            else
            {
              cellValue = "Unknown";
            }
          }, field );

          // Estimate text width (rough approximation: 7 pixels per character)
          float textWidth = cellValue.length() * 7.0f + 16.0f; // +16 for padding
          maxContentWidth = std::max( maxContentWidth, textWidth );
        }
        sampleCount++;
      }

      // Also consider header width
      float headerWidth = colName.length() * 7.0f + 16.0f;
      maxContentWidth = std::max( maxContentWidth, headerWidth );

      // Set a reasonable width with limits
      float columnWidth = std::max( minWidth, std::min( maxContentWidth, 300.0f ) );

      ImGui::TableSetupColumn( colName.c_str(), ImGuiTableColumnFlags_WidthFixed, columnWidth );
    }

    ImGui::TableHeadersRow();



    ImGui::SameLine();
    ImGui::Text( "(Total: %zu)", m_cachedData.rows.size() );

    // Populate rows from cached data - very fast!
    size_t rowsDisplayed = 0;
    for( const auto& [ rowId, fields ] : m_cachedData.rows )
    {
      if( rowsDisplayed >= static_cast< size_t >( maxRowsToDisplay ) )
      {
        ImGui::TableNextRow();
        ImGui::TableSetColumnIndex( 0 );
        ImGui::Text( "... (%zu more rows)", m_cachedData.rows.size() - maxRowsToDisplay );
        break;
      }

      ImGui::TableNextRow();

      // Row ID column
      ImGui::TableSetColumnIndex( 0 );
      ImGui::Text( "%u", rowId );

      // Data columns
      const size_t maxCols = std::min( fields.size(), static_cast< size_t >( m_cachedData.columnCount - 1 ) );
      for( size_t col = 0; col < maxCols; ++col )
      {
        ImGui::TableSetColumnIndex( static_cast< int >( col + 1 ) );

        const auto& field = fields[ col ];

        // Convert variant to string for display
        std::string cellValue;
        try
        {
          std::visit( [&cellValue]( const auto& value )
          {
            using T = std::decay_t< decltype(value) >;
            if constexpr( std::is_same_v< T, std::string > )
            {
              cellValue = value.empty() ? " " : value;
            }
            else if constexpr( std::is_same_v< T, bool > )
            {
              cellValue = value ? "true" : "false";
            }
            else if constexpr( std::is_floating_point_v< T > )
            {
              char buffer[ 32 ];
              snprintf( buffer, sizeof( buffer ), "%.6g", static_cast< double >( value ) );
              cellValue = buffer;
            }
            else if constexpr( std::is_integral_v< T > )
            {
              cellValue = std::to_string( value );
            }
            else
            {
              cellValue = "Unknown";
            }
          }, field );
        } catch( ... )
        {
          cellValue = "Error";
        }

        // Limit cell text length to prevent UI issues
        if( cellValue.length() > 100 )
        {
          cellValue = cellValue.substr( 0, 97 ) + "...";
        }

        ImGui::TextUnformatted( cellValue.c_str() );
      }

      rowsDisplayed++;
    }

    ImGui::EndTable();
  }

  ImGui::End();
}


void ExdView::onSelectionChanged( const std::string& selectedPath )
{
  m_selectedExdFile = selectedPath;
  std::cout << "Selected EXD file: " << selectedPath << std::endl;

  // Load the data immediately when selection changes
  loadExdData();
}

void ExdView::loadExdData()
{
  m_cachedData.isValid = false;
  m_cachedData.rows.clear();
  m_cachedData.columnCount = 0;
  m_cachedData.fileName = m_selectedExdFile;

  if( m_selectedExdFile.empty() )
    return;

  auto& exdD = Engine::Service< Sapphire::Data::ExdData >::ref();

  try
  {
    std::cout << "Loading EXD data for: " << m_selectedExdFile << std::endl;

    auto& cat = exdD.getExdData()->get_category( m_selectedExdFile );

    // Choose language: prefer en if available, otherwise none
    xiv::exd::Language lang = xiv::exd::Language::none;
    if( cat.get_header().get_languages().size() > 1 )
      lang = xiv::exd::Language::en;

    // Expected columns from EXH (true member count)
    const size_t expectedCols =
      static_cast<size_t>(cat.get_header().get_members().size());

    auto& exd = cat.get_data_ln( lang );
    auto& rows = exd.get_rows();

    if( rows.empty() )
    {
      std::cout << "No rows found in EXD file" << std::endl;
      return;
    }

    // Copy rows and normalize columns
    m_cachedData.rows = rows;

    if (expectedCols > 0)
    {
      for (auto& kv : m_cachedData.rows)
      {
        auto& vec = kv.second;
        if (vec.size() > expectedCols)
        {
          // If data was appended per chunk, size will be a multiple of expectedCols.
          // Keep only the first expectedCols (drop duplicates).
          if (vec.size() % expectedCols == 0)
          {
            vec.resize(expectedCols);
          }
          else
          {
            // Fallback: clamp to expectedCols (or to current size if smaller).
            vec.resize(std::min(vec.size(), expectedCols));
          }
        }
        else if (vec.size() < expectedCols)
        {
          // Optional: pad to expectedCols if you prefer consistent widths.
          // Not strictly needed for display; we leave as-is to avoid introducing fake data.
        }
      }

      m_cachedData.columnCount = static_cast<int>(expectedCols) + 1; // +1 for Row ID
    }
    else
    {
      // If we cannot read members from header, fall back to min size among rows.
      size_t minCols = std::numeric_limits<size_t>::max();
      for (const auto& kv : m_cachedData.rows)
        minCols = std::min(minCols, kv.second.size());

      if (minCols == std::numeric_limits<size_t>::max())
        minCols = 0;

      for (auto& kv : m_cachedData.rows)
      {
        auto& vec = kv.second;
        if (vec.size() > minCols)
          vec.resize(minCols);
      }

      m_cachedData.columnCount = static_cast<int>(minCols) + 1;
    }

    m_cachedData.isValid = true;

    std::cout << "Successfully loaded " << rows.size() << " rows with "
              << ( m_cachedData.columnCount - 1 ) << " columns (from EXH)" << std::endl;
  }
  catch( const std::exception& e )
  {
    std::cout << "Error loading EXD data: " << e.what() << std::endl;
    m_cachedData.isValid = false;
  }
  catch( ... )
  {
    std::cout << "Unknown error loading EXD data" << std::endl;
    m_cachedData.isValid = false;
  }
}

