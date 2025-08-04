#pragma once

#include <cstdint>

#include <cassert>

#include <glm/glm.hpp>

#include <utility>
#include <vector>
#include <memory>
#include <string>
#include "glcommon.h"
#include "GfxApiCommon.h"
#include "CommonTypes.h"

namespace Engine::Rendering
{

  struct VertexBuffer;
  struct IndexBuffer;
  struct ShaderProgram;
  struct Mesh;
  struct Texture;
  struct TextureUnit;
  struct TextureSampler;

  int checkOglError( const char* func );
  int checkOglError( const char* file, int line );

  enum class Access
  {
    ReadOnly,
    WriteOnly,
    ReadWrite
  };

  enum BufferBit
  {
    DepthBufferBit = 0x00000100,
    StencilBufferBit = 0x00000400,
    ColorBufferBit = 0x00004000
  };


  enum class Usage
  {
    STREAM_DRAW,
    STREAM_READ,
    STREAM_COPY,
    STATIC_DRAW,
    STATIC_READ,
    STATIC_COPY,
    DYNAMIC_DRAW,
    DYNAMIC_READ,
    DYNAMIC_COPY
  };

  enum class VertexDataSemantic
  {
    COLOR,
    COLOR2,
    NORMAL,
    TCOORD,
    VCOORD
  };


  enum class VertexDataType
  {
    BYTE,
    UNSIGNED_BYTE,
    UNSIGNED_SHORT,
    SHORT,
    INT,
    FLOAT,
    DOUBLE
  };

  enum class BarrierBit
  {
    AttribArray,
    ElementArray,
    Uniform,
    TextureFetch,
    ShaderImage,
    Command,
    PixelBuffer,
    TextureUpdate,
    BufferUpdate,
    Framebuffer,
    TransformFeedback,
    AtomicCounter
  };

  enum class EnableAttribute
  {
    Blend,
    ClipDistance,
    ColorLogicOp,
    CullFace,
    DebugOutput,
    DebugOutputSync,
    DepthClamp,
    DepthTest,
    Dither,
    FrameBufferSrgb,
    LineSmooth,
    MultiSample,
    PoligonOffsetFill,
    PoligonOffsetLine,
    PoligonOffsetPoint,
    PoligonSmooth,
    PrimitiveRestart,
    PrimitiveRestartFixedIndex,
    RasterizerDiscard,
    SampleAlphaToCoverage,
    SampleAlphaToOne,
    SampleCoverage,
    SampleShading,
    SampleMask,
    ScissorTest,
    StencilTest,
    TextureCubemapSeamless,
    ProgramPointSize
  };

  enum class ShaderType
  {
    NullShader,
    VertexShader,
    PixelShader,
    GeometryShader,
    ComputeShader,
  };


  enum class PrimitiveType
  {
    Point,
    LineList,
    LineStrip,
    TriangleList,
    TriangleStrip
  };


  enum class PrimitiveIndexType
  {
    IndicesNone,
    Indices8Bit,
    Indices16Bit,
    Indices32Bit
  };

  enum class ResourceUsage
  {
    UsageImmutable,
    UsageMutable
  };

  enum class TextureType
  {
    Texture1D,
    Texture1DArray,
    Texture2D,
    Texture2DArray,
    TextureRectangle,
    Texture3D,

    TextureCubeMap,
    TextureCubeMapArray
  };

  enum class TextureAddressMode
  {
    TextureAddressWrap,
    TextureAddressMirrorWrap,
    TextureAddressEdgeClamp,
    TextureAddressMirrorEdgeClamp,
    TextureAddressBorderClamp
  };

  enum class TextureFilterMode
  {
    Nearest,
    Linear,
    NearestMipmapNearest,
    LinearMipmapNearest,
    NearestMipmapLinear,
    LinearMipmapLinear
  };

