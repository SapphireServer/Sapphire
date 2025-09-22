#include <string>
#include "Resource.h"
#include "ShaderResource.h"
#include "nlohmann/json.hpp"
#include "ResourceManager.h"
#include <fstream>
#include "GfxApi.h"

#include "Logger.h"

Engine::Resources::ShaderResource::ShaderResource( const std::string& path ) :
  Resource( path )
{
  load( path );
}

Engine::Resources::ShaderResource::~ShaderResource()
{
  unload();
}

void Engine::Resources::ShaderResource::load( const std::string& path )
{
  m_path = path;
  const std::string shaderPath = Engine::Resources::ResourceManager::assetPath + "/" + Engine::Resources::ResourceManager::shaderPath + "/";

  std::ifstream t( shaderPath + path + ".json" );
  auto json = nlohmann::json::parse( t );

  std::string fragment;
  std::string vertex;
  std::string geo;
  std::string compute;
  setName( json[ "name" ] );

  Engine::Logger::debug( "Loading program: {}", path );

  fragment = json.value( "fragmentShader", "" );
  vertex = json.value( "vertexShader", "" );
  geo = json.value( "geometryShader", "" );
  compute = json.value( "computeShader", "" );

  m_pProgram = std::make_shared< Engine::Rendering::ShaderProgram >();

  if( !fragment.empty() )
  {
    Engine::Logger::debug( "Loading shader: frag: {}", fragment );
    m_pFragmentShader = std::make_shared< Engine::Rendering::Shader >( Engine::Rendering::ShaderType::PixelShader, shaderPath + fragment );
    m_pProgram->attach( *m_pFragmentShader );
  }

  if( !vertex.empty() )
  {
    Engine::Logger::debug( "Loading shader: vertex: {}", vertex );
    m_pVertexShader = std::make_shared< Engine::Rendering::Shader >( Engine::Rendering::ShaderType::VertexShader, shaderPath + vertex );
    m_pProgram->attach( *m_pVertexShader );
  }

  if( !geo.empty() )
  {
    Engine::Logger::debug( "Loading shader: geo: {}", geo );
    m_pGeometryShader = std::make_shared< Engine::Rendering::Shader >( Engine::Rendering::ShaderType::GeometryShader, shaderPath + geo );
    m_pProgram->attach( *m_pGeometryShader );
  }

  if( !compute.empty() )
  {
    Engine::Logger::debug( "Loading shader: compute: {}", compute );
    m_pComputeShader = std::make_shared< Engine::Rendering::Shader >( Engine::Rendering::ShaderType::ComputeShader, shaderPath + compute );
    m_pProgram->attach( *m_pComputeShader );
  }

}

Engine::Rendering::ShaderProgramPtr Engine::Resources::ShaderResource::getShaderProgram()
{
  return m_pProgram;
}

Engine::Rendering::ShaderProgram& Engine::Resources::ShaderResource::getShaderProgramRef()
{
  return *m_pProgram;
}

void Engine::Resources::ShaderResource::unload()
{
  m_pProgram.reset();
}

void Engine::Resources::ShaderResource::reload()
{
  unload();
  load( m_path );
}
