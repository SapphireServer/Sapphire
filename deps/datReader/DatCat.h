#pragma once

#include <filesystem>
#include <memory>
#include <vector>

namespace xiv::dat
{

  class Index;

  class Dat;

  class File;

  // A category represents an .index and its associated .datX
  class Cat
  {
  public:
    // basePath: Path to the folder containingthe datfiles
    // catNum: The number of the category
    // name: The name of the category, empty if not known
    Cat( const std::filesystem::path& basePath, uint32_t catNum, const std::string& name );

    // basePath: Path to the folder containingthe datfiles
    // catNum: The number of the category
    // name: The name of the category, empty if not known
    // exNum: The number of the expansion to load from
    // chunk: The chunk to load from
    Cat( const std::filesystem::path& basePath, uint32_t catNum, const std::string& name, uint32_t exNum,
         uint32_t chunk );

    ~Cat();

    // Returns .index of the category
    const Index& getIndex() const;

    // Retrieve a file from the category given its hashes
    std::unique_ptr< File > getFile( uint32_t dir_hash, uint32_t filename_hash ) const;


    bool doesFileExist( uint32_t dir_hash, uint32_t filename_hash ) const;

    bool doesDirExist( uint32_t dir_hash ) const;


    // Returns thename of the category
    const std::string& getName() const;

    // Returns the number of the category
    uint32_t getCatNum() const;

  protected:
    const std::string m_name;
    const uint32_t m_catNum;
    const uint32_t m_chunk;

    // The .index
    std::unique_ptr< Index > m_index;

    // The .datXs such as dat nb X => m_dats[X]
    std::vector< std::unique_ptr< Dat > > m_dats;
  };
    
}