  /**
  * See https://www.opengl.org/sdk/docs/man/html/glTexImage2D.xhtml
  *
  * Section describing the @c type parameter.
  */
  enum class TextureElementType
  {
    UNSIGNED_BYTE,
    BYTE,
    UNSIGNED_SHORT,
    SHORT,
    UNSIGNED_INT,
    INT,
    FLOAT,
    UNSIGNED_BYTE_3_3_2,
    UNSIGNED_BYTE_2_3_3_REV,
    UNSIGNED_SHORT_5_6_5,
    UNSIGNED_SHORT_5_6_5_REV,
    UNSIGNED_SHORT_4_4_4_4,
    UNSIGNED_SHORT_4_4_4_4_REV,
    UNSIGNED_SHORT_5_5_5_1,
    UNSIGNED_SHORT_1_5_5_5_REV,
    UNSIGNED_INT_8_8_8_8,
    UNSIGNED_INT_8_8_8_8_REV,
    UNSIGNED_INT_10_10_10_2,
    UNSIGNED_INT_2_10_10_10_REV
  };

  ///https://www.opengl.org/sdk/docs/man/html/glTexImage2D.xhtml see the section on the @c format parameter
  enum class TexturePixelFormat
  {
    RED,
    RG,
    RGB,
    BGR,
    RGBA,
    BGRA,
    RED_INTEGER,
    RG_INTEGER,
    RGB_INTEGER,
    BGR_INTEGER,
    RGBA_INTEGER,
    BGRA_INTEGER,
    STENCIL_INDEX,
    DEPTH_COMPONENT,
    DEPTH_STENCIL
  };

  ///https://www.opengl.org/sdk/docs/man/html/glTexImage2D.xhtml see the section on the @c internalFormat parameter
  enum class TextureInternalFormat
  {
    DEPTH_COMPONENT,
    DEPTH_STENCIL,
    RED,
    RG,
    RGB,
    RGBA,


    R8,
    R8_SNORM,
    R16,
    R16_SNORM,
    RG8,
    RG8_SNORM,
    RG16,
    RG16_SNORM,
    R3_G3_B2,
    RGB4,
    RGB5,
    RGB8,
    RGB8_SNORM,
    RGB10,
    RGB12,
    RGB16_SNORM,
    RGBA2,
    RGBA4,
    RGB5_A1,
    RGBA8,
    RGBA8_SNORM,
    RGB10_A2,
    RGB10_A2UI,
    RGBA12,
    RGBA16,
    SRGB8,
    SRGB8_ALPHA8,
    R16F,
    RG16F,
    RGB16F,
    RGBA16F,
    R32F,
    RG32F,
    RGB32F,
    RGBA32F,
    R11F_G11F_B10F,
    RGB9_E5,
    R8I,
    R8UI,
    R16I,
    R16UI,
    R32I,
    R32UI,
    RG8I,
    RG8UI,
    RG16I,
    RG16UI,
    RG32I,
    RG32UI,
    RGB8I,
    RGB8UI,
    RGB16I,
    RGB16UI,
    RGB32I,
    RGB32UI,
    RGBA8I,
    RGBA8UI,
    RGBA16I,
    RGBA16UI,
    RGBA32I,
    RGBA32UI,

    COMPRESSED_RED,
    COMPRESSED_RG,
    COMPRESSED_RGB,
    COMPRESSED_RGBA,
    COMPRESSED_SRGB,
    COMPRESSED_SRGB_ALPHA,
    COMPRESSED_RED_RGTC1,
    COMPRESSED_SIGNED_RED_RGTC1,
    COMPRESSED_RG_RGTC2,
    COMPRESSED_SIGNED_RG_RGTC2,
    COMPRESSED_RGBA_BPTC_UNORM,
    COMPRESSED_SRGB_ALPHA_BPTC_UNORM,
    COMPRESSED_RGB_BPTC_SIGNED_FLOAT,
    COMPRESSED_RGB_BPTC_UNSIGNED_FLOAT
  };

