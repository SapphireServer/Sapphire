#include "GfxApi.h"

#include <limits>
#include <map>
#include <assert.h>

#include <sstream>
#include <iostream>
#include <fstream>

#include <algorithm>
#include <set>

#include <glm/gtc/type_ptr.hpp>
#include "Engine/glcommon.h"
#include "Service.h"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

using namespace Engine::Rendering;

int Engine::Rendering::checkOglError( const char* func )
{

  GLenum glErr;
  int retCode = 0;
  glErr = glGetError();
  if( glErr != GL_NO_ERROR )
  {
    std::string msg = "glError in " + std::string( func ) + ": " +
                      std::string( reinterpret_cast< const char* >( glewGetErrorString( glErr ) ) );
    std::cout << msg << std::endl;
    //throw std::runtime_error( msg );
    retCode = 1;
  }
  return retCode;
}


#define checkOpenGLError() checkOglError(__FUNCTION__)

GLenum Engine::Rendering::toGL( BarrierBit bit )
{
  switch( bit )
  {
    case BarrierBit::AttribArray:
      return GL_VERTEX_ATTRIB_ARRAY_BARRIER_BIT;
    case BarrierBit::ElementArray:
      return GL_ELEMENT_ARRAY_BARRIER_BIT;
    case BarrierBit::Uniform:
      return GL_UNIFORM_BARRIER_BIT;
    case BarrierBit::TextureFetch:
      return GL_TEXTURE_FETCH_BARRIER_BIT;
    case BarrierBit::ShaderImage:
      return GL_SHADER_IMAGE_ACCESS_BARRIER_BIT;
    case BarrierBit::Command:
      return GL_COMMAND_BARRIER_BIT;
    case BarrierBit::PixelBuffer:
      return GL_PIXEL_BUFFER_BARRIER_BIT;
    case BarrierBit::TextureUpdate:
      return GL_TEXTURE_UPDATE_BARRIER_BIT;
    case BarrierBit::BufferUpdate:
      return GL_BUFFER_UPDATE_BARRIER_BIT;
    case BarrierBit::Framebuffer:
      return GL_FRAMEBUFFER_BARRIER_BIT;
    case BarrierBit::TransformFeedback:
      return GL_TRANSFORM_FEEDBACK_BARRIER_BIT;
    case BarrierBit::AtomicCounter:
      return GL_ATOMIC_COUNTER_BARRIER_BIT;
  }
  return GL_NONE;
}

GLenum Engine::Rendering::toGL( VertexDataType type )
{
  switch( type )
  {
    case ( VertexDataType::BYTE ) :
      return GL_BYTE;
    case ( VertexDataType::UNSIGNED_BYTE ) :
      return GL_UNSIGNED_BYTE;
    case ( VertexDataType::UNSIGNED_SHORT ) :
      return GL_UNSIGNED_SHORT;
    case ( VertexDataType::SHORT ) :
      return GL_SHORT;
    case ( VertexDataType::INT ) :
      return GL_INT;
    case ( VertexDataType::FLOAT ) :
      return GL_FLOAT;
    case ( VertexDataType::DOUBLE ) :
      return GL_DOUBLE;
    default:
      assert( false );
      return GL_NONE;
  }
}

GLenum Engine::Rendering::toGL( Access access )
{
  switch( access )
  {
    case ( Access::ReadOnly ) :
      return GL_READ_ONLY;
    case ( Access::WriteOnly ) :
      return GL_WRITE_ONLY;
    case ( Access::ReadWrite ) :
      return GL_READ_WRITE;
    default:
      assert( false );
      return GL_NONE;
  }
}

GLenum Engine::Rendering::toGL( Usage usage )
{
  switch( usage )
  {
    case ( Usage::STREAM_DRAW ) :
      return GL_STREAM_DRAW;
    case ( Usage::STREAM_READ ) :
      return GL_STREAM_READ;
    case ( Usage::STREAM_COPY ) :
      return GL_STREAM_COPY;

    case ( Usage::STATIC_DRAW ) :
      return GL_STATIC_DRAW;
    case ( Usage::STATIC_READ ) :
      return GL_STATIC_READ;
    case ( Usage::STATIC_COPY ) :
      return GL_STATIC_COPY;

    case ( Usage::DYNAMIC_DRAW ) :
      return GL_DYNAMIC_DRAW;
    case ( Usage::DYNAMIC_READ ) :
      return GL_DYNAMIC_READ;
    case ( Usage::DYNAMIC_COPY ) :
      return GL_DYNAMIC_COPY;

    default:
      assert( false );
      return GL_NONE;
  }
}


GLenum Engine::Rendering::toGL( TextureElementType elementtype )
{
  switch( elementtype )
  {
    case ( TextureElementType::UNSIGNED_BYTE ) :
      return GL_UNSIGNED_BYTE;
    case ( TextureElementType::BYTE ) :
      return GL_BYTE;
    case ( TextureElementType::UNSIGNED_SHORT ) :
      return GL_UNSIGNED_SHORT;
    case ( TextureElementType::SHORT ) :
      return GL_SHORT;
    case ( TextureElementType::UNSIGNED_INT ) :
      return GL_UNSIGNED_INT;
    case ( TextureElementType::INT ) :
      return GL_INT;
    case ( TextureElementType::FLOAT ) :
      return GL_FLOAT;
    case ( TextureElementType::UNSIGNED_BYTE_3_3_2 ) :
      return GL_UNSIGNED_BYTE_3_3_2;
    case ( TextureElementType::UNSIGNED_BYTE_2_3_3_REV ) :
      return GL_UNSIGNED_BYTE_2_3_3_REV;
    case ( TextureElementType::UNSIGNED_SHORT_5_6_5 ) :
      return GL_UNSIGNED_SHORT_5_6_5;
    case ( TextureElementType::UNSIGNED_SHORT_5_6_5_REV ) :
      return GL_UNSIGNED_SHORT_5_6_5_REV;
    case ( TextureElementType::UNSIGNED_SHORT_4_4_4_4 ) :
      return GL_UNSIGNED_SHORT_4_4_4_4;
    case ( TextureElementType::UNSIGNED_SHORT_4_4_4_4_REV ) :
      return GL_UNSIGNED_SHORT_4_4_4_4_REV;
    case ( TextureElementType::UNSIGNED_SHORT_5_5_5_1 ) :
      return GL_UNSIGNED_SHORT_5_5_5_1;
    case ( TextureElementType::UNSIGNED_SHORT_1_5_5_5_REV ) :
      return GL_UNSIGNED_SHORT_1_5_5_5_REV;
    case ( TextureElementType::UNSIGNED_INT_8_8_8_8 ) :
      return GL_UNSIGNED_INT_8_8_8_8;
    case ( TextureElementType::UNSIGNED_INT_8_8_8_8_REV ) :
      return GL_UNSIGNED_INT_8_8_8_8_REV;
    case ( TextureElementType::UNSIGNED_INT_10_10_10_2 ) :
      return GL_UNSIGNED_INT_10_10_10_2;
    case ( TextureElementType::UNSIGNED_INT_2_10_10_10_REV ) :
      return GL_UNSIGNED_INT_2_10_10_10_REV;

    default:
      assert( false );
      return GL_NONE;
  }
}

int toGLBytes( TextureElementType elementtype )
{

  switch( elementtype )
  {
    case ( TextureElementType::UNSIGNED_BYTE ) :
    case ( TextureElementType::BYTE ) :
    case ( TextureElementType::UNSIGNED_BYTE_3_3_2 ) :
    case ( TextureElementType::UNSIGNED_BYTE_2_3_3_REV ) :
      return 1;
    case ( TextureElementType::UNSIGNED_SHORT ) :
    case ( TextureElementType::SHORT ) :
    case ( TextureElementType::UNSIGNED_SHORT_5_6_5 ) :
    case ( TextureElementType::UNSIGNED_SHORT_5_6_5_REV ) :
    case ( TextureElementType::UNSIGNED_SHORT_4_4_4_4 ) :
    case ( TextureElementType::UNSIGNED_SHORT_4_4_4_4_REV ) :
    case ( TextureElementType::UNSIGNED_SHORT_5_5_5_1 ) :
    case ( TextureElementType::UNSIGNED_SHORT_1_5_5_5_REV ) :
      return 2;
    case ( TextureElementType::UNSIGNED_INT ) :
    case ( TextureElementType::INT ) :
    case ( TextureElementType::FLOAT ) :
    case ( TextureElementType::UNSIGNED_INT_8_8_8_8 ) :
    case ( TextureElementType::UNSIGNED_INT_8_8_8_8_REV ) :
    case ( TextureElementType::UNSIGNED_INT_10_10_10_2 ) :
    case ( TextureElementType::UNSIGNED_INT_2_10_10_10_REV ) :
      return 4;

    default:
      assert( false );
      return 0;
  }
}

GLenum Engine::Rendering::toGL( TexturePixelFormat pixelformat )
{
  switch( pixelformat )
  {
    case ( TexturePixelFormat::RED ) :
      return GL_RED;
    case ( TexturePixelFormat::RG ) :
      return GL_RG;
    case ( TexturePixelFormat::RGB ) :
      return GL_RGB;
    case ( TexturePixelFormat::BGR ) :
      return GL_BGR;
    case ( TexturePixelFormat::RGBA ) :
      return GL_RGBA;
    case ( TexturePixelFormat::BGRA ) :
      return GL_BGRA;
    case ( TexturePixelFormat::RED_INTEGER ) :
      return GL_RED_INTEGER;
    case ( TexturePixelFormat::RG_INTEGER ) :
      return GL_RG_INTEGER;
    case ( TexturePixelFormat::RGB_INTEGER ) :
      return GL_RGB_INTEGER;
    case ( TexturePixelFormat::BGR_INTEGER ) :
      return GL_BGR_INTEGER;
    case ( TexturePixelFormat::RGBA_INTEGER ) :
      return GL_RGBA_INTEGER;
    case ( TexturePixelFormat::BGRA_INTEGER ) :
      return GL_BGRA_INTEGER;
    case ( TexturePixelFormat::STENCIL_INDEX ) :
      return GL_STENCIL_INDEX;
    case ( TexturePixelFormat::DEPTH_COMPONENT ) :
      return GL_DEPTH_COMPONENT;
    case ( TexturePixelFormat::DEPTH_STENCIL ) :
      return GL_DEPTH_STENCIL;

    default:
      assert( false );
      return GL_NONE;
  }
}

int toGLCount( TexturePixelFormat pixelformat )
{
  switch( pixelformat )
  {
    case ( TexturePixelFormat::RED ) :
    case ( TexturePixelFormat::DEPTH_COMPONENT ) :
    case ( TexturePixelFormat::RED_INTEGER ) :
      return 1;
    case ( TexturePixelFormat::RG ) :
    case ( TexturePixelFormat::RG_INTEGER ) :
    case ( TexturePixelFormat::DEPTH_STENCIL ) :
      return 2;
    case ( TexturePixelFormat::RGB ) :
    case ( TexturePixelFormat::RGB_INTEGER ) :
    case ( TexturePixelFormat::BGR_INTEGER ) :
    case ( TexturePixelFormat::BGR ) :
      return 3;
    case ( TexturePixelFormat::RGBA ) :
    case ( TexturePixelFormat::BGRA ) :
    case ( TexturePixelFormat::RGBA_INTEGER ) :
    case ( TexturePixelFormat::BGRA_INTEGER ) :
      return 4;
    //case (TexturePixelFormat::STENCIL_INDEX): return GL_STENCIL_INDEX;

    default:
      assert( false );
      return 0;
  }
}


GLenum Engine::Rendering::toGL( TextureType texturetype )
{
  switch( texturetype )
  {
    case ( TextureType::Texture1D ) :
      return GL_TEXTURE_1D;
    case ( TextureType::Texture1DArray ) :
      return GL_TEXTURE_1D_ARRAY;
    case ( TextureType::Texture2D ) :
      return GL_TEXTURE_2D;
    case ( TextureType::Texture2DArray ) :
      return GL_TEXTURE_2D_ARRAY;
    case ( TextureType::TextureRectangle ) :
      return GL_TEXTURE_RECTANGLE;
    case ( TextureType::Texture3D ) :
      return GL_TEXTURE_3D;
    case (TextureType::TextureCubeMap):
      return GL_TEXTURE_CUBE_MAP;
    case (TextureType::TextureCubeMapArray):
      return GL_TEXTURE_CUBE_MAP_ARRAY;


    default:
      assert( false );
      return GL_NONE;
  }
}

GLenum Engine::Rendering::toGLBinding( TextureType texturetype )
{

  switch( texturetype )
  {
    case ( TextureType::Texture1D ) :
      return GL_TEXTURE_BINDING_1D;
    case ( TextureType::Texture1DArray ) :
      return GL_TEXTURE_BINDING_1D_ARRAY;
    case ( TextureType::Texture2D ) :
      return GL_TEXTURE_BINDING_2D;
    case ( TextureType::Texture2DArray ) :
      return GL_TEXTURE_BINDING_2D_ARRAY;
    case ( TextureType::TextureRectangle ) :
      return GL_TEXTURE_BINDING_RECTANGLE;
    case ( TextureType::Texture3D ) :
      return GL_TEXTURE_BINDING_3D;
    default:
      assert( false );
      return GL_NONE;
  }
}


GLenum Engine::Rendering::toGL( TextureAddressMode addressmode )
{
  switch( addressmode )
  {
    case ( TextureAddressMode::TextureAddressWrap ) :
      return GL_REPEAT;
    case ( TextureAddressMode::TextureAddressMirrorWrap ) :
      return GL_MIRRORED_REPEAT;
    case ( TextureAddressMode::TextureAddressEdgeClamp ) :
      return GL_CLAMP_TO_EDGE;
    case ( TextureAddressMode::TextureAddressMirrorEdgeClamp ) :
      return GL_MIRROR_CLAMP_TO_EDGE;
    case ( TextureAddressMode::TextureAddressBorderClamp ) :
      return GL_CLAMP_TO_BORDER;


    default:
      assert( false );
      return GL_NONE;
  }
}

