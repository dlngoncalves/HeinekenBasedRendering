#pragma once
#include <cstddef>
#include <vector>
#include <string>

enum class CullFace {
    Back,
    Front,
    None
};

enum class PolygonMode {
    Fill,
    Wireframe
};

enum class DepthFunc {
    Less,
    LessEqual,
    Equal,
    Always
};

enum class BlendFactor {
    Zero,
    One,
    SrcAlpha,
    OneMinusSrcAlpha
};

 enum class BufferUsage
 {
        VERTEX,
        INDEX,
        UNIFORM,
 };
 
 enum class TextureFormat
 {
    RGBA8,
    RGB8,
    RG8,
    R8,
    DEPTH24_STENCIL8,
    RGBA16F,
};

enum class TextureWrap
{
    Repeat,
    ClampToEdge,
    MirroredRepeat
};

enum class TextureFilter
{
    Nearest,
    Linear,
    LinearMipmap    // only meaningful for minFilter
};

enum class RenderTargetType
{
    Screen,     // default framebuffer — no textures needed
    Offscreen   // custom FBO with attached textures
};

struct BufferDesc
{
    size_t size;
    BufferUsage usage;
    // other buffer properties like usage, etc.
};

struct TextureDesc
{
    int width;
    int height;
    int channels;
    TextureFormat format;    // replaces raw GL internal format
    TextureWrap wrapS;       // all APIs have wrapping
    TextureWrap wrapT;
    TextureFilter minFilter; // all APIs have filtering
    TextureFilter magFilter;
    bool generateMips;       // all APIs support mipmaps
};

struct VertexAttribute
{
    int        location;  // layout location in shader
    int        count;     // 2, 3, 4 components
    bool       normalized;
};

struct VertexLayout
{
    std::vector<VertexAttribute> attributes;
    size_t stride;
};

struct PipelineDesc
{
    std::string vertexShaderPath;
    std::string fragmentShaderPath;
    VertexLayout vertexLayout;
    // BlendState   blendState;
    // DepthState   depthState;
    // RasterState  rasterState;
};

struct DepthState
{
    bool  testEnabled;   // glEnable(GL_DEPTH_TEST)
    bool  writeEnabled;  // glDepthMask()
    DepthFunc func;         // glDepthFunc() — LESS, LEQUAL etc.
};

struct BlendState
{
    bool enabled;        // glEnable(GL_BLEND)
    // src/dst factors — glBlendFunc()
};

struct RasterState
{
    bool  cullEnabled;   // glEnable(GL_CULL_FACE)
    CullFace cullFace;     // GL_BACK, GL_FRONT
    PolygonMode polygonMode;  // GL_FILL, GL_LINE — useful for debug wireframe
};

struct RenderTargetDesc
{
    RenderTargetType type = RenderTargetType::Screen;
    int width  = 0;
    int height  = 0;
    // color attachments — empty means no color (depth only pass)
    std::vector<TextureFormat> colorFormats;
    // depth attachment
    bool             hasDepth      = true;
    TextureFormat    depthFormat   = TextureFormat::DEPTH24_STENCIL8;
};