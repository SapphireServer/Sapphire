#pragma once
#include <string>

namespace Engine::Resources
{
  class Resource
  {
  protected:
    std::string m_path;
    std::string m_name;

  public:
    explicit Resource( const std::string& path ) :
      m_path( path )
    {
    }

    virtual ~Resource() = default;

    const std::string& getName()
    {
      return m_name;
    }

    void setName( const std::string& name )
    {
      m_name = name;
    }
  };

}