  enum class DepthFunc
  {
    Never,
    Less,
    Equal,
    Lequal,
    Greater,
    NotEqual,
    GEqual,
    Always
  };

  enum class BlendFunc
  {
    SrcColor,
    OneMinusSrcColor,
    SrcAlpha,
    OneMinusSrcAlpha,
    DstAlpha,
    OneMinusDstAlpha,
    DstColor,
    OneMinusDstColor,
    SrcAlphaSaturate
  };

  enum class CullMode
  {
    Front,
    Back,
    Both
  };

  enum class CullOrder
  {
    ClockWise,
    CounterClockWise
  };

  GLenum toGL( BlendFunc blendFunc );

  GLenum toGL( DepthFunc depthFunc );

  GLenum toGL( VertexDataType type );

  GLenum toGL( BarrierBit bit );

  GLenum toGL( Access access );

  GLenum toGL( Usage usage );

  GLenum toGL( TextureInternalFormat internalformat );

  GLenum toGL( TexturePixelFormat pixelformat );

  GLenum toGL( TextureElementType elementtype );

  GLenum toGL( TextureType texturetype );

  GLenum toGL( PrimitiveIndexType indextype );

  GLenum toGL( TextureFilterMode filtermode );

  GLenum toGL( TextureAddressMode addressmode );

  GLenum toGL( EnableAttribute attribute );

  GLenum toGL( CullMode cullmode );

  GLenum toGL( CullOrder cullOrder );

  GLenum toGLBinding( TextureType texturetype );

  const char* toGLSTR( PrimitiveIndexType indextype );

  struct Graphics
  {
  public:
    Graphics();

    ~Graphics();


    void initializeGlew();
    int init( const std::string& title, int screenWidth, int screenHeight, bool fullscreen, bool resizeable );

    int getWindowHeight();
    int getWindowWidth();
    Engine::ivec2 getWindowSize();

    void setWindowSize( int width, int height );
    static void setViewport( int x, int y, int width, int height );

    bool isBufferReInitRequired() const;
    void clearBufferReInit();

    std::string getDeviceString();


    static void clear( bool clearDepth = true, bool clearStencil = true, bool clearColor = true,
                       float depthValue = 1.f, int stencilValue = 0 );

    static void clearColor( float red = 0.f, float green = 0.f, float blue = 0.f, float alpha = 0.f );

    static void enableDepthWrite( bool enable );

    static void enable( EnableAttribute attrib );

    static void disable( EnableAttribute attrib );

    static void setDepthFunc( DepthFunc depthFunc );
    static void setBlendFunc( BlendFunc blendFunc1, BlendFunc blendFunc2 );

    static void setCullMode( CullMode cullmode );

    static void setCullOrder( CullOrder cullOrder );

    bool shouldWindowClose();

    bool isWindowFocused();

    void getFramebufferSize( int& width, int& height );

    static void blitFramebuffer( const Engine::ivec4& src,
                                 const Engine::ivec4& dst,
                                 int mask, TextureFilterMode filter );

    void makeContextCurrent();

    void swapBuffers();

    void terminate();

    GLFWwindow* getWindowHandle();

    uint32_t getFrameCount() const;
    void resetFrameCount();
    void increaseFrameCount();


  private:
    GLFWwindow* m_pWindow;
    std::string m_windowTitle;
    int m_windowWidth;
    int m_windowHeight;

    bool m_requireBufferInit;
    uint32_t m_frameCount{ 0 };
  };



  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


  class VertexElement
  {
  public:
    VertexElement( VertexDataSemantic semantic, VertexDataType type, int count, const std::string& name );

    ~VertexElement();

    int sizeBytes() const;

    int sizeElems() const;

    VertexDataSemantic getSemantic() const;

    VertexDataType getType() const;

    const std::string& getName() const;

    //void save_to_file(std::ostream& out);
    //void load_from_file(std::istream& in);

    //void dump_to_console();