GLenum Engine::Rendering::toGL( TextureFilterMode filtermode )
{
  switch( filtermode )
  {
    case ( TextureFilterMode::Nearest ) :
      return GL_NEAREST;
    case ( TextureFilterMode::Linear ) :
      return GL_LINEAR;
    case ( TextureFilterMode::NearestMipmapNearest ) :
      return GL_NEAREST_MIPMAP_NEAREST;
    case ( TextureFilterMode::LinearMipmapNearest ) :
      return GL_LINEAR_MIPMAP_NEAREST;
    case ( TextureFilterMode::NearestMipmapLinear ) :
      return GL_NEAREST_MIPMAP_LINEAR;
    case ( TextureFilterMode::LinearMipmapLinear ) :
      return GL_LINEAR_MIPMAP_LINEAR;


    default:
      assert( false );
      return GL_NONE;
  }
}


GLenum Engine::Rendering::toGL( TextureInternalFormat internalformat )
{
  switch( internalformat )
  {

    case ( TextureInternalFormat::DEPTH_COMPONENT ) :
      return GL_DEPTH_COMPONENT;
    case ( TextureInternalFormat::DEPTH_STENCIL ) :
      return GL_DEPTH_STENCIL;
    case ( TextureInternalFormat::RED ) :
      return GL_RED;
    case ( TextureInternalFormat::RG ) :
      return GL_RG;
    case ( TextureInternalFormat::RGB ) :
      return GL_RGB;
    case ( TextureInternalFormat::RGBA ) :
      return GL_RGBA;


    case ( TextureInternalFormat::R8 ) :
      return GL_R8;
    case ( TextureInternalFormat::R8_SNORM ) :
      return GL_R8_SNORM;
    case ( TextureInternalFormat::R16 ) :
      return GL_R16;
    case ( TextureInternalFormat::R16_SNORM ) :
      return GL_R16_SNORM;
    case ( TextureInternalFormat::RG8 ) :
      return GL_RG8;
    case ( TextureInternalFormat::RG8_SNORM ) :
      return GL_RG8_SNORM;
    case ( TextureInternalFormat::RG16 ) :
      return GL_RG16;
    case ( TextureInternalFormat::RG16_SNORM ) :
      return GL_RG16_SNORM;
    case ( TextureInternalFormat::R3_G3_B2 ) :
      return GL_R3_G3_B2;
    case ( TextureInternalFormat::RGB4 ) :
      return GL_RGB4;
    case ( TextureInternalFormat::RGB5 ) :
      return GL_RGB5;
    case ( TextureInternalFormat::RGB8 ) :
      return GL_RGB8;
    case ( TextureInternalFormat::RGB8_SNORM ) :
      return GL_RGB8_SNORM;
    case ( TextureInternalFormat::RGB10 ) :
      return GL_RGB10;
    case ( TextureInternalFormat::RGB12 ) :
      return GL_RGB12;
    case ( TextureInternalFormat::RGB16_SNORM ) :
      return GL_RGB16_SNORM;
    case ( TextureInternalFormat::RGBA2 ) :
      return GL_RGBA2;
    case ( TextureInternalFormat::RGBA4 ) :
      return GL_RGBA4;
    case ( TextureInternalFormat::RGB5_A1 ) :
      return GL_RGB5_A1;
    case ( TextureInternalFormat::RGBA8 ) :
      return GL_RGBA8;
    case ( TextureInternalFormat::RGBA8_SNORM ) :
      return GL_RGBA8_SNORM;
    case ( TextureInternalFormat::RGB10_A2 ) :
      return GL_RGB10_A2;
    case ( TextureInternalFormat::RGB10_A2UI ) :
      return GL_RGB10_A2UI;
    case ( TextureInternalFormat::RGBA12 ) :
      return GL_RGBA12;
    case ( TextureInternalFormat::RGBA16 ) :
      return GL_RGBA16;
    case ( TextureInternalFormat::SRGB8 ) :
      return GL_SRGB8;
    case ( TextureInternalFormat::SRGB8_ALPHA8 ) :
      return GL_SRGB8_ALPHA8;
    case ( TextureInternalFormat::R16F ) :
      return GL_R16F;
    case ( TextureInternalFormat::RG16F ) :
      return GL_RG16F;
    case ( TextureInternalFormat::RGB16F ) :
      return GL_RGB16F;
    case ( TextureInternalFormat::RGBA16F ) :
      return GL_RGBA16F;
    case ( TextureInternalFormat::R32F ) :
      return GL_R32F;
    case ( TextureInternalFormat::RG32F ) :
      return GL_RG32F;
    case ( TextureInternalFormat::RGB32F ) :
      return GL_RGB32F;
    case ( TextureInternalFormat::RGBA32F ) :
      return GL_RGBA32F;
    case ( TextureInternalFormat::R11F_G11F_B10F ) :
      return GL_R11F_G11F_B10F;
    case ( TextureInternalFormat::RGB9_E5 ) :
      return GL_RGB9_E5;
    case ( TextureInternalFormat::R8I ) :
      return GL_R8I;
    case ( TextureInternalFormat::R8UI ) :
      return GL_R8UI;
    case ( TextureInternalFormat::R16I ) :
      return GL_R16I;
    case ( TextureInternalFormat::R16UI ) :
      return GL_R16UI;
    case ( TextureInternalFormat::R32I ) :
      return GL_R32I;
    case ( TextureInternalFormat::R32UI ) :
      return GL_R32UI;
    case ( TextureInternalFormat::RG8I ) :
      return GL_RG8I;
    case ( TextureInternalFormat::RG8UI ) :
      return GL_RG8UI;
    case ( TextureInternalFormat::RG16I ) :
      return GL_RG16I;
    case ( TextureInternalFormat::RG16UI ) :
      return GL_RG16UI;
    case ( TextureInternalFormat::RG32I ) :
      return GL_RG32I;
    case ( TextureInternalFormat::RG32UI ) :
      return GL_RG32UI;
    case ( TextureInternalFormat::RGB8I ) :
      return GL_RGB8I;
    case ( TextureInternalFormat::RGB8UI ) :
      return GL_RGB8UI;
    case ( TextureInternalFormat::RGB16I ) :
      return GL_RGB16I;
    case ( TextureInternalFormat::RGB16UI ) :
      return GL_RGB16UI;
    case ( TextureInternalFormat::RGB32I ) :
      return GL_RGB32I;
    case ( TextureInternalFormat::RGB32UI ) :
      return GL_RGB32UI;
    case ( TextureInternalFormat::RGBA8I ) :
      return GL_RGBA8I;
    case ( TextureInternalFormat::RGBA8UI ) :
      return GL_RGBA8UI;
    case ( TextureInternalFormat::RGBA16I ) :
      return GL_RGBA16I;
    case ( TextureInternalFormat::RGBA16UI ) :
      return GL_RGBA16UI;
    case ( TextureInternalFormat::RGBA32I ) :
      return GL_RGBA32I;
    case ( TextureInternalFormat::RGBA32UI ) :
      return GL_RGBA32UI;

    case ( TextureInternalFormat::COMPRESSED_RED ) :
      return GL_COMPRESSED_RED;
    case ( TextureInternalFormat::COMPRESSED_RG ) :
      return GL_COMPRESSED_RG;
    case ( TextureInternalFormat::COMPRESSED_RGB ) :
      return GL_COMPRESSED_RGB;
    case ( TextureInternalFormat::COMPRESSED_RGBA ) :
      return GL_COMPRESSED_RGBA;
    case ( TextureInternalFormat::COMPRESSED_SRGB ) :
      return GL_COMPRESSED_SRGB;
    case ( TextureInternalFormat::COMPRESSED_SRGB_ALPHA ) :
      return GL_COMPRESSED_SRGB_ALPHA;
    case ( TextureInternalFormat::COMPRESSED_RED_RGTC1 ) :
      return GL_COMPRESSED_RED_RGTC1;
    case ( TextureInternalFormat::COMPRESSED_SIGNED_RED_RGTC1 ) :
      return GL_COMPRESSED_SIGNED_RED_RGTC1;
    case ( TextureInternalFormat::COMPRESSED_RG_RGTC2 ) :
      return GL_COMPRESSED_RG_RGTC2;
    case ( TextureInternalFormat::COMPRESSED_SIGNED_RG_RGTC2 ) :
      return GL_COMPRESSED_SIGNED_RG_RGTC2;
    case ( TextureInternalFormat::COMPRESSED_RGBA_BPTC_UNORM ) :
      return GL_COMPRESSED_RGBA_BPTC_UNORM;
    case ( TextureInternalFormat::COMPRESSED_SRGB_ALPHA_BPTC_UNORM ) :
      return GL_COMPRESSED_SRGB_ALPHA_BPTC_UNORM;
    case ( TextureInternalFormat::COMPRESSED_RGB_BPTC_SIGNED_FLOAT ) :
      return GL_COMPRESSED_RGB_BPTC_SIGNED_FLOAT;
    case ( TextureInternalFormat::COMPRESSED_RGB_BPTC_UNSIGNED_FLOAT ) :
      return GL_COMPRESSED_RGB_BPTC_UNSIGNED_FLOAT;


    default:
      assert( false );
      return GL_NONE;
  }
}


GLenum Engine::Rendering::toGL( PrimitiveIndexType primitiveindextype )
{
  switch( primitiveindextype )
  {
    case PrimitiveIndexType::Indices8Bit:
      return GL_UNSIGNED_BYTE;
    case PrimitiveIndexType::Indices16Bit:
      return GL_UNSIGNED_SHORT;
    case PrimitiveIndexType::Indices32Bit:
      return GL_UNSIGNED_INT;
    default:
      assert( false );
      return GL_NONE;
  }
}


GLenum Engine::Rendering::toGL( EnableAttribute attribute )
{
  switch( attribute )
  {
    case ( EnableAttribute::Blend ):
      return GL_BLEND;
    case ( EnableAttribute::ClipDistance ):
      return GL_CLIP_DISTANCE0;
    case ( EnableAttribute::ColorLogicOp ):
      return GL_COLOR_LOGIC_OP;
    case ( EnableAttribute::CullFace ):
      return GL_CULL_FACE;
    case ( EnableAttribute::DebugOutput ):
      return GL_DEBUG_OUTPUT;
    case ( EnableAttribute::DebugOutputSync ):
      return GL_DEBUG_OUTPUT_SYNCHRONOUS;
    case ( EnableAttribute::DepthClamp ):
      return GL_DEPTH_CLAMP;
    case ( EnableAttribute::DepthTest ):
      return GL_DEPTH_TEST;
    case ( EnableAttribute::Dither ):
      return GL_DITHER;
    case ( EnableAttribute::FrameBufferSrgb ):
      return GL_FRAMEBUFFER_SRGB;
    case ( EnableAttribute::LineSmooth ):
      return GL_LINE_SMOOTH;
    case ( EnableAttribute::MultiSample ):
      return GL_MULTISAMPLE;
    case ( EnableAttribute::PoligonOffsetFill ):
      return GL_POLYGON_OFFSET_FILL;
    case ( EnableAttribute::PoligonOffsetLine ):
      return GL_POLYGON_OFFSET_LINE;
    case ( EnableAttribute::PoligonOffsetPoint ):
      return GL_POLYGON_OFFSET_POINT;
    case ( EnableAttribute::PoligonSmooth ):
      return GL_POLYGON_SMOOTH;
    case ( EnableAttribute::PrimitiveRestart ):
      return GL_PRIMITIVE_RESTART;
    case ( EnableAttribute::PrimitiveRestartFixedIndex ):
      return GL_PRIMITIVE_RESTART_FIXED_INDEX;
    case ( EnableAttribute::RasterizerDiscard ):
      return GL_RASTERIZER_DISCARD;
    case ( EnableAttribute::SampleAlphaToCoverage ):
      return GL_SAMPLE_ALPHA_TO_COVERAGE;
    case ( EnableAttribute::SampleAlphaToOne ):
      return GL_SAMPLE_ALPHA_TO_ONE;
    case ( EnableAttribute::SampleCoverage ):
      return GL_SAMPLE_COVERAGE;
    case ( EnableAttribute::SampleShading ):
      return GL_SAMPLE_SHADING;
    case ( EnableAttribute::SampleMask ):
      return GL_SAMPLE_MASK;
    case ( EnableAttribute::ScissorTest ):
      return GL_SCISSOR_TEST;
    case ( EnableAttribute::StencilTest ):
      return GL_STENCIL_TEST;
    case ( EnableAttribute::TextureCubemapSeamless ):
      return GL_TEXTURE_CUBE_MAP_SEAMLESS;
    case ( EnableAttribute::ProgramPointSize ):
      return GL_PROGRAM_POINT_SIZE;

    default:
      assert( false );
      return GL_NONE;
  }
}

GLenum Engine::Rendering::toGL( CullMode cullmode )
{
  switch( cullmode )
  {
    case CullMode::Front:
      return GL_FRONT;
    case CullMode::Back:
      return GL_BACK;
    case CullMode::Both:
      return GL_FRONT_AND_BACK;
    default:
      assert( false );
      return GL_NONE;
  }
}

GLenum Engine::Rendering::toGL( CullOrder cullOrder )
{
  switch( cullOrder )
  {
    case CullOrder::ClockWise:
      return GL_CW;
    case CullOrder::CounterClockWise:
      return GL_CCW;
    default:
      assert( false );
      return GL_NONE;
  }
}

