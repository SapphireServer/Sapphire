#pragma once
#include <string>
#include <memory>
#include "Engine/Resource.h"
#include "Engine/GfxApiCommon.h"


namespace Engine::Resources
{

  class ShaderResource : public Engine::Resources::Resource
  {
  public:
    Engine::Rendering::ShaderProgramPtr m_pProgram;
    Engine::Rendering::ShaderPtr m_pVertexShader;
    Engine::Rendering::ShaderPtr m_pGeometryShader;
    Engine::Rendering::ShaderPtr m_pFragmentShader;
    Engine::Rendering::ShaderPtr m_pComputeShader;

    explicit ShaderResource( const std::string& path );
    virtual ~ShaderResource();

    Engine::Rendering::ShaderProgramPtr getShaderProgram();
    Engine::Rendering::ShaderProgram& getShaderProgramRef();

    void reload();

  protected:
    void load( const std::string& path );

    void unload();



  private:
    std::string m_path;
  };

}