    /**
    * Returns a string of format "(semantic): : (name) semantic: (type), count: (num)".
    */
    std::string toString() const;

  private:
    VertexDataSemantic m_semantic;
    VertexDataType m_type;
    int m_count;
    std::string m_name;

  };


  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


  class VertexDeclaration
  {
  public:
    VertexDeclaration();

    ~VertexDeclaration();

    /**
    * Adds a new data element to the end of the element list.
    */
    void add( const VertexElement& elem );

    /**
    * The size of a single vertex in the stream in bytes, including any padding.
    */
    int stride() const;

    const std::vector< VertexElement >& getElements() const;

  private:
    std::vector< VertexElement > m_elements;
  };


  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


  struct VertexBuffer
  {
  public:
    explicit VertexBuffer( int numVertices, const VertexDeclaration& dec, Usage usage, bool allocateCpu = true );

    ~VertexBuffer();

    VertexBuffer( const VertexBuffer& ) = delete;

    VertexBuffer& operator=( const VertexBuffer& ) = delete;

    using CpuData = std::vector< unsigned char >;

    int getNumVertices() const;

    //int getSizeInBytes() const;

    int getVertexSizeBytes() const;

    void setNumVertices( std::size_t size, bool perseveOldCpuData = true );

    void updateToGpu( const uint8_t* data = 0, int bytes = 0 );

    void updateToCpu( uint8_t* data = 0, int bytes = 0 );

    void allocateCpuMemory();

    void allocateGpuMemory();

    bool hasCpuMemory() const;

    bool hasGpuMemory() const;

    const VertexDeclaration& getDeclaration() const;

    VertexDeclaration& getDeclaration();

    const unsigned char* getCpuPtr() const;

    unsigned char* getCpuPtr();

    int getLogicalBufferSizeBytes() const;

    int getGpuSizeInBytes() const;

    int getCpuSizeInBytes() const;

    void bind();

    void unbind();

    bool isBound() const;

    static void unbindAll();

  private:
    int m_numVertices;
    VertexDeclaration m_declaration;
    Usage m_usage;
    GLuint m_vbo;
    int m_gpuSize;
    std::shared_ptr< CpuData > m_cpuData;

    friend struct Graphics;
    friend struct Mesh;
  };


  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


  struct IndexBuffer
  {
  public:
    typedef std::vector< unsigned char > cpu_data_t;

    explicit IndexBuffer( std::weak_ptr< Mesh > mesh, int numIndices, PrimitiveIndexType type, Usage usage,
                          bool allocateCpu = true );

    ~IndexBuffer();

    IndexBuffer( const IndexBuffer& ) = delete;

    IndexBuffer& operator=( const IndexBuffer& ) = delete;

    void updateToGpu( const uint8_t* data = 0, int bytes = 0 );

    void updateToCpu( uint8_t* data = 0, int bytes = 0 );

    void allocateCpuMemory();

    void allocateGpuMemory();

    int getNumIndices() const;

    ///Returns the size of a single index in bytes (1,2 or 4, depending on indexType).
    int getIndexSizeBytes() const;

    int getLogicalBufferSizeBytes() const;

    bool hasCpuMemory() const;

    bool hasGpuMemory() const;

    void setNumIndices( std::size_t size, bool perseveOldCpuData );

    unsigned char* getCpuPtr();

    const unsigned char* getCpuPtr() const;

    PrimitiveIndexType getIndexType() const;

    void bind();

    void unbind();

    bool isBound() const;

    bool isVAOBound() const;

    static void unbindAll();

  private:
    std::weak_ptr< Mesh > m_mesh;
    int m_numIndices;
    PrimitiveIndexType m_indexType;
    Usage m_usage;

    std::shared_ptr< cpu_data_t > m_indexData;
  public:
    GLuint m_indexBuffer;
  private:
    int m_gpuSize;