GLenum Engine::Rendering::toGL( BlendFunc blendFunc )
{
  switch( blendFunc )
  {
    case BlendFunc::SrcColor:
      return GL_SRC_COLOR;
    case BlendFunc::OneMinusSrcColor:
      return GL_ONE_MINUS_SRC_COLOR;
    case BlendFunc::SrcAlpha:
      return GL_SRC_ALPHA;
    case BlendFunc::OneMinusSrcAlpha:
      return GL_ONE_MINUS_SRC_ALPHA;
    case BlendFunc::DstAlpha:
      return GL_DST_ALPHA;
    case BlendFunc::OneMinusDstAlpha:
      return GL_ONE_MINUS_DST_ALPHA;
    case BlendFunc::DstColor:
      return GL_DST_COLOR;
    case BlendFunc::OneMinusDstColor:
      return GL_ONE_MINUS_DST_COLOR;
    case BlendFunc::SrcAlphaSaturate:
      return GL_SRC_ALPHA_SATURATE;
  }
}

GLenum Engine::Rendering::toGL( DepthFunc depthFunc )
{
  switch( depthFunc )
  {
    case DepthFunc::Never:
      return GL_NEVER;
    case DepthFunc::Less:
      return GL_LESS;
    case DepthFunc::Equal:
      return GL_EQUAL;
    case DepthFunc::Lequal:
      return GL_LEQUAL;
    case DepthFunc::Greater:
      return GL_GREATER;
    case DepthFunc::NotEqual:
      return GL_NOTEQUAL;
    case DepthFunc::GEqual:
      return GL_GEQUAL;
    case DepthFunc::Always:
      return GL_ALWAYS;
    default:
      assert( false );
      return GL_NONE;
  }
}


std::map< PrimitiveIndexType, const char* > genGLSTRMAP()
{
  std::map< PrimitiveIndexType, const char* > result;

  result[ PrimitiveIndexType::Indices8Bit ] = "GL_UNSIGNED_BYTE";
  result[ PrimitiveIndexType::Indices16Bit ] = "GL_UNSIGNED_SHORT";
  result[ PrimitiveIndexType::Indices32Bit ] = "GL_UNSIGNED_INT";
  result[ PrimitiveIndexType::IndicesNone ] = "GL_NONE";

  return result;
}

const char* Engine::Rendering::toGLSTR( PrimitiveIndexType primitiveindextype )
{
  static auto strmap = genGLSTRMAP();

  auto w = strmap.find( primitiveindextype );

  if( w != strmap.end() )
  {
    return w->second;
  }
  assert( false );
  return "GL_NONE";
}


Graphics::Graphics() :
  m_requireBufferInit( false )
{


}


Graphics::~Graphics( void )
{
}

void Graphics::initializeGlew()
{
  GLenum err = glewInit();
  if( GLEW_OK != err )
  {
    /* Problem: glewInit failed, something is seriously wrong. */
    std::string msg =
      std::string( "Error initializing glew: " ) + reinterpret_cast<const char*>(glewGetErrorString( err ));
    throw std::runtime_error( msg );
  }
}

const char* Graphics::init( const std::string& title, int screenWidth, int screenHeight, bool fullscreen, bool resizeable )
{
  glewExperimental = true;
  if( !glfwInit() )
    throw std::runtime_error( "Error initializing GLFW" );

  // Decide GL+GLSL versions
#if defined( IMGUI_IMPL_OPENGL_ES2 )
  // GL ES 2.0 + GLSL 100
  const char* glsl_version = "#version 100";
  glfwWindowHint( GLFW_CONTEXT_VERSION_MAJOR, 2 );
  glfwWindowHint( GLFW_CONTEXT_VERSION_MINOR, 0 );
  glfwWindowHint( GLFW_CLIENT_API, GLFW_OPENGL_ES_API );
#elif defined( __APPLE__ )
  // GL 3.2 + GLSL 150
  const char* glsl_version = "#version 150";
  glfwWindowHint( GLFW_CONTEXT_VERSION_MAJOR, 3 );
  glfwWindowHint( GLFW_CONTEXT_VERSION_MINOR, 2 );
  glfwWindowHint( GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE );// 3.2+ only
  glfwWindowHint( GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE );          // Required on Mac
#else
  // GL 3.0 + GLSL 130
  const char* glsl_version = "#version 130";
  glfwWindowHint( GLFW_CONTEXT_VERSION_MAJOR, 3 );
  glfwWindowHint( GLFW_CONTEXT_VERSION_MINOR, 0 );
  //glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
  //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // 3.0+ only
#endif

  glfwWindowHint( GLFW_DOUBLEBUFFER, GLFW_TRUE );

  // Request stencil buffer of at least 8-bit size to supporting clipping on transformed elements.
  glfwWindowHint(GLFW_STENCIL_BITS, 8);

  // Enable MSAA for better-looking visuals, especially when transforms are applied.
  glfwWindowHint(GLFW_SAMPLES, 2);

  // Apply window properties and create it.
  glfwWindowHint(GLFW_RESIZABLE, resizeable ? GLFW_TRUE : GLFW_FALSE );
  glfwWindowHint(GLFW_SCALE_TO_MONITOR, GLFW_TRUE);
//  glfwWindowHint(GLFW_DECORATED, GLFW_FALSE);

  //glfwGetPrimaryMonitor()
  if( fullscreen )
    m_pWindow = glfwCreateWindow( screenWidth, screenHeight, title.c_str(), glfwGetPrimaryMonitor(), NULL );
  else
    m_pWindow = glfwCreateWindow( screenWidth, screenHeight, title.c_str(), NULL, NULL );

  if( !m_pWindow )
  {
    const char* glfwError = nullptr;
    glfwGetError( &glfwError );
    glfwTerminate();
    throw std::runtime_error( std::string( "Could not create GLFW window: " ) + glfwError );
  }
  // glfwSetWindowUserPointer(window, &context);
  // thats useful for key-callbacks

  /* Make the window's context current */
  glfwMakeContextCurrent( m_pWindow );
  glewExperimental = true;

  glfwSetInputMode( m_pWindow, GLFW_CURSOR, GLFW_CURSOR_HIDDEN );
  glfwSetInputMode( m_pWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED );

  glfwGetFramebufferSize( m_pWindow, &m_windowWidth, &m_windowHeight );

  auto clbk = []( GLFWwindow* window, int width, int height )
  {
    auto& gfx = Engine::Service< Graphics >::ref();

    gfx.setWindowSize( width, height );
    gfx.setViewport( 0, 0, width, height );
  };

  glfwSetFramebufferSizeCallback( getWindowHandle(), clbk );

  initializeGlew();

  return glsl_version;
}

void Graphics::clearColor( float red, float green, float blue, float alpha )
{
  glClearColor( red, green, blue, alpha );
}

void Graphics::clear( bool clearDepth, bool clearStencil, bool clearColor,
                      float depthValue, int stencilValue )
{
  GLbitfield mask = 0;

  mask |= ( ( clearDepth ) ? GL_DEPTH_BUFFER_BIT : 0 )
          | ( ( clearStencil ) ? GL_STENCIL_BUFFER_BIT : 0 )
          | ( ( clearColor ) ? GL_COLOR_BUFFER_BIT : 0 );

  glClear( mask );
}

void Graphics::enableDepthWrite( bool enable )
{
  if( enable )
    glDepthMask( GL_TRUE );
  else
    glDepthMask( GL_FALSE );
}

void Graphics::enable( EnableAttribute attrib )
{
  glEnable( toGL( attrib ) );
}

void Graphics::disable( EnableAttribute attrib )
{
  glDisable( toGL( attrib ) );
}

void Graphics::setDepthFunc( DepthFunc depthFunc )
{
  glDepthFunc( toGL( depthFunc ) );
}

void Graphics::setBlendFunc( BlendFunc blendFunc1, BlendFunc blendFunc2 )
{
  glBlendFunc( toGL( blendFunc1 ), toGL( blendFunc2 ) );
}

void Graphics::setCullMode( CullMode cullmode )
{
  glCullFace( toGL( cullmode ) );
}

void Graphics::setCullOrder( CullOrder cullOrder )
{
  glFrontFace( toGL( cullOrder ) );
}

GLFWwindow* Graphics::getWindowHandle()
{
  return m_pWindow;
}

bool Graphics::shouldWindowClose()
{
  return glfwWindowShouldClose( m_pWindow );
}

bool Graphics::isWindowFocused()
{
  return glfwGetWindowAttrib( m_pWindow, GLFW_FOCUSED );
}

void Graphics::getFramebufferSize( int& width, int& height )
{
  glfwGetFramebufferSize( m_pWindow, &width, &height );
}

void Graphics::makeContextCurrent()
{
  glfwMakeContextCurrent( m_pWindow );
}

void Graphics::swapBuffers()
{
  glfwSwapBuffers( m_pWindow );
}

void Graphics::terminate()
{
  glfwTerminate();
}

int Graphics::getWindowHeight()
{
  return m_windowHeight;
}

int Graphics::getWindowWidth()
{
  return m_windowWidth;
}

Engine::ivec2 Graphics::getWindowSize()
{
  return { m_windowWidth, m_windowHeight };
}

void Graphics::setWindowSize( int width, int height )
{
  m_windowWidth = width;
  m_windowHeight = height;
  m_requireBufferInit = true;
}

void Graphics::setViewport( int x, int y, int width, int height )
{
  glViewport( x, y, width, height );
}

bool Graphics::isBufferReInitRequired() const
{
  return m_requireBufferInit;
}

void Graphics::clearBufferReInit()
{
  m_requireBufferInit = false;
}

void Graphics::blitFramebuffer( const Engine::ivec4& src, const Engine::ivec4& dst, int mask, TextureFilterMode filter )
{
  glBlitFramebuffer( src.x, src.y, src.z, src.w,
                     dst.x, dst.y, dst.z, dst.w, mask, toGL( filter ) );
}

std::string Graphics::getDeviceString()
{
  std::string vendor = (const char*)glGetString(GL_VENDOR);
  std::string renderer = (const char*)glGetString(GL_RENDERER);
  std::string version = (const char*)glGetString(GL_VERSION);
  std::string shading_language_version =
          (const char*)glGetString(GL_SHADING_LANGUAGE_VERSION);

  std::ostringstream sstr;
  sstr << "OpenGL Vendor: " << vendor << std::endl;
  sstr << "OpenGL Renderer: " << renderer << std::endl;
  sstr << "OpenGL Version: " << version << std::endl;
  sstr << "OpenGL Shading Language Version: " << shading_language_version
       << std::endl;

  return sstr.str();
}

uint32_t Graphics::getFrameCount() const
{
  return m_frameCount;
}

void Graphics::resetFrameCount()
{
 m_frameCount = 0;
}

