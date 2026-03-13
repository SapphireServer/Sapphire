#pragma once

#include <cstdint>

#include <cassert>

#include <glm/glm.hpp>

#include <utility>
#include <vector>
#include <memory>
#include "glcommon.h"

namespace Engine::Rendering
{
  struct VertexBuffer;
  struct IndexBuffer;
  struct ShaderProgram;
  struct Mesh;
  struct Texture;
  struct TextureUnit;
  struct TextureSampler;
  struct MeshTexture;
  struct Ssbo;

  class VertexElement;
  class VertexDeclaration;
  class PixelBuffer;
  class Shader;

  using VertexBufferPtr = std::shared_ptr< VertexBuffer >;
  using IndexBufferPtr = std::shared_ptr< IndexBuffer >;
  using ShaderProgramPtr = std::shared_ptr< ShaderProgram >;
  using MeshPtr = std::shared_ptr< Mesh >;
  using TexturePtr = std::shared_ptr< Texture >;
  using TextureUnitPtr = std::shared_ptr< TextureUnit >;
  using TextureSamplerPtr = std::shared_ptr< TextureSampler >;
  using MeshTexturePtr = std::shared_ptr< MeshTexture >;
  using VertexElementPtr = std::shared_ptr< VertexElement >;
  using VertexDeclarationPtr = std::shared_ptr< VertexDeclaration >;
  using PixelBufferPtr = std::shared_ptr< PixelBuffer >;
  using ShaderPtr = std::shared_ptr< Shader >;
  using SsboPtr = std::shared_ptr< Ssbo >;
}