    friend struct Graphics;
    friend struct Mesh;
  };


  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  template< typename T >
  struct BindGuard
  {
    T* b;

    BindGuard( BindGuard&& o ) :
      b( std::move( o.b ) )
    {
    }

    BindGuard( T& b )
      :
      b( &b )
    {
      this->b->bind();
    }

    BindGuard( const BindGuard& ) = delete;

    BindGuard& operator=( const BindGuard& ) = delete;


    ~BindGuard()
    {
      b->unbind();
    }
  };

  template< typename T >
  BindGuard< T > make_bind_guard( T& b )
  {
    return BindGuard< T >( b );
  }

  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


  class PixelBuffer
  {
  public:
    PixelBuffer( Usage usage, std::size_t bytes, bool allocateCpu = true );

    ~PixelBuffer();

    PixelBuffer( const PixelBuffer& ) = delete;

    PixelBuffer& operator=( const PixelBuffer& ) = delete;

    //void loadDDS(const char * imagepath);
    //void loadBMP(const char * imagepath, int index);

    int getLogicalBufferSizeBytes() const;


    void bind();

    void unbind();

    static void unbindAll();

    bool isBound() const;


    unsigned char* getCpuPtr();

    const unsigned char* getCpuPtr() const;

    void allocateCpuMemory();

    void allocateGpuMemory();

    bool hasCpuMemory() const;

    bool hasGpuMemory() const;

    void updateToGpu( const uint8_t* data = 0, int bytes = 0 );

    void updateToCpu( uint8_t* data = 0, int bytes = 0 );

    /**
    * Locks the GPU buffer, and returns a pointer to the memory on the CPU.
    *
    * Must call UnMap() when reading/writing is complete.
    *
    * Allows calls to glReadPixels(), while bound, and it will not block until the
    * PBO is mapped.
    */
    //void* Map(Access access);
    //void UnMap();

  private:
    GLuint m_pbo;
    Usage m_usage;
    std::size_t m_logicalBytes;
    int m_gpuSize;

    using CpuData = std::vector< unsigned char >;

    std::shared_ptr< CpuData > m_cpuData;
  };

  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  struct Ssbo
  {
    explicit Ssbo( int size );
    ~Ssbo();

    Ssbo( const Ssbo& ) = delete;
    Ssbo& operator=( const Ssbo& ) = delete;

    void bindBuffer();
    void bindBufferBase( int index );
    void unbindBufferBase( int index );
    void unbindBuffer();
    void updateBufferData( uint8_t* data, uint32_t size );
    void updatePartialBufferData( int offset, uint8_t* data, uint32_t size );

    GLuint getHandle() const;

  private:
    GLuint m_handle;
    int m_size;
  };

  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  struct TextureBuffer
  {
    explicit TextureBuffer( int size, TextureInternalFormat internalFormat );
    ~TextureBuffer();

    TextureBuffer( const TextureBuffer& ) = delete;
    TextureBuffer& operator=( const TextureBuffer& ) = delete;

    void bindBuffer();
    void bindBufferBase( int index );
    void unbindBufferBase( int index );
    void unbindBuffer();
    void updateBufferData( uint8_t* data, uint32_t size );
    void updatePartialBufferData( int offset, uint8_t* data, uint32_t size );

    void bindTexture();

    GLuint getBufferHandle() const;
    GLuint getTextureHandle() const;

    TextureInternalFormat getTextureFormat() const;

  private:
    GLuint m_bufferHandle;
    GLuint m_textureHandle;
    TextureInternalFormat m_format;
    int m_size;
  };

  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  struct TextureUnit
  {
    TextureUnit( int index );
    ~TextureUnit();

    TextureUnit( const TextureUnit& ) = delete;
    TextureUnit& operator=( const TextureUnit& ) = delete;

    void activate();
    //void Deactivate();

    bool isActive() const;
    int getIndex() const;
    void bindSampler( const TextureSampler& sampler );
    void unbindSampler();
    static int getMaxTextureUnits();

  private:
    int m_index;
  };

  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  struct TextureSampler
  {
    TextureSampler();

    ~TextureSampler();

    TextureSampler( const TextureSampler& ) = delete;

    TextureSampler& operator=( const TextureSampler& ) = delete;

    //void Bind();
    //void UnBind();
    //bool IsBound() const;
    //static void UnBindAll();

    TextureAddressMode addressU;
    TextureAddressMode addressV;
    TextureAddressMode addressW;
    TextureFilterMode minFilter;
    TextureFilterMode mipFilter;
    TextureFilterMode magFilter;

    void generateParams();

    void setTextureAddressModeU( const TextureAddressMode& addressMode );
    void setTextureAddressModeV( const TextureAddressMode& addressMode );
    void setTextureAddressModeW( const TextureAddressMode& addressMode );

    void setTextureMinFilterMode( const TextureFilterMode& filterMode );
    void setTextureMipFilterMode( const TextureFilterMode& filterMode );
    void setTextureMagFilterMode( const TextureFilterMode& filterMode );

    GLuint getHandle() const;

  private:
    GLuint m_smplr;
  };

  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  struct TextureFormat
  {
    TextureFormat( TextureElementType elementtype, TexturePixelFormat pixelformat ) :
      elementtype( elementtype ),
      pixelformat( pixelformat )
    {
    }

    TextureElementType elementtype;
    TexturePixelFormat pixelformat;
  };

  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  struct Texture
  {
  public:
    /**
    * @param texture_type
    *      The type of texture, 1D,2D,3D/arrays etc.
    * @param internalFormat
    *      A suggestion to the GPU of the type of format to store the image in, internally, on the GPU.
    * @param usage
    *      If this texture parameters will change (they won't, because the parameters are set in the ctor).
    * @param width
    *      The width of the image; for 1D, the length of the image.
    * @param height
    *      The height of the image, for 1D, this will be 1.
    * @param depth
    *      The depth of the image, for 1D,2D, this will be 1.
    * @param mipmaps
    *      The number of mipmaps this texture will have.
    * @param rowalignment
    *      The uploaded data will have this rowalignment. See @c UpdateToGpu(). Defaults to 4.
    */
    Texture( TextureType texture_type, TextureInternalFormat internalFormat, ResourceUsage usage, int width, int height,
             int depth, int mipmaps = 1000, int rowalignment = 4 );

    ~Texture();

    Texture( const Texture& ) = delete;

    Texture& operator=( const Texture& ) = delete;

    /**
    * Set a mipmap level of the texture.
    *
    * @param textureFormat
    *      The format of the data being uploaded. The data will be stored according to the @c internal_format
    *      parameter in the ctor.
    * @param data pointer to a buffer with the data for the texture.
    *        If data is 0, then will upload from a bound pixel buffer object instead.
    * @param dataBytesSize the size of the entire buffer. This is basically rowsize*width*height,
    *        where rowsize is (sizeperpixel*width) adjusted for @c rowalignment, specified in the ctor.
    * @param level this specifies the mipmap level to upload the data for. Level 0 *must* be uploaded.
    *        Other levels are optional, depending on the @c mipmaps parameter specified in the ctor.
    *        Call @c GenMipmaps() to automatically generate the mipmaps from level 0.
    */
    void
    updateToGpu( int width, int height, int depth, TextureFormat textureFormat, const uint8_t* data, size_t dataBytesSize,
                 int level = 0, const std::string& debugName = std::string() );

    void
    updateToGpuOffset( int width, int height, int depth, TextureFormat textureFormat, const uint8_t* data, size_t dataBytesSize,
                       int level = 0, int offX = 0, int offY = 0, int offZ = 0 );

    /*
    void CreateNew( int width, int height, int depth, int numMipmaps
    , TextureType type, TextureFormat format, ResourceUsage usage
    , bool cpuReadAccess, bool cpuWriteAccess
    , const uint8_t **initialSurfaceDataArray, size_t *initialSurfaceDataByteSizes, int numInitialSurfaces
    , const char *debugName=0);
    void CreateNew( int width, int height, int depth, int numMipmaps
    , TextureType type, TextureFormat format, ResourceUsage usage
    , bool cpuReadAccess, bool cpuWriteAccess
    , const Image *initialImageArray, int numInitialImages, const char *debugName=0);
    */

    /**
    * Automatically generate mipmaps.
    */
    void genMipmaps();

    void bind();

    void unbind();

    bool isBound() const;

    static void unbindAll();

    int getHeight() const;

    int getWidth() const;

    int getDepth() const;

    TextureInternalFormat getFormat() const;

    int getNumMipmaps() const;

    //void SetNumMipmaps(int numMipLevels, bool generateNewMipLevels=true);
    int getCPUSizeBytes() const;

    int getGPUSizeBytes() const;

    void disableMipmaps();

    static int logicalSizeBytes( int width, int height, int depth, TextureFormat format, int rowalignment );

    GLuint getHandle() const;

  private:
    void _initializeImmutableStorage();

    int _getRowAlignment();

    void _setRowAlignment( int alignment );

    void _mutableUpdateToGpu( int width, int height, int depth, TextureFormat textureFormat, const uint8_t* data,
                              size_t dataBytesSize, int level, const std::string& debugName = std::string() );

    void _immutableUpdateToGpu( int width, int height, int depth, TextureFormat textureFormat, const uint8_t* data,
                                size_t dataBytesSize, int level,
                                int offX = 0, int offY = 0, int offZ = 0, const std::string& debugName = std::string() );

    GLuint m_tex;
    TextureType m_textureType;
    TextureInternalFormat m_internalFormat;
    ResourceUsage m_usage;
    int m_width, m_height, m_depth, m_rowalignment, m_mipmaps;
  };

  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