void Graphics::increaseFrameCount()
{
  ++m_frameCount;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


VertexElement::VertexElement( VertexDataSemantic semantic, VertexDataType type, int count, const std::string& name ) :
  m_semantic( semantic ),
  m_type( type ),
  m_count( count ),
  m_name( name )
{
}


VertexDataType VertexElement::getType() const
{
  return m_type;
}


VertexElement::~VertexElement()
{
}


const std::string& VertexElement::getName() const
{
  return m_name;
}

int VertexElement::sizeBytes() const
{
  int size = 0;
  switch( m_type )
  {
    case VertexDataType::BYTE:
    case VertexDataType::UNSIGNED_BYTE:
      size = 1;
      break;
    case VertexDataType::DOUBLE:
      size = 8;
      break;
    case VertexDataType::FLOAT:
    case VertexDataType::INT:
      size = 4;
      break;
    case VertexDataType::SHORT:
    case VertexDataType::UNSIGNED_SHORT:
      size = 2;
      break;
  }

  return size * m_count;
}


int VertexElement::sizeElems() const
{
  return m_count;
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


VertexDeclaration::VertexDeclaration()
{
}


VertexDeclaration::~VertexDeclaration( void )
{
}


void VertexDeclaration::add( const VertexElement& elem )
{
  m_elements.push_back( elem );
}


int VertexDeclaration::stride() const
{

  int size = 0;

  for( auto& elem : m_elements )
  {
    size += elem.sizeBytes();
  }

  return size;
}


const std::vector< VertexElement >& VertexDeclaration::getElements() const
{
  return m_elements;
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


VertexBuffer::VertexBuffer( int numVertices, const VertexDeclaration& dec, Usage usage, bool allocateCpu )
  :
  m_numVertices( numVertices ), m_declaration( dec ), m_usage( usage ), m_vbo( 0 ), m_gpuSize( 0 )
{
  glGenBuffers( 1, &m_vbo );
  checkOpenGLError();

  if( allocateCpu )
    allocateCpuMemory();
}


VertexBuffer::~VertexBuffer()
{
  if( m_vbo )
  {
    glDeleteBuffers( 1, &m_vbo );
    m_vbo = 0;
  }
}


int VertexBuffer::getNumVertices() const
{
  return m_numVertices;
}


int VertexBuffer::getLogicalBufferSizeBytes() const
{
  return m_numVertices * m_declaration.stride();
}


const unsigned char* VertexBuffer::getCpuPtr() const
{
  if( !m_cpuData )
  {
    throw std::runtime_error( "no cpu data" );
  }
  return m_cpuData->data();
}


unsigned char* VertexBuffer::getCpuPtr()
{
  if( !m_cpuData )
  {
    throw std::runtime_error( "no cpu data" );
  }

  return m_cpuData->data();
}


int VertexBuffer::getGpuSizeInBytes() const
{
  return m_gpuSize;
}


const VertexDeclaration& VertexBuffer::getDeclaration() const
{
  return m_declaration;
}


VertexDeclaration& VertexBuffer::getDeclaration()
{
  return m_declaration;
}


void VertexBuffer::setNumVertices( std::size_t size, bool perseve_old_cpu_data )
{

  ///set the new number of vertices
  m_numVertices = size;

  std::size_t new_bytes = getLogicalBufferSizeBytes();

  if( hasCpuMemory() )
  {
    if( perseve_old_cpu_data && !!m_cpuData && new_bytes > m_cpuData->size() )
    {
      ///keep the old data around a bit
      std::shared_ptr< CpuData > oldCpuData = m_cpuData;


      ///allocate the buffer
      allocateCpuMemory();

      ///copy the old buffer to the new one
      memcpy( m_cpuData->data(), oldCpuData->data(), oldCpuData->size() );
    }
    else
    {
      allocateCpuMemory();
    }
  }
}


void VertexBuffer::allocateCpuMemory()
{
  std::size_t bytes = getLogicalBufferSizeBytes();

  if( !m_cpuData )
  {
    m_cpuData = std::make_shared< CpuData >( bytes );
  }
  else
  {
    if( m_cpuData->size() != bytes )
      m_cpuData->resize( bytes );
  }
}


void VertexBuffer::allocateGpuMemory()
{

  assert( isBound() );
  checkOpenGLError();

  int bytes = getLogicalBufferSizeBytes();

  glBufferData( GL_ARRAY_BUFFER, bytes, NULL, toGL( m_usage ) );
  checkOpenGLError();

  m_gpuSize = bytes;

}

bool VertexBuffer::hasCpuMemory() const
{
  return !!m_cpuData;
}

void VertexBuffer::bind()
{
  checkOpenGLError();
  glBindBuffer( GL_ARRAY_BUFFER, m_vbo );
  checkOpenGLError();
  assert( isBound() );
}

void VertexBuffer::unbind()
{
  checkOpenGLError();
  glBindBuffer( GL_ARRAY_BUFFER, 0 );
  checkOpenGLError();
}

void VertexBuffer::unbindAll()
{
  checkOpenGLError();
  glBindBuffer( GL_ARRAY_BUFFER, 0 );
  checkOpenGLError();
}

bool VertexBuffer::isBound() const
{
  checkOpenGLError();
  GLint boundvbo = 0;
  glGetIntegerv( GL_ARRAY_BUFFER_BINDING, &boundvbo );
  checkOpenGLError();
  return boundvbo != 0 && boundvbo == m_vbo;
}

void VertexBuffer::updateToGpu( const uint8_t* data, int bytes )
{
  assert( isBound() );
  checkOpenGLError();
  if( !data && !m_cpuData )
  {
    throw std::runtime_error( "no cpu data to send to gpu" );
  }


  if( !data )
  {
    data = m_cpuData->data();
    bytes = m_cpuData->size();
  }


  assert( bytes == getLogicalBufferSizeBytes() );
  glBufferData( GL_ARRAY_BUFFER, bytes, data, toGL( m_usage ) );
  checkOpenGLError();

  m_gpuSize = bytes;
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


IndexBuffer::IndexBuffer( std::weak_ptr< Mesh > mesh, int numIndices, PrimitiveIndexType type, Usage usage,
                          bool allocateCpu )
  :
  m_mesh( mesh ), m_numIndices( numIndices ), m_indexType( type ), m_usage( usage ), m_indexBuffer( 0 ), m_gpuSize( 0 )
{
  glGenBuffers( 1, &m_indexBuffer );
  checkOpenGLError();

  if( allocateCpu )
    allocateCpuMemory();
}


IndexBuffer::~IndexBuffer( void )
{
  if( m_indexBuffer )
  {
    glDeleteBuffers( 1, &m_indexBuffer );
    m_indexBuffer = 0;
  }
}


int IndexBuffer::getNumIndices() const
{
  return m_numIndices;
}


PrimitiveIndexType IndexBuffer::getIndexType() const
{
  return m_indexType;
}


int IndexBuffer::getIndexSizeBytes() const
{
  int32_t size = 0;

  switch( m_indexType )
  {
    case PrimitiveIndexType::IndicesNone:
      size = 0;
      break;
    case PrimitiveIndexType::Indices8Bit:
      size = 1;
      break;
    case PrimitiveIndexType::Indices16Bit:
      size = 2;
      break;
    case PrimitiveIndexType::Indices32Bit:
      size = 4;
      break;
  }

  return size;
}


bool IndexBuffer::hasCpuMemory() const
{
  return !!m_indexData;
}

int IndexBuffer::getLogicalBufferSizeBytes() const
{
  return getNumIndices() * getIndexSizeBytes();
}

void IndexBuffer::allocateCpuMemory()
{
  int bytes = getLogicalBufferSizeBytes();

  if( !m_indexData )
  {
    m_indexData = std::make_shared< cpu_data_t >( bytes );
  }
  else
  {
    m_indexData->resize( bytes );
  }
}


void IndexBuffer::setNumIndices( std::size_t size, bool perseve_old_cpu_data )
{

  ///set the new number of vertices
  m_numIndices = size;

  std::size_t newBytes = getLogicalBufferSizeBytes();

  if( hasCpuMemory() )
  {
    if( perseve_old_cpu_data && !!m_indexData && newBytes > m_indexData->size() )
    {
      ///keep the old data around a bit
      std::shared_ptr< cpu_data_t > oldCpuData = m_indexData;

      ///allocate the buffer
      allocateCpuMemory();

      ///copy the old buffer to the new one
      memcpy( m_indexData->data(), oldCpuData->data(), oldCpuData->size() );
    }
    else
    {
      allocateCpuMemory();
    }
  }
}


unsigned char* IndexBuffer::getCpuPtr()
{
  if( !m_indexData )
  {
    throw std::runtime_error( "no cpu data" );
  }
  return m_indexData->data();
}


const unsigned char* IndexBuffer::getCpuPtr() const
{
  if( !m_indexData )
  {
    throw std::runtime_error( "no cpu data" );
  }
  return m_indexData->data();
}


bool IndexBuffer::isVAOBound() const
{
  if( auto mesh = m_mesh.lock() )
  {
    return mesh->isBound();
  }

  return false;
}

void IndexBuffer::bind()
{
  ///https://www.opengl.org/wiki/Buffer_Object#General_use
  ///"Note that this binding target is part of a Vertex Array Objects state,
  /// so a VAO must be bound before binding a buffer here".
  assert( isVAOBound() );
  checkOpenGLError();

  glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, m_indexBuffer );
  checkOpenGLError();
}

void IndexBuffer::unbind()
{
  checkOpenGLError();
  glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, 0 );
  checkOpenGLError();
}

void IndexBuffer::unbindAll()
{
  checkOpenGLError();
  glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, 0 );
  checkOpenGLError();
}

bool IndexBuffer::isBound() const
{
  checkOpenGLError();
  GLint boundibo = 0;
  glGetIntegerv( GL_ELEMENT_ARRAY_BUFFER_BINDING, &boundibo );
  checkOpenGLError();
  return boundibo != 0 && boundibo == m_indexBuffer;
}

void IndexBuffer::allocateGpuMemory()
{
  assert( isBound() );
  checkOpenGLError();

  int bytes = getLogicalBufferSizeBytes();

  glBufferData( GL_ELEMENT_ARRAY_BUFFER, bytes, NULL, toGL( m_usage ) );
  checkOpenGLError();

  m_gpuSize = bytes;
}


void IndexBuffer::updateToGpu( const uint8_t* data, int bytes )
{
  assert( isBound() );
  checkOpenGLError();
  if( !data && !m_indexData )
  {
    throw std::runtime_error( "no cpu data to send to gpu" );
  }

  if( !data )
  {
    data = m_indexData->data();
    bytes = m_indexData->size();
  }


  assert( bytes == getLogicalBufferSizeBytes() );
  glBufferData( GL_ELEMENT_ARRAY_BUFFER, bytes, data, toGL( m_usage ) );
  checkOpenGLError();

  m_gpuSize = bytes;
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


Shader::Shader( ShaderType type ) :
  m_shaderHandle( 0 ),
  m_type( type )
{
  if( type == ShaderType::VertexShader )
  {
    m_shaderHandle = glCreateShader( GL_VERTEX_SHADER );
    //assert(m_shaderHandle != -1);
    checkOpenGLError();
  }
  else if( type == ShaderType::PixelShader )
  {
    m_shaderHandle = glCreateShader( GL_FRAGMENT_SHADER );
    //assert(m_shaderHandle != -1);
    checkOpenGLError();
  }
  else if( type == ShaderType::GeometryShader )
  {
    m_shaderHandle = glCreateShader( GL_GEOMETRY_SHADER );
    //assert(m_shaderHandle != -1);
    checkOpenGLError();
  }
  else if( type == ShaderType::ComputeShader )
  {
    m_shaderHandle = glCreateShader( GL_COMPUTE_SHADER );
    //assert(m_shaderHandle != -1);
    checkOpenGLError();
  }
  else
  {
    throw std::runtime_error( "Cannot create Shader: Invalid shader type" );
  }
  assert( m_shaderHandle );
}

Shader::Shader( ShaderType type, const std::string& fileName ) :
  m_shaderHandle( 0 ),
  m_type( type )
{
  if( type == ShaderType::VertexShader )
  {
    m_shaderHandle = glCreateShader( GL_VERTEX_SHADER );
    //assert(m_shaderHandle != -1);
    checkOpenGLError();
  }
  else if( type == ShaderType::PixelShader )
  {
    m_shaderHandle = glCreateShader( GL_FRAGMENT_SHADER );
    //assert(m_shaderHandle != -1);
    checkOpenGLError();
  }
  else if( type == ShaderType::GeometryShader )
  {
    m_shaderHandle = glCreateShader( GL_GEOMETRY_SHADER );
    //assert(m_shaderHandle != -1);
    checkOpenGLError();
  }
  else if( type == ShaderType::ComputeShader )
  {
    m_shaderHandle = glCreateShader( GL_COMPUTE_SHADER );
    //assert(m_shaderHandle != -1);
    checkOpenGLError();
  }
  else
  {
    throw std::runtime_error( "Cannot create Shader: Invalid shader type" );
  }
  assert( m_shaderHandle );

  loadFromFile( type, fileName.c_str() );
}


void Shader::loadFromString( ShaderType type,
                             const char* shaderData,
                             const char* entryPoint,
                             const char* profile )
{
  assert( entryPoint == 0 );
  assert( profile == 0 );
  if( type != m_type )
  {
    throw std::runtime_error( "Cannot load Shader: Invalid shader type; does not match type indicated in constructor" );
  }

  assert( m_shaderHandle );

  glShaderSource( m_shaderHandle, 1, &shaderData, NULL );
  checkOpenGLError();
  glCompileShader( m_shaderHandle );
  checkOpenGLError();

  GLint params = 0;
  glGetShaderiv( m_shaderHandle, GL_COMPILE_STATUS, &params );
  checkOpenGLError();

  if( params == GL_FALSE )
  {
    GLint maxLength = 0;
    glGetShaderiv( m_shaderHandle, GL_INFO_LOG_LENGTH, &maxLength );

    std::vector< GLchar > errorLog( maxLength );
    glGetShaderInfoLog( m_shaderHandle, maxLength, &maxLength, &errorLog[ 0 ] );

    glDeleteShader( m_shaderHandle );
    m_shaderHandle = 0;
    throw std::runtime_error( std::string( "Shader: Failed to compile. " ) + errorLog.data() );
  }
}

std::string Shader::getSourceFromFile( const std::string& path )
{
  //std::cout << "Shader Path " << path << std::endl;
  std::string includeIndentifier = "#include ";
  std::string fullSourceCode = "";

  //open file
  std::ifstream file;
  file.open( path, std::ios::in | std::ios::binary );
  if( !file.is_open() )
  {
    throw std::runtime_error( std::string( "Failed to open file: " ) + path );
  }

  std::string lineBuffer;
  while( std::getline( file, lineBuffer ) )
  {
    // Look for the new shader include identifier
    if( lineBuffer.find( includeIndentifier ) != lineBuffer.npos )
    {
      // Remove the include identifier, this will cause the path to remain
      lineBuffer.erase( 0, includeIndentifier.size() );

      // The include path is relative to the current shader file path
      std::string pathOfThisFile;
      size_t found = path.find_last_of( "/\\" );
      pathOfThisFile = path.substr( 0, found + 1 );

      //std::cout << "Including shader " << pathOfThisFile << std::endl;


      lineBuffer.insert( 0, pathOfThisFile );

      if( lineBuffer.find_first_of( '\r' ) != std::string::npos )
      {
        lineBuffer = lineBuffer.substr( 0, lineBuffer.find_first_of( '\r' ) );
      }
      // By using recursion, the new include file can be extracted
      // and inserted at this location in the shader source code
      // isRecursiveCall = true;
      fullSourceCode += getSourceFromFile( lineBuffer );

      // Do not add this line to the shader source code, as the include
      // path would generate a compilation issue in the final source code
      continue;
    }

    fullSourceCode += lineBuffer + '\n';
  }

  return fullSourceCode;

}

void Shader::loadFromFile( ShaderType type,
                           const char* fileName,
                           const char* entryPoint,
                           const char* profile )
{


  std::string fullSourceCode = "";
  std::string path( fileName );

  fullSourceCode = getSourceFromFile( path );

  loadFromString( type, fullSourceCode.c_str(), entryPoint, profile );

}


Shader::~Shader( void )
{
  glDeleteShader( m_shaderHandle );
  checkOpenGLError();
  m_shaderHandle = 0;
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Ssbo::Ssbo( int size ) :
  m_handle( 0 ),
  m_size( size )
{
  glGenBuffers( 1, &m_handle );
  checkOpenGLError();
  glBindBuffer( GL_SHADER_STORAGE_BUFFER, m_handle );
  checkOpenGLError();
  glBufferData( GL_SHADER_STORAGE_BUFFER, size, nullptr, GL_DYNAMIC_DRAW );
  //glBindBufferBase( GL_SHADER_STORAGE_BUFFER, 2, m_handle );
  checkOpenGLError();
  glBindBuffer( GL_SHADER_STORAGE_BUFFER, 0 );
  checkOpenGLError();
}

Ssbo::~Ssbo()
{

}

GLuint Ssbo::getHandle() const
{
  return m_handle;
}

void Ssbo::bindBuffer()
{
  glBindBuffer( GL_SHADER_STORAGE_BUFFER, m_handle );
  checkOpenGLError();
}

void Ssbo::bindBufferBase( int index )
{
  glBindBufferBase( GL_SHADER_STORAGE_BUFFER, index, m_handle );
  checkOpenGLError();
}

void Ssbo::unbindBufferBase( int index )
{
  glBindBufferBase( GL_SHADER_STORAGE_BUFFER, index, 0 );
  checkOpenGLError();
}

void Ssbo::unbindBuffer()
{
  glBindBuffer( GL_SHADER_STORAGE_BUFFER, 0 );
  checkOpenGLError();
}

void Ssbo::updateBufferData( uint8_t* data, uint32_t size )
{
  bindBuffer();
  glBufferData( GL_SHADER_STORAGE_BUFFER, size, data, GL_DYNAMIC_DRAW );
  checkOpenGLError();
  unbindBuffer();
}

void Ssbo::updatePartialBufferData(int offset, uint8_t* data, uint32_t size)
{
  bindBuffer();
  glBufferSubData(GL_SHADER_STORAGE_BUFFER, offset, size, data);
  checkOpenGLError();
  unbindBuffer();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


  TextureBuffer::TextureBuffer( int size, TextureInternalFormat format ) :
          m_bufferHandle( 0 ),
          m_textureHandle( 0 ),
          m_size( size ),
          m_format( format )
  {
    glPixelStorei( GL_PACK_ALIGNMENT, 1 );

    glGenBuffers( 1, &m_bufferHandle );
    glBindBuffer( GL_TEXTURE_BUFFER, m_bufferHandle );
    //glBufferData( GL_TEXTURE_BUFFER, size, data, GL_STATIC_DRAW );
    glGenTextures( 1, &m_textureHandle );
    glBindTexture( GL_TEXTURE_BUFFER, m_textureHandle );
    glTexBuffer( GL_TEXTURE_BUFFER, toGL( format ), m_bufferHandle );
  }

  TextureBuffer::~TextureBuffer()
  {
    glDeleteTextures( 1, &m_textureHandle );
    glDeleteBuffers( 1, &m_bufferHandle );
  }

  GLuint TextureBuffer::getBufferHandle() const
  {
    return m_bufferHandle;
  }

  GLuint TextureBuffer::getTextureHandle() const
  {
    return m_textureHandle;
  }

  TextureInternalFormat TextureBuffer::getTextureFormat() const
  {
    return m_format;
  }

  void TextureBuffer::bindBuffer()
  {
    glBindBuffer( GL_TEXTURE_BUFFER, m_bufferHandle );
    checkOpenGLError();
  }

  void TextureBuffer::bindBufferBase( int index )
  {
    glBindBufferBase( GL_TEXTURE_BUFFER, index, m_bufferHandle );
    checkOpenGLError();
  }

  void TextureBuffer::unbindBufferBase( int index )
  {
    glBindBufferBase( GL_TEXTURE_BUFFER, index, 0 );
    checkOpenGLError();
  }

  void TextureBuffer::unbindBuffer()
  {
    glBindBuffer( GL_TEXTURE_BUFFER, 0 );
    checkOpenGLError();
  }

  void TextureBuffer::updateBufferData( uint8_t* data, uint32_t size )
  {
    bindBuffer();
    glBufferData( GL_TEXTURE_BUFFER, size, data, GL_STATIC_DRAW );
    checkOpenGLError();
    unbindBuffer();
  }

  void TextureBuffer::updatePartialBufferData( int offset, uint8_t* data, uint32_t size )
  {
    bindBuffer();
    glBufferSubData( GL_TEXTURE_BUFFER, offset, size, data );
    checkOpenGLError();
    unbindBuffer();
  }

  void TextureBuffer::bindTexture()
  {
    glBindTexture( GL_TEXTURE_BUFFER, m_textureHandle );
    checkOpenGLError();
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

ShaderProgram::ShaderProgram() :
  m_programHandle( 0 )
{
  m_programHandle = glCreateProgram();
  checkOpenGLError();
  assert( m_programHandle );
}


ShaderProgram::~ShaderProgram( void )
{
  if( m_programHandle )
  {
    std::cout << "" << std::to_string( m_programHandle ) << std::endl;
    glDeleteProgram( m_programHandle );
    checkOpenGLError();
  }
}


GLuint ShaderProgram::getHandle() const
{
  return m_programHandle;
}

void ShaderProgram::use()
{
  assert( m_programHandle );
  checkOpenGLError();
  glUseProgram( m_programHandle );
  checkOpenGLError();
}

bool ShaderProgram::inUse() const
{
  checkOpenGLError();
  GLint boundsp = 0;
  glGetIntegerv( GL_CURRENT_PROGRAM, &boundsp );
  checkOpenGLError();
  return boundsp != 0 && boundsp == m_programHandle;
}


void ShaderProgram::deselect()
{
  checkOpenGLError();
  glUseProgram( 0 );
  checkOpenGLError();
}

void ShaderProgram::deselectAll()
{
  checkOpenGLError();
  glUseProgram( 0 );
  checkOpenGLError();
}

int ShaderProgram::getUniformLocation( const char* name )
{
  return glGetUniformLocation( m_programHandle, name );
}

void ShaderProgram::setUniform( const glm::mat4& matrix, const std::string& name )
{
  int location = getUniformLocation( name.c_str() );
  assert( location != -1 );

  ShaderProgram::setMat4( location, matrix );
}

void ShaderProgram::setUniform( double value, const std::string& name )
{
  int location = getUniformLocation( name.c_str() );
  assert( location != -1 );

  ShaderProgram::setDouble( location, value );
}

void ShaderProgram::setUniform( float value, const std::string& name )
{
  int location = getUniformLocation( name.c_str() );
  assert( location != -1 );

  ShaderProgram::setFloat( location, value );
}

void ShaderProgram::setUniform( float v1, float v2, float v3, const std::string& name )
{
  int location = getUniformLocation( name.c_str() );
  assert( location != -1 );

  ShaderProgram::setFloat3( location, v1, v2, v3 );
}

void ShaderProgram::setUniform( Engine::vec3* vecList, size_t size, const std::string& name )
{
  int location = getUniformLocation( name.c_str() );
  assert( location != -1 );

  ShaderProgram::setVectorList3( location, vecList, size );
}

void ShaderProgram::setUniform( float v1, float v2, const std::string& name )
{
  int location = getUniformLocation( name.c_str() );
  assert( location != -1 );

  ShaderProgram::setFloat2( location, v1, v2 );
}


void ShaderProgram::setUniform( int value, const std::string& name )
{
  int location = getUniformLocation( name.c_str() );
  assert( location != -1 );

  ShaderProgram::setInt( location, value );
}

void ShaderProgram::setUniform( unsigned int value, const std::string& name )
{
  int location = getUniformLocation( name.c_str() );
  assert( location != -1 );

  ShaderProgram::setInt( location, value );
}

void ShaderProgram::setUniform( Engine::ivec2 value, const std::string& name )
{
  int location = getUniformLocation( name.c_str() );
  assert( location != -1 );

  ShaderProgram::setInt2( location, value.x, value.y );
}

void ShaderProgram::setUniform( Engine::vec2 value, const std::string& name )
{
  int location = getUniformLocation( name.c_str() );
  assert( location != -1 );

  ShaderProgram::setFloat2( location, value.x, value.y );
}

void ShaderProgram::setMat4( int parameterIndex, const glm::mat4& matrix )
{
  //glm::mat4 colMajor = matrix.Transposed();
  glUniformMatrix4fv( parameterIndex, 1 /*count*/, GL_FALSE /*transpose*/, glm::value_ptr( matrix ) /*value*/);
}

void ShaderProgram::setDouble( int parameterIndex, double value )
{
  glUniform1d( parameterIndex, value );
}

void ShaderProgram::setFloat( int parameterIndex, float value )
{
  glUniform1f( parameterIndex, value );
}

void ShaderProgram::setFloat2( int parameterIndex, float v1, float v2 )
{
  glUniform2f( parameterIndex, v1, v2 );
}

void ShaderProgram::setFloat3( int parameterIndex, float v1, float v2, float v3 )
{
  glUniform3f( parameterIndex, v1, v2, v3 );
}

void ShaderProgram::setFloat4( int parameterIndex, float v1, float v2, float v3, float v4 )
{
  glUniform4f( parameterIndex, v1, v2, v3, v4 );
}

void ShaderProgram::setInt( int parameterIndex, int value )
{
  glUniform1i( parameterIndex, value );
}

void ShaderProgram::setInt2( int parameterIndex, int v1, int v2 )
{
  glUniform2i( parameterIndex, v1, v2 );
}

void ShaderProgram::setVectorList3( int parameterIndex, Engine::vec3* vecList, size_t size )
{
  glUniform3fv( parameterIndex, size, (const GLfloat*)vecList );
}

void
ShaderProgram::bindTexture( int index, TextureUnit& texture_unit, Texture& texture, const std::string& samplerName )
{
  assert( !( index < 0 ) );
  assert( inUse() );
  assert( texture_unit.isActive() );
  assert( texture.isBound() );
  assert( index == texture_unit.getIndex() );
  checkOpenGLError();

  GLint location = glGetUniformLocation( m_programHandle, samplerName.c_str() );
  assert( location != -1 );
  glUniform1i( location, index );
  checkOpenGLError();
}

void ShaderProgram::bindImageTexture( int index, Texture& texture, Access access, const std::string& name )
{
  GLint location = glGetUniformLocation( m_programHandle, name.c_str() );
  assert( location != -1 );

  glUniform1i( location, index );
  checkOpenGLError();
  glBindImageTexture( index, texture.getHandle(), 0, GL_FALSE, 0, toGL( access ), toGL( texture.getFormat() ) );
  checkOpenGLError();
}

void ShaderProgram::bindImageTextureRaw( int index, GLuint texture, Access access, const std::string& name )
{
 // GLint location = glGetUniformLocation( m_programHandle, name.c_str() );
 // assert( location != -1 );
 // glUniform1i( location, index );
  checkOpenGLError();
  glBindImageTexture( index, texture, 0, GL_FALSE, 0, toGL( access ), GL_R32F );
  checkOpenGLError();
}

void ShaderProgram::bindBufferTexture( int index, TextureBuffer& textureBuffer, Access access, const std::string& name )
{
  GLint location = glGetUniformLocation( m_programHandle, name.c_str() );
  assert( location != -1 );



  glUniform1i( location, index );
  checkOpenGLError();
  //glBindImageTexture( index, textureBuffer.getTextureHandle(), 0, GL_FALSE, 0, toGL( access ), toGL( textureBuffer.getTextureFormat() ) );
  //checkOpenGLError();

  glActiveTexture(GL_TEXTURE20);
  glBindTexture( GL_TEXTURE_BUFFER, textureBuffer.getTextureHandle() );
}

void
ShaderProgram::bindTextureUnit( int index, TextureUnit& texture_unit, const std::string& samplerName )
{
  assert( !( index < 0 ) );
  assert( inUse() );
  assert( index == texture_unit.getIndex() );
  checkOpenGLError();

  GLint location = glGetUniformLocation( m_programHandle, samplerName.c_str() );
  assert( location != -1 );
  glUniform1i( location, index );
  checkOpenGLError();
}

void ShaderProgram::attach( Shader& shader )
{
  assert( m_programHandle );
  glAttachShader( m_programHandle, shader.m_shaderHandle );
  checkOpenGLError();
  glLinkProgram( m_programHandle );
  checkOpenGLError();
  GLint status;
  GLchar infoLog[512];

  glGetProgramiv(m_programHandle, GL_LINK_STATUS, &status);
  if (!status) {
    glGetProgramInfoLog(m_programHandle, 512, NULL, infoLog);
    std::cout << "Shader program linking failed:\n" << infoLog << std::endl;
  }

}

void ShaderProgram::dispatch( int num_x, int num_y, int num_z )
{
  glDispatchCompute( static_cast< GLuint >( num_x ), static_cast< GLuint >( num_y ), static_cast< GLuint >( num_z ) );
  checkOpenGLError();
}

void ShaderProgram::waitForImageCompute()
{
  glMemoryBarrier( GL_SHADER_IMAGE_ACCESS_BARRIER_BIT );
  checkOpenGLError();
}

void ShaderProgram::waitForBufferCompute()
{
  glMemoryBarrier( GL_SHADER_STORAGE_BARRIER_BIT  );
  checkOpenGLError();
}

void ShaderProgram::setUniform( const Engine::vec3& v, const std::string& name )
{
  int location = getUniformLocation( name.c_str() );
  assert( location != -1 );


  ShaderProgram::setFloat3( location, v.x, v.y, v.z );
}

void ShaderProgram::setUniform( const Engine::vec4& v, const std::string& name )
{
  int location = getUniformLocation( name.c_str() );
  assert( location != -1 );


  ShaderProgram::setFloat4( location, v.x, v.y, v.z, v.a );
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


Mesh::Mesh( PrimitiveType primType ) :
  m_vao( 0 ), m_numVertices( 0 ), m_numRenderableVertices( 0 ), m_primType( primType )
{
  glGenVertexArrays( 1, &m_vao );
  checkOpenGLError();
}


Mesh::~Mesh()
{
  if( m_vao != 0 )
  {
    glDeleteVertexArrays( 1, &m_vao );
    checkOpenGLError();
  }
}


PrimitiveType Mesh::getPrimType() const
{
  return m_primType;
}


void Mesh::generateVAO( int startVertexOffset )
{
  assert( isBound() );

  ///determine numVertices
  {
    m_numVertices = std::numeric_limits< int >::max();

    for( auto& vb : vbs )
    {
      m_numVertices = std::min( vb->getNumVertices(), m_numVertices );
    }
  }

  m_numRenderableVertices = m_numVertices - startVertexOffset;
  checkValid();
  checkValidVBO( startVertexOffset );


  ///Fill in declaration.elements
  {
    for( auto& vb : vbs )
    {
      for( const auto& element : vb->getDeclaration().getElements() )
        m_declaration.add( element );
    }
  }


  int attr_index = 0;
  ///vbo
  for( auto& vb : vbs )
  {
    /**
			* From http://antongerdelan.net/opengl/vertexbuffers.html
			*
			* Also see http://www.arcsynthesis.org/gltut/Positioning/Tutorial%2005.html
			*/

    const VertexDeclaration& dec = vb->getDeclaration();

    vb->bind();
    assert( vb->isBound() );
    //glBindBuffer(GL_ARRAY_BUFFER, vb.m_vbo);
    //checkOpenGLError();

    int offset = 0;
    int stride = dec.stride();

    ///FIXME: Make this a NDEBUG runtime check too
    assert( startVertexOffset < vb->getLogicalBufferSizeBytes() );
    for( const auto& element : dec.getElements() )
    {

      //element.check_valid();
      glEnableVertexAttribArray( attr_index );
      if( element.getType() == VertexDataType::FLOAT )
      {
        glVertexAttribPointer( attr_index,
                               element.sizeElems(),
                               toGL( element.getType() ),
                               GL_FALSE,
                               stride,
                               ( void* ) ( startVertexOffset + offset ) );
      }
      else
      {
        glVertexAttribIPointer( attr_index,
                                element.sizeElems(),
                                toGL( element.getType() ),
                                stride,
                                ( void* ) ( startVertexOffset + offset ) );
      }

      checkOpenGLError();


      offset += element.sizeBytes();
      ++attr_index;
    }


  }

  for( int i = 0; i < attr_index; ++i )
  {
    glEnableVertexAttribArray (i);
    checkOpenGLError();
  }

  ///indices
  if( ib )
  {
    /**
			* From http://www.opengl.org/wiki/Vertex_Specification#Index_buffers
			*
			*
			* Indexed rendering, as defined above, requires an array of indices;
			* all vertex attributes will use the same index from this index array.
			* The index array is provided by a Buffer Object bound to the
			* GL_ELEMENT_ARRAY_BUFFER​ binding point. When a buffer is bound to
			* GL_ELEMENT_ARRAY_BUFFER​, all rendering commands of the form
			* gl*Draw*Elements*​ will use indexes from that buffer. Indices can be
			* unsigned bytes, unsigned shorts, or unsigned ints.
			*/
    ib->bind();
    assert( ib->isBound() );
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ib->m_indexBuffer);
    checkOpenGLError();
  }


		unbind();
		VertexBuffer::unbindAll();

		if (ib)
		ib->unbind();

		bind();

}


void Mesh::linkShaders()
{
  if( !sp )
  {
    throw std::runtime_error( "Mesh.LinkShaders(): No shader program; no shaders to link" );
  }

  assert( isBound() );

  GLint programHandle = sp->getHandle();

  int attr_index = 0;

  for( auto& vb : vbs )
  {
    const VertexDeclaration& dec = vb->getDeclaration();

    for( const auto& element : dec.getElements() )
    {
      const std::string& attribute_name = element.getName();
      glBindAttribLocation( programHandle, attr_index, attribute_name.c_str() );
      checkOpenGLError();
      ++attr_index;
    }
  }

  glLinkProgram( programHandle );
  checkOpenGLError();
}


void Mesh::bind()
{
  checkOpenGLError();
  if( m_vao == 0 )
    throw std::runtime_error( "Can't bind the mesh: no VAO" );

  glBindVertexArray( m_vao );
  checkOpenGLError();
  assert( isBound() );
}

void Mesh::unbind()
{
  checkOpenGLError();
  glBindVertexArray( 0 );
  checkOpenGLError();
}

void Mesh::unbindAll()
{
  checkOpenGLError();
  glBindVertexArray( 0 );
  checkOpenGLError();
}

bool Mesh::isBound() const
{
  checkOpenGLError();
  GLint boundvao = 0;
  glGetIntegerv( GL_VERTEX_ARRAY_BINDING, &boundvao );
  checkOpenGLError();
  return boundvao != 0 && boundvao == m_vao;
}

void Mesh::draw( int numIndices, int startIndexOffset )
{
  assert( isBound() );
  checkOpenGLError();
  checkValid();

  if( m_vao == 0 )
    throw std::runtime_error( "Can't render the mesh: no VAO" );

  if( ib )
  {
    assert( ib->isBound() );

    int index_count = ib->getNumIndices();

    if( numIndices == -1 )
      numIndices = index_count - startIndexOffset;


    if( startIndexOffset + numIndices > index_count )
      throw std::runtime_error(
        "Can't render the mesh: startIndexOffset/numIndices lie outside the range of possible indices" );


    ///FIXME: need to get a primitve count based on the primitive type
 //   assert( getPrimType() == PrimitiveType::TriangleList );

    /*
			GLenum data_type = 0;
			switch (ib->getIndexType())
			{
			case(PrimitiveIndexType::IndicesNone):
			throw std::runtime_error("IndexBuffer has no index type specified");
			case(PrimitiveIndexType::Indices8Bit):
			data_type = GL_UNSIGNED_BYTE;
			break;
			case(PrimitiveIndexType::Indices16Bit):
			data_type = GL_UNSIGNED_SHORT;
			break;
			case(PrimitiveIndexType::Indices32Bit):
			data_type = GL_UNSIGNED_INT;
			break;
			default:
			assert(false);

			}
			*/

    //GLint bound_buff;

    //glGetIntegerv(GL_ELEMENT_ARRAY_BUFFER_BINDING, &bound_buff);

    //printf("%i\n", bound_buff);
    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ib->m_indexBuffer);
    //printf("%i\n", index_count - startIndexOffset);

    //std::cout << "numIndices" << numIndices << ", startIndexOffset: " << startIndexOffset
    //    << ", ib->IndexType(): " << toGLSTR(ib->IndexType()) << std::endl;
    glDrawElements( GL_TRIANGLES, numIndices, toGL( ib->getIndexType() ), ( void* ) startIndexOffset );
    checkOpenGLError();

  }
  else
  {
    switch( getPrimType() )
    {
      case PrimitiveType::TriangleList:
        glDrawArrays( GL_TRIANGLES, startIndexOffset, m_numVertices );
        checkOpenGLError();
        break;
      case PrimitiveType::LineList:
        glDrawArrays( GL_LINES, 0, m_numVertices );
        checkOpenGLError();
        break;
      case PrimitiveType::Point:
        glDrawArrays( GL_POINTS, 0, m_numVertices );
        checkOpenGLError();
        break;
      case PrimitiveType::TriangleStrip:
        glDrawArrays( GL_TRIANGLE_STRIP, 0, m_numVertices );
        checkOpenGLError();
        break;
      default:
      {
        assert( false );
      }
    }
  }

}


template< typename index_t >
void Mesh::_checkIndexBounds( int numIndices, int startIndexOffset ) const
{

  if( !ib )
    return;

  if( numIndices == -1 )
    numIndices = ib->getNumIndices();

  if( startIndexOffset + numIndices > ib->getNumIndices() )
    throw std::runtime_error( "requesting check for indices that do not exist in the buffer" );

  const index_t* begin = reinterpret_cast<const index_t*>(ib->getCpuPtr());

  const index_t* it = begin;
  const index_t* end = begin + numIndices;

  it += startIndexOffset;


  for( ; it != end; ++it )
  {
    const index_t& index = *it;

    //std::cout << "index: " << index
    //    << ", numIndices: " << numIndices
    //    << ", m_numRenderableVertices: " << m_numRenderableVertices
    //    << std::endl;
    if( !( index < m_numRenderableVertices ) )
      throw std::runtime_error( "Index out of range" );
  }

}


void Mesh::checkIndexBounds( int numIndices, int startIndexOffset ) const
{

  if( !ib )
    return;

  if( ib->getIndexType() == PrimitiveIndexType::Indices8Bit )
    _checkIndexBounds< uint8_t >( numIndices, startIndexOffset );
  else if( ib->getIndexType() == PrimitiveIndexType::Indices16Bit )
    _checkIndexBounds< uint16_t >( numIndices, startIndexOffset );
  else if( ib->getIndexType() == PrimitiveIndexType::Indices32Bit )
    _checkIndexBounds< uint32_t >( numIndices, startIndexOffset );
  else
    assert( false );

}


void Mesh::checkValidVBO( int startVertexOffset ) const
{

  if( !( startVertexOffset < m_numVertices ) )
  {
    throw std::runtime_error( "cannot start with a vertex offset greater than the number of vertices" );
  }

  /*	if (!ib)
		{
			if (m_numRenderableVertices % 3 != 0)
				throw std::runtime_error("empty index buffer, but vbo has a non-divisible-by-3 length");
		}*/
}

void Mesh::checkValid() const
{
  if( ib )
  {
    if( ib->getIndexType() == PrimitiveIndexType::IndicesNone )
      throw std::runtime_error( "Invalid Mesh: Index Buffer does not have a valid index type" );
  }

  if( vbs.size() == 0 )
    throw std::runtime_error( "Invalid Mesh: no Vertex Buffer" );


  /*
		BOOST_FOREACH(const VertexBuffer& vb, vbs | indirected)
		{
		if (vb.GpuSizeInBytes() < vb.LogicalBufferSizeBytes())
		throw std::runtime_error("Invalid Mesh: GPU side of VertexBuffer does not have enough memory");
		}
		*/
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
	Input::Input(GLFWwindow* window)
	: m_pWindow(window)
	{
	}


	Input::~Input(void)
	{
	}


	int Input::keyHeld(int key)
	{
	return glfwGetKey(m_pWindow, key);
	}


	void Input::poll()
	{
	glfwPollEvents();
	}
	*/

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


PixelBuffer::PixelBuffer( Usage usage, std::size_t bytes, bool allocateCpu ) :
  m_pbo( 0 ), m_usage( usage ), m_logicalBytes( bytes )
{
  /// READ THIS:
  ///https://developer.apple.com/library/mac/documentation/GraphicsImaging/Conceptual/OpenGL-MacProgGuide/opengl_texturedata/opengl_texturedata.html

  glGenBuffers( 1, &m_pbo );
  checkOpenGLError();

  if( allocateCpu )
    allocateCpuMemory();
}


PixelBuffer::~PixelBuffer()
{
  if( m_pbo )
    glDeleteBuffers( 1, &m_pbo );
  m_pbo = 0;
}

int PixelBuffer::getLogicalBufferSizeBytes() const
{
  return m_logicalBytes;
}

void PixelBuffer::bind()
{
  checkOpenGLError();
  glBindBuffer( GL_PIXEL_UNPACK_BUFFER, m_pbo );
  checkOpenGLError();
  assert( isBound() );
}

void PixelBuffer::unbind()
{
  PixelBuffer::unbindAll();
}

void PixelBuffer::unbindAll()
{
  checkOpenGLError();
  glBindBuffer( GL_PIXEL_UNPACK_BUFFER, 0 );
  checkOpenGLError();
}

bool PixelBuffer::isBound() const
{
  checkOpenGLError();
  GLint boundpbo = 0;
  glGetIntegerv( GL_PIXEL_UNPACK_BUFFER_BINDING, &boundpbo );
  checkOpenGLError();
  return boundpbo != 0 && boundpbo == m_pbo;
}

void PixelBuffer::allocateCpuMemory()
{
  int bytes = getLogicalBufferSizeBytes();

  if( !m_cpuData )
  {
    m_cpuData = std::make_shared< CpuData >( bytes );
  }
  else
  {
    m_cpuData->resize( bytes );
  }
}

void PixelBuffer::allocateGpuMemory()
{
  assert( m_pbo );
  assert( isBound() );
  checkOpenGLError();


  int bytes = getLogicalBufferSizeBytes();

  ///Create and initialize the data store of the buffer object by calling the function glBufferData
  glBufferData( GL_PIXEL_UNPACK_BUFFER, bytes, 0, toGL( m_usage ) );
  checkOpenGLError();
  m_gpuSize = bytes;

}


void PixelBuffer::updateToGpu( const uint8_t* data, int bytes )
{
  assert( m_pbo );
  assert( isBound() );
  checkOpenGLError();

  if( !data && !m_cpuData )
  {
    throw std::runtime_error( "no cpu data to send to gpu" );
  }

  if( !data )
  {
    data = m_cpuData->data();
    bytes = m_cpuData->size();
  }

  assert( bytes == getLogicalBufferSizeBytes() );

  glBufferData( GL_PIXEL_UNPACK_BUFFER, bytes, data, toGL( m_usage ) );
  checkOpenGLError();

  m_gpuSize = bytes;
}


Texture::Texture( TextureType texture_type, TextureInternalFormat internalFormat, ResourceUsage usage, int width,
                  int height, int depth, int mipmaps, int rowalignment ) :
  m_tex( 0 ),
  m_textureType( texture_type ),
  m_internalFormat( internalFormat ),
  m_usage( usage ),
  m_width( width ),
  m_height( height ),
  m_depth( depth ),
  m_rowalignment( rowalignment ),
  m_mipmaps( mipmaps )
{
  assert( width > 0 );
  assert( height > 0 );
  assert( depth > 0 );
  checkOpenGLError();
  glGenTextures( 1, &m_tex );

  assert( m_mipmaps > 0 );
  bind();

 // glTexParameteri( toGL( m_textureType ), GL_TEXTURE_MIN_FILTER, GL_LINEAR );
 // glTexParameteri( toGL( m_textureType ), GL_TEXTURE_MAG_FILTER, GL_LINEAR );
 // glTexParameteri( toGL( m_textureType ), GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE );
//  glTexParameteri( toGL( m_textureType ), GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE );

  if( texture_type != TextureType::TextureCubeMap )
  {
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER );
    float borderColor[] = { 1.0, 1.0, 1.0, 1.0 };
    glTexParameterfv( GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor );
  }
  else
  {
    // todo: gross
    glTexParameteri( GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
    glTexParameteri( GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
    glTexParameteri( GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE );
    glTexParameteri( GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE );
    glTexParameteri( GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE );
  }



  if( _getRowAlignment() != rowalignment )
  {
    _setRowAlignment( rowalignment );
  }

  if( m_usage == ResourceUsage::UsageImmutable )
  {
    _initializeImmutableStorage();
  }

  checkOpenGLError();
}

void Texture::_initializeImmutableStorage()
{
  assert( isBound() );
  assert( m_width > 0 );
  assert( m_height > 0 );
  assert( m_depth > 0 );
  checkOpenGLError();

  ///see decription of https://www.opengl.org/sdk/docs/man/html/glGetTexImage.xhtml
  if( m_textureType == TextureType::Texture1D )
  {


    glTexStorage1D( toGL( m_textureType ),
                    m_mipmaps,
                    toGL( m_internalFormat ),
                    m_width );
    assert( m_height == 1 && m_depth == 1 );
  }
  else if( m_textureType == TextureType::Texture2D || m_textureType == TextureType::Texture1DArray
           || m_textureType == TextureType::TextureRectangle || m_textureType == TextureType::TextureCubeMap )
  {

    glTexStorage2D( toGL( m_textureType ),
                    m_mipmaps,
                    toGL( m_internalFormat ),
                    m_width,
                    m_height );

    assert( m_depth == 1 );
  }
  else if( m_textureType == TextureType::Texture3D || m_textureType == TextureType::Texture2DArray ||
           m_textureType == TextureType::TextureCubeMapArray )
  {
    glTexStorage3D( toGL( m_textureType ),
                    m_mipmaps,
                    toGL( m_internalFormat ),
                    m_width,
                    m_height,
                    m_depth );
  }
  else
  {
    assert( false );
  }

  checkOpenGLError();
}

Texture::~Texture()
{
  if( m_tex )
    glDeleteTextures( 1, &m_tex );
  m_tex = 0;
}

void Texture::bind()
{
  checkOpenGLError();
  glBindTexture( toGL( m_textureType ), m_tex );
  checkOpenGLError();
}


void Texture::unbind()
{
  checkOpenGLError();
  glBindTexture( toGL( m_textureType ), 0 );
  checkOpenGLError();
}

bool Texture::isBound() const
{
  checkOpenGLError();
  GLint boundtex = 0;
  glGetIntegerv( toGLBinding( m_textureType ), &boundtex );
  checkOpenGLError();
  return boundtex != 0 && boundtex == m_tex;
}

int Texture::getHeight() const
{
  return m_height;
}

int Texture::getWidth() const
{
  return m_width;
}


int Texture::_getRowAlignment()
{
  assert( isBound() );

  GLint rowalignment = 0;
  checkOpenGLError();
  glGetIntegerv( GL_UNPACK_ALIGNMENT, &rowalignment );
  checkOpenGLError();
  return rowalignment;
}

void Texture::_setRowAlignment( int alignment )
{
  assert( isBound() );
  ///https://www.opengl.org/wiki/Common_Mistakes#Texture_upload_and_pixel_reads
  ///The GL_PACK/UNPACK_ALIGNMENTs can only be 1, 2, 4, or 8. So an alignment of 3 is not allowed.
  assert( ( alignment == 1 || alignment == 2 || alignment == 4 || alignment == 8 ) &&
          "The GL_PACK/UNPACK_ALIGNMENTs can only be 1, 2, 4, or 8." );
  checkOpenGLError();

  glPixelStorei( GL_UNPACK_ALIGNMENT, alignment );
  checkOpenGLError();
}

void Texture::updateToGpu( int width, int height, int depth, TextureFormat textureFormat, const uint8_t* data,
                           size_t dataBytesSize, int level, const std::string& debugName )
{
  if( m_usage == ResourceUsage::UsageImmutable )
  {
    this->_immutableUpdateToGpu( width, height, depth, textureFormat, data, dataBytesSize, level, 0, 0, 0, debugName );
  }
  else
  {

    this->_mutableUpdateToGpu( width, height, depth, textureFormat, data, dataBytesSize, level, debugName );
  }
}


void Texture::updateToGpuOffset( int width, int height, int depth, TextureFormat textureFormat, const uint8_t* data,
                                 size_t dataBytesSize, int level, int offX, int offY, int offZ )
{
  std::string debugName = "";
  if( m_usage == ResourceUsage::UsageImmutable )
  {
    this->_immutableUpdateToGpu( width, height, depth, textureFormat, data, dataBytesSize, level, offX, offY, offZ, debugName );
  }
  else
  {

    this->_mutableUpdateToGpu( width, height, depth, textureFormat, data, dataBytesSize, level, debugName );
  }
}



void Texture::_immutableUpdateToGpu( int width, int height, int depth, TextureFormat textureFormat, const uint8_t* data,
                                     size_t dataBytesSize, int level,
                                     int offX, int offY, int offZ, const std::string& debugName )
{
  ///https://www.opengl.org/wiki/Common_Mistakes#Creating_a_complete_texture

  assert( width > 0 );
  assert( height > 0 );
  assert( depth > 0 );

  assert( isBound() );
  assert( data );
  assert( m_rowalignment == _getRowAlignment() );
  checkOpenGLError();


  assert( logicalSizeBytes( width, height, depth, textureFormat, m_rowalignment ) == dataBytesSize );

  int border = 0;

  ///see decription of https://www.opengl.org/sdk/docs/man/html/glGetTexImage.xhtml
  if( m_textureType == TextureType::Texture1D )
  {

    glTexSubImage1D( toGL( m_textureType ),
                     level,
                     offX, width,
                     toGL( textureFormat.pixelformat ),
                     toGL( textureFormat.elementtype ),
                     data );

    assert( height == 1 && depth == 1 );
  }
  else if( m_textureType == TextureType::Texture2D || m_textureType == TextureType::Texture1DArray
           || m_textureType == TextureType::TextureRectangle || m_textureType == TextureType::TextureCubeMap )
  {

    glTexSubImage2D( toGL( m_textureType ),
                     level,
                     offX, offY, width, height,
                     toGL( textureFormat.pixelformat ),
                     toGL( textureFormat.elementtype ),
                     data );

    assert( depth == 1 );
  }
  else if( m_textureType == TextureType::Texture3D || m_textureType == TextureType::Texture2DArray ||
           m_textureType == TextureType::TextureCubeMapArray )
  {

    glTexSubImage3D( toGL( m_textureType ),
                     level,
                     offX, offY, offZ, width, height, depth,
                     toGL( textureFormat.pixelformat ),
                     toGL( textureFormat.elementtype ),
                     data );
  }
  else
  {
    assert( false );
  }
  checkOpenGLError();

}

void Texture::_mutableUpdateToGpu( int width, int height, int depth, TextureFormat textureFormat, const uint8_t* data,
                                   size_t dataBytesSize, int level, const std::string& debugName )
{
  ///https://www.opengl.org/wiki/Common_Mistakes#Creating_a_complete_texture

  assert( width > 0 );
  assert( height > 0 );
  assert( depth > 0 );

  assert( isBound() );
 // assert( data );
  assert( m_rowalignment == _getRowAlignment() );
  checkOpenGLError();

//  assert( logicalSizeBytes( width, height, depth, textureFormat, m_rowalignment ) == dataBytesSize );

  int border = 0;

  ///see decription of https://www.opengl.org/sdk/docs/man/html/glGetTexImage.xhtml
  if( m_textureType == TextureType::Texture1D )
  {

    glTexImage1D( GL_TEXTURE_1D, level, toGL( m_internalFormat ), width, border, toGL( textureFormat.pixelformat ),
                  toGL( textureFormat.elementtype ), data );

    assert( height == 1 && depth == 1 );
  }
  else if( m_textureType == TextureType::Texture2D || m_textureType == TextureType::Texture1DArray
           || m_textureType == TextureType::TextureRectangle || m_textureType == TextureType::TextureCubeMap )
  {
    glTexImage2D( toGL( m_textureType ), level, toGL( m_internalFormat ), width, height, border,
                  toGL( textureFormat.pixelformat ), toGL( textureFormat.elementtype ), data );


    assert( depth == 1 );
  }
  else if( m_textureType == TextureType::Texture3D || m_textureType == TextureType::Texture2DArray ||
           m_textureType == TextureType::TextureCubeMapArray )
  {

    std::cout << level << " " << width << " " << height << " " << depth << "\n";

    glTexImage3D( toGL( m_textureType ), level, toGL( m_internalFormat ), width, height, depth, border,
                  toGL( textureFormat.pixelformat ), toGL( textureFormat.elementtype ), data );
  }
  else
  {
    assert( false );
  }

  checkOpenGLError();

}

void Texture::genMipmaps()
{
  assert( isBound() );
  assert( m_mipmaps > 0 );
  checkOpenGLError();

  if( m_mipmaps > 1 )
  {
    glGenerateMipmap( toGL( m_textureType ) );
    checkOpenGLError();
  }
}

TextureInternalFormat Texture::getFormat() const
{
  return m_internalFormat;
}

GLuint Texture::getHandle() const
{
  return m_tex;
}

int Texture::logicalSizeBytes( int width, int height, int depth, TextureFormat format, int rowalignment )
{
  assert( width > 0 );
  assert( height > 0 );
  assert( depth > 0 );

  ///https://www.opengl.org/wiki/Common_Mistakes#Texture_upload_and_pixel_reads
  ///The GL_PACK/UNPACK_ALIGNMENTs can only be 1, 2, 4, or 8. So an alignment of 3 is not allowed.
  assert( ( rowalignment == 1 || rowalignment == 2 || rowalignment == 4 || rowalignment == 8 ) &&
          "The GL_PACK/UNPACK_ALIGNMENTs can only be 1, 2, 4, or 8." );

  int baserowsize = width * toGLCount( format.pixelformat ) * toGLBytes( format.elementtype );
  int unalignedbytes = baserowsize % rowalignment;
  int alignmentadjustment = ( rowalignment - unalignedbytes ) % rowalignment;

  int alignedrowsize = baserowsize + alignmentadjustment;

  std::cout << "\n";
  std::cout << baserowsize << "|" << "\n";
  std::cout << unalignedbytes << "|" << "\n";
  std::cout << alignmentadjustment << "|" << "\n";

  return alignedrowsize * height * depth;
}


///http://www.geeks3d.com/20110908/opengl-3-3-sampler-objects-control-your-texture-units/
TextureSampler::TextureSampler() :
  addressU( TextureAddressMode::TextureAddressWrap ),
  addressV( TextureAddressMode::TextureAddressWrap ),
  addressW( TextureAddressMode::TextureAddressWrap ),
  minFilter( TextureFilterMode::Linear ),
  mipFilter( TextureFilterMode::Linear ),
  magFilter( TextureFilterMode::Linear ),
  m_smplr( 0 )
{


  checkOpenGLError();
  glGenSamplers( 1, &m_smplr );
  checkOpenGLError();
  generateParams();

}

TextureSampler::~TextureSampler()
{
  if( m_smplr )
    glDeleteSamplers( 1, &m_smplr );
  m_smplr = 0;
}


GLuint TextureSampler::getHandle() const
{
  return m_smplr;
}

void TextureSampler::setTextureAddressModeU( const TextureAddressMode& addressMode )
{
  addressU = addressMode;
  glSamplerParameteri( m_smplr, GL_TEXTURE_WRAP_S, toGL( addressU ) );
}

void TextureSampler::setTextureAddressModeV( const TextureAddressMode& addressMode )
{
  addressV = addressMode;
  glSamplerParameteri( m_smplr, GL_TEXTURE_WRAP_T, toGL( addressV ) );
}

void TextureSampler::setTextureAddressModeW( const TextureAddressMode& addressMode )
{
  addressW = addressMode;
  glSamplerParameteri( m_smplr, GL_TEXTURE_WRAP_R, toGL( addressW ) );
}

void TextureSampler::setTextureMinFilterMode( const TextureFilterMode& filterMode )
{
  minFilter = filterMode;
  glSamplerParameteri( m_smplr, GL_TEXTURE_MIN_FILTER, toGL( minFilter ) );
}

void TextureSampler::setTextureMipFilterMode( const TextureFilterMode& filterMode )
{
  mipFilter = filterMode;
//  glSamplerParameteri( m_smplr, GL_TEXTURE_MIP_FILTER, toGL( mipFilter ) );
}

void TextureSampler::setTextureMagFilterMode( const TextureFilterMode& filterMode )
{
  magFilter = filterMode;
  glSamplerParameteri( m_smplr, GL_TEXTURE_MAG_FILTER, toGL( magFilter ) );
}

void TextureSampler::generateParams()
{
  std::set< TextureFilterMode > minfilters;

  minfilters.insert( TextureFilterMode::Nearest );
  minfilters.insert( TextureFilterMode::Linear );
  minfilters.insert( TextureFilterMode::NearestMipmapNearest );
  minfilters.insert( TextureFilterMode::LinearMipmapNearest );
  minfilters.insert( TextureFilterMode::NearestMipmapLinear );
  minfilters.insert( TextureFilterMode::LinearMipmapLinear );

  std::set< TextureFilterMode > magfilters;
  magfilters.insert( TextureFilterMode::Nearest );
  magfilters.insert( TextureFilterMode::Linear );

  assert( minfilters.count( minFilter ) && "minFilter is not valid" );
  assert( magfilters.count( magFilter ) && "magFilter is not valid" );

  checkOpenGLError();
  glSamplerParameteri( m_smplr, GL_TEXTURE_WRAP_S, toGL( addressU ) );
  glSamplerParameteri( m_smplr, GL_TEXTURE_WRAP_T, toGL( addressV ) );
  glSamplerParameteri( m_smplr, GL_TEXTURE_WRAP_R, toGL( addressW ) );
  glSamplerParameteri( m_smplr, GL_TEXTURE_MAG_FILTER, toGL( magFilter ) );
  glSamplerParameteri( m_smplr, GL_TEXTURE_MIN_FILTER, toGL( minFilter ) );
  checkOpenGLError();


}


TextureUnit::TextureUnit( int index ) :
  m_index( index )
{
  static const int max_texture_units = getMaxTextureUnits();
  assert( m_index < max_texture_units );
}


TextureUnit::~TextureUnit()
{
  glBindSampler( getIndex(), 0 );
}

void TextureUnit::bindSampler( const TextureSampler& sampler )
{
  checkOpenGLError();
  glBindSampler( getIndex(), sampler.getHandle() );
  checkOpenGLError();
}

void TextureUnit::unbindSampler()
{
  checkOpenGLError();
  glBindSampler( getIndex(), 0 );
  checkOpenGLError();
}

int TextureUnit::getIndex() const
{
  return m_index;
}


void TextureUnit::activate()
{
  checkOpenGLError();
  glActiveTexture( GL_TEXTURE0 + getIndex() );
  checkOpenGLError();
}

bool TextureUnit::isActive() const
{
  GLint active = 0;
  checkOpenGLError();
  glGetIntegerv( GL_ACTIVE_TEXTURE, &active );
  checkOpenGLError();

  return active == GL_TEXTURE0 + getIndex();
}

int TextureUnit::getMaxTextureUnits()
{
  GLint result = 0;
  checkOpenGLError();
  glGetIntegerv( GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS, &result );
  checkOpenGLError();
  return result;
}


#define FOURCC_DXT1 0x31545844 // Equivalent to "DXT1" in ASCII
#define FOURCC_DXT3 0x33545844 // Equivalent to "DXT3" in ASCII
#define FOURCC_DXT5 0x35545844 // Equivalent to "DXT5" in ASCII

#if 0
                                                                                                                        void Texture::loadDDS(const char * imagepath)
	{

		unsigned char header[124];

		FILE *fp;

		/* try to open the file */
		fp = fopen(imagepath, "rb");
		if (fp == NULL)
		{
			throw std::runtime_error("Image path could not be opened. Are you in the right directory ?");
		}

		/* verify the type of file */
		char filecode[4];
		fread(filecode, 1, 4, fp);
		if (strncmp(filecode, "DDS ", 4) != 0) {
			fclose(fp);
			throw std::runtime_error("No valid DDS header");
		}

		/* get the surface desc */
		fread(&header, 124, 1, fp);

		m_height = *(unsigned int*) &(header[8]);
		m_width = *(unsigned int*) &(header[12]);
		unsigned int linearSize = *(unsigned int*) &(header[16]);
		unsigned int mipMapCount = *(unsigned int*) &(header[24]);
		unsigned int fourCC = *(unsigned int*) &(header[80]);


		unsigned char * buffer;
		unsigned int bufsize;
		/* how big is it going to be including all mipmaps? */
		bufsize = mipMapCount > 1 ? linearSize * 2 : linearSize;
		buffer = (unsigned char*) malloc(bufsize * sizeof(unsigned char));
		fread(buffer, 1, bufsize, fp);
		/* close the file pointer */
		fclose(fp);

		unsigned int components = (fourCC == FOURCC_DXT1) ? 3 : 4;
		unsigned int format;
		switch (fourCC)
		{
		case FOURCC_DXT1:
			format = GL_COMPRESSED_RGBA_S3TC_DXT1_EXT;
			break;
		case FOURCC_DXT3:
			format = GL_COMPRESSED_RGBA_S3TC_DXT3_EXT;
			break;
		case FOURCC_DXT5:
			format = GL_COMPRESSED_RGBA_S3TC_DXT5_EXT;
			break;
		default:
			free(buffer);
			throw std::runtime_error("Unknown DXT type.");
		}

		// Create one OpenGL texture
		GLuint textureID;
		glGenTextures(1, &textureID);

		// "Bind" the newly created texture : all future texture functions will modify this texture
		glBindTexture(GL_TEXTURE_2D, textureID);
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

		unsigned int blockSize = (format == GL_COMPRESSED_RGBA_S3TC_DXT1_EXT) ? 8 : 16;
		unsigned int offset = 0;

		unsigned int height = m_height;
		unsigned int width = m_width;

		/* load the mipmaps */
		for (unsigned int level = 0; level < mipMapCount && (m_width || m_height); ++level)
		{
			unsigned int size = ((width + 3) / 4)*((height + 3) / 4)*blockSize;
			glCompressedTexImage2D(GL_TEXTURE_2D, level, format, width, height,
				0, size, buffer + offset);

			offset += size;
			width /= 2;
			height /= 2;

			// Deal with Non-Power-Of-Two textures. This code is not included in the webpage to reduce clutter.
			if (width < 1)
				width = 1;
			if (height < 1)
				height = 1;

		}

		free(buffer);

		m_textureHandle = textureID;


	}
#endif

void clearBindings()
{

  Mesh::unbindAll();
  //Texture::UnBindAll();
  VertexBuffer::unbindAll();
  IndexBuffer::unbindAll();
  PixelBuffer::unbindAll();
  ShaderProgram::deselectAll();
}

ShaderProgramPtr defaultShader()
{
  static ShaderProgramPtr sp;
  if( !sp )
  {
    ShaderPtr vs = std::make_shared< Shader >( ShaderType::VertexShader );
    const char* vertex_shader =
      "#version 400\n"
      "uniform mat4 world;"
      "uniform mat4 worldViewProj;"
      "layout(location = 0) in vec3 vertex_position;\n"
      "layout(location = 1) in vec3 vertex_colour;\n"
      "\n"
      "out vec3 colour;\n"

      "void main () {\n"
      "  colour = vertex_colour;\n"
      "  gl_Position =  worldViewProj * world * vec4 (vertex_position, 1.0);\n"
      "}\n";

    vs->loadFromString( ShaderType::VertexShader, vertex_shader );

    ShaderPtr ps = std::make_shared< Shader >( ShaderType::PixelShader );

    const char* fragment_shader =
      "#version 400\n"
      "in vec3 colour;\n"
      "out vec4 frag_colour;\n"
      "\n"
      "void main () {\n"
      "  frag_colour = vec4 (colour, 1.0);\n"
      "}\n";

    ps->loadFromString( ShaderType::PixelShader, fragment_shader );

    sp = std::make_shared< ShaderProgram >();
    sp->attach( *vs );
    sp->attach( *ps );

  }
  return sp;
}


ShaderProgramPtr defaultSSPCWhiteShader()
{
  static ShaderProgramPtr sp;
  if( !sp )
  {
    ShaderPtr vs = std::make_shared< Shader >( ShaderType::VertexShader );

    const char* vertex_shader =
      "#version 400\n"
      //"uniform mat4 world;"
      //"uniform mat4 worldViewProj;"
      "layout(location = 0) in vec2 vertex_position;\n"
      "\n"
      "void main () {\n"
      "  gl_Position =  vec4(vertex_position.xy,0,1);\n"
      "}\n";

    vs->loadFromString( ShaderType::VertexShader, vertex_shader );

    ShaderPtr ps = std::make_shared< Shader >( ShaderType::PixelShader );
    const char* fragment_shader =
      "#version 400\n"
      "out vec4 frag_colour;\n"
      "\n"
      "void main () {\n"
      "  frag_colour = vec4 (1,1,1, 1.0);\n"
      "}\n";

    ps->loadFromString( ShaderType::PixelShader, fragment_shader );

    sp = std::make_shared< ShaderProgram >();
    sp->attach( *vs );
    sp->attach( *ps );

  }
  return sp;
}

ShaderProgramPtr defaultWhiteShader()
{
  static ShaderProgramPtr sp;
  if( !sp )
  {
    ShaderPtr vs = std::make_shared< Shader >( ShaderType::VertexShader );

    const char* vertex_shader =
      "#version 400\n"
      "uniform mat4 world;"
      "uniform mat4 worldViewProj;"
      "layout(location = 0) in vec3 vertex_position;\n"
      "\n"
      "out vec3 colour;\n"

      "void main () {\n"
      "  colour = vec3(1,1,1);\n"
      "  gl_Position =  worldViewProj * world * vec4 (vertex_position, 1.0);\n"
      "}\n";

    vs->loadFromString( ShaderType::VertexShader, vertex_shader );

    ShaderPtr ps = std::make_shared< Shader >( ShaderType::PixelShader );
    const char* fragment_shader =
      "#version 400\n"
      "in vec3 colour;\n"
      "out vec4 frag_colour;\n"
      "\n"
      "void main () {\n"
      "  frag_colour = vec4 (1,1,1, 1.0);\n"
      "}\n";

    ps->loadFromString( ShaderType::PixelShader, fragment_shader );

    sp = std::make_shared< ShaderProgram >();
    sp->attach( *vs );
    sp->attach( *ps );

  }
  return sp;
}

ShaderProgramPtr defaultTextureShader()
{
  static ShaderProgramPtr sp;
  if( !sp )
  {
    ShaderPtr vs = std::make_shared< Shader >( ShaderType::VertexShader );
    const char* vertex_shader =
      "#version 400\n"
      "uniform mat4 world;"
      "uniform mat4 worldViewProj;"
      "layout(location = 0) in vec3 vertex_position;\n"
      "layout(location = 1) in vec2 texture_coord;\n"
      "\n"
      "out vec2 frag_texture_coord;\n"

      "void main () {\n"
      "  frag_texture_coord = texture_coord;\n"
      "  gl_Position =  worldViewProj * world * vec4 (vertex_position, 1.0);\n"
      "}\n";

    vs->loadFromString( ShaderType::VertexShader, vertex_shader );

    ShaderPtr ps = std::make_shared< Shader >( ShaderType::PixelShader );


    const char* fragment_shader =
      "#version 400\n"
      "\n"
      "uniform sampler2D texture1;\n"
      "\n"
      "in vec2 frag_texture_coord;\n"
      "out vec4 result_colour;\n"
      "\n"
      "void main () {\n"
      "  result_colour = texture2D(texture1, frag_texture_coord);\n"
      "}\n";

    ps->loadFromString( ShaderType::PixelShader, fragment_shader );

    sp = std::make_shared< ShaderProgram >();
    sp->attach( *vs );
    sp->attach( *ps );

  }
  return sp;
}

MeshPtr Engine::Rendering::createFullScreenQuad( ShaderProgramPtr pSp )
{
  VertexDeclaration decl;
  decl.add( VertexElement( VertexDataSemantic::VCOORD, VertexDataType::FLOAT, 3, "vertex_position" ) );

  auto mesh = std::make_shared< Mesh >( PrimitiveType::TriangleList );
  mesh->bind();

  auto pVertexBuffer = std::make_shared< VertexBuffer >( 4, decl, Usage::STATIC_DRAW );

  auto pIndexBuffer = std::make_shared< IndexBuffer >( mesh, 6, PrimitiveIndexType::Indices16Bit,
                                                       Usage::STATIC_DRAW );

  float* vbPtr = reinterpret_cast< float* >( pVertexBuffer->getCpuPtr() );
  uint16_t* ibPtr = reinterpret_cast< uint16_t* >( pIndexBuffer->getCpuPtr() );

  uint32_t offset = 0;

  vbPtr[ offset++ ] = -1.0f;
  vbPtr[ offset++ ] = 1.0f;
  vbPtr[ offset++ ] = 0.0f;

  vbPtr[ offset++ ] = -1.0f;
  vbPtr[ offset++ ] = -1.0f;
  vbPtr[ offset++ ] = 0.0f;

  vbPtr[ offset++ ] = 1.0f;
  vbPtr[ offset++ ] = -1.0f;
  vbPtr[ offset++ ] = 0.0f;

  vbPtr[ offset++ ] = 1.0f;
  vbPtr[ offset++ ] = 1.0f;
  vbPtr[ offset++ ] = 0.0f;

  pVertexBuffer->bind();
  pVertexBuffer->updateToGpu();
  offset = 0;

  ibPtr[ offset++ ] = 0;
  ibPtr[ offset++ ] = 1;
  ibPtr[ offset++ ] = 2;

  ibPtr[ offset++ ] = 0;
  ibPtr[ offset++ ] = 2;
  ibPtr[ offset++ ] = 3;

  pIndexBuffer->bind();
  pIndexBuffer->updateToGpu();

  mesh->vbs.push_back( pVertexBuffer );
  mesh->ib.swap( pIndexBuffer );

  mesh->sp = pSp;

  mesh->generateVAO();
  mesh->linkShaders();

  return mesh;

}
