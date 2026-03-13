#pragma once
#include <memory>
#include <unordered_map>
#include <string>
#include <stdexcept>

namespace Engine::Resources
{
  class Resource;

  class ResourceManager
  {
  public:

    inline static const std::string assetPath = "assets";
    inline static const std::string shaderPath = "shader";


    template< typename T >
    std::shared_ptr< T > get( const std::string& path )
    {
      static_assert( std::is_base_of< Resource, T >::value, "T must inherit from Resource" );

      std::shared_ptr< T > returnValue;
      auto res = m_resources.find( path );
      if( res == m_resources.end() )
      {
        // assuming constructor loads resource
        m_resources[ path ] = std::make_shared< T >( path );
      }

      auto return_value = std::dynamic_pointer_cast< T >( m_resources[ path ] );
      if( !return_value )
      {
        throw std::runtime_error( std::string( "Resource '" ) + path + "' is already loaded as another type" );
      }
      return return_value;
    }

    template< typename T >
    std::shared_ptr< T > retrieve( const std::string& path )
    {
      static_assert( std::is_base_of< Resource, T >::value, "T must inherit from Resource" );

      std::shared_ptr< T > returnValue;
      auto res = m_resources.find( path );
      if( res == m_resources.end() )
      {
        return nullptr;
      }

      auto return_value = std::dynamic_pointer_cast< T >( m_resources[ path ] );
      if( !return_value )
      {
        throw std::runtime_error( std::string( "Resource '" ) + path + "' is already loaded as another type" );
      }
      return return_value;
    }

    template< typename T >
    void load( const std::string& path )
    {
      get< T >( path );
    }

  private:
    std::unordered_map< std::string, std::shared_ptr< Resource > > m_resources;
  };

}