  class Shader
  {
  public:
    explicit Shader( ShaderType type, const std::string& fileName );
    explicit Shader( ShaderType type );

    ~Shader();

    Shader( const Shader& ) = delete;

    Shader& operator=( const Shader& ) = delete;

    void loadFromString( ShaderType type,
                         const char* shaderData,
                         const char* entryPoint = 0,
                         const char* profile = 0 );

    void loadFromFile( ShaderType type,
                       const char* fileName,
                       const char* entryPoint = 0,
                       const char* profile = 0 );

    std::string getSourceFromFile( const std::string& path );

    GLuint m_shaderHandle;

  private:
    ShaderType m_type;

  };


  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


  struct ShaderProgram
  {
  public:
    explicit ShaderProgram();

    ~ShaderProgram();

    ShaderProgram( const ShaderProgram& ) = delete;

    ShaderProgram& operator=( const ShaderProgram& ) = delete;

    void attach( Shader& shader );

    void dispatch( int num_x = 1, int num_y = 1, int num_z = 1 );

    void waitForImageCompute();
    void waitForBufferCompute();

    int getUniformLocation( const char* name );

    void use();

    bool inUse() const;

    void deselect();

    static void deselectAll();

    GLuint getHandle() const;

    void bindTexture( int index, TextureUnit& texture_unit, Texture& texture, const std::string& samplerName );
    void bindTextureUnit( int index, TextureUnit& texture_unit, const std::string& samplerName );
    void bindImageTexture( int index, Texture& texture, Access access, const std::string& name );
    void bindImageTextureRaw( int index, GLuint texture, Access access, const std::string& name );

    void bindBufferTexture( int index, TextureBuffer& textureBuffer, Access access, const std::string& name );

    void setUniform( const glm::mat4& matrix, const std::string& name );
    void setUniform( float value, const std::string& name );
    void setUniform( double value, const std::string& name );
    void setUniform( int value, const std::string& name );
    void setUniform( unsigned int value, const std::string& name );
    void setUniform( float v1, float v2, const std::string& name );
    void setUniform( float v1, float v2, float v3, const std::string& name );
    void setUniform( const Engine::vec3& v, const std::string& name );
    void setUniform( const Engine::vec4& v, const std::string& name );
    void setUniform( Engine::vec3* vecList, size_t size, const std::string& name );
    void setUniform( Engine::ivec2 value, const std::string& name );
    void setUniform( Engine::vec2 value, const std::string& name );

    static void setMat4( int parameterIndex, const glm::mat4& matrix );
    static void setInt( int parameterIndex, int value );
    static void setInt2( int parameterIndex, int v1, int v2 );
    static void setDouble( int parameterIndex, double value );
    static void setFloat( int parameterIndex, float value );
    static void setFloat2( int parameterIndex, float v1, const float v2 );
    static void setFloat3( int parameterIndex, float v1, float v2, float v3 );
    static void setFloat4( int parameterIndex, float v1, float v2, float v3, float v4 );
    static void setVectorList3( int parameterIndex, Engine::vec3* vecList, size_t size );

  private:
    GLuint m_programHandle;
  };


  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  /**
  * Just a container that bundles together the texture, texture unit, sampler, and shader name.
  */
  struct MeshTexture
  {
    MeshTexture( TexturePtr texture, TextureUnitPtr texture_unit, TextureSamplerPtr sampler, std::string sampler_name ) :
      texture (std::move( texture ) ),
      texture_unit( std::move( texture_unit ) ),
      sampler( std::move( sampler ) ),
      sampler_name( std::move( sampler_name ) )
    {
    }

    TexturePtr texture;
    TextureUnitPtr texture_unit;
    TextureSamplerPtr sampler;
    std::string sampler_name;
  };

  struct Mesh
  {
  public:
    explicit Mesh( PrimitiveType primType );

    ~Mesh();

    Mesh( const Mesh& ) = delete;

    Mesh& operator=( const Mesh& ) = delete;

    std::vector< VertexBufferPtr > vbs;
    IndexBufferPtr ib;
    ShaderProgramPtr sp;
    std::vector< MeshTexturePtr > textures;

    void generateVAO( int startVertexOffset = 0 );

    void linkShaders();

    ///Bind the VAO
    void bind();

    ///Unbind the VAO
    void unbind();

    bool isBound() const;

    static void unbindAll();

    void draw( int numIndices = -1, int startIndexOffset = 0 );

    void checkValid() const;

    void checkValidVBO( int startVertexOffset = 0 ) const;

    ///This loops through all the indices and checks that they are valid
    void checkIndexBounds( int numIndices = -1, int startIndexOffset = 0 ) const;

    const VertexDeclaration& getDeclaration() const;

    /**
    * Returns the type of primitives used by this mesh (PrimPoint, PrimLineList, PrimLineStrip, PrimTriangleList or PrimTriangleStrip).
    */
    PrimitiveType getPrimType() const;

  private:

    GLuint m_vao;
    int m_numVertices;
    ///If GenerateVAO() is called with a startVertexOffset > 0, the number
    /// of renderable vertices will be less.
    int m_numRenderableVertices;
    VertexDeclaration m_declaration;

    /**
    * The primitive type that is used for rendering.
    */
    PrimitiveType m_primType;


    template< typename index_t >
    void _checkIndexBounds( int numIndices = -1, int startIndexOffset = 0 ) const;

    friend struct Graphics;

  };

  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


  struct RenderNode
  {
  public:

    MeshPtr mesh;
  //  float4x4 xform;
  };


  void clearBindings();


  ShaderProgramPtr defaultShader();

  ShaderProgramPtr defaultWhiteShader();

  ShaderProgramPtr defaultSSPCWhiteShader();

  ShaderProgramPtr defaultTextureShader();

  MeshPtr createFullScreenQuad( ShaderProgramPtr pSp );


}