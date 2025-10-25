#ifndef RENDERER_HPP
#define RENDERER_HPP
#include <../scene_graph/mesh.hpp>
#include <../resource/sampler_builder.hpp>
#include "resource_manager.hpp"
#include "../../../extern/examples/renderer_resource.hpp"
#include "../GPU/context.hpp"
#include "unique.hpp"
#include "ui.hpp"

struct RenderInitInfo
{
  ResourceManager* resourceManager;
};

enum class ViewMode
{
  SINGLE,
  MULTI,
  FPS,
  TPS,
  VR
};

class IRenderer
{
  friend class Engine;
  friend class EventManager;

  public:
  IRenderer(RenderInitInfo info);
  void uploadGBufferPass();
  ~IRenderer() = default;
  void uploadDepthPass();
  void uploadQuadDraw();
  void uploadUiDraw();
  void pushConstant(VkCommandBuffer cmdBuffer);
  void draw(VkCommandBuffer cmd, uint32_t currentFrame);

  private:
  std::vector<gpu::SwapchainHandle> swapchainHandle_;
  std::vector<gpu::VkMeshBuffer*> drawHandle_;

  std::vector<gpu::VkFrameAttachment*> depthAttachmentHandle_;
  std::vector<gpu::VkFrameAttachment*> shadowAttachmentHandle_;

  std::vector<gpu::VkFrameAttachment*> gBufferAlbedoHandle_;
  std::vector<gpu::VkFrameAttachment*> gBufferNormalHandle_;
  std::vector<gpu::VkFrameAttachment*> gBufferPositionHandle_;
  std::vector<gpu::VkFrameAttachment*> gBufferRoughnessHandle_;
  std::vector<gpu::VkFrameAttachment*> shadowBufferHandle_;

  std::vector<gpu::VkTexture*> textures_;
  gpu::Pipeline depthRenderingPipeline__;
  gpu::Pipeline albedoRenderingPipeline__;
  gpu::Pipeline normalRenderingPipeline__;
  gpu::Pipeline positionRenderingPipeline__;

  gpu::Pipeline gBufferWritePipeline__;
  gpu::Pipeline depthWritePipeline__;

  gpu::PipelineLayout pipelineLayout_h;
  PFN_vkCmdSetPolygonModeEXT vkCmdSetPolygonModeEXT;
  VkPolygonMode polygonMode = VK_POLYGON_MODE_FILL;
  VkBool32 depthTest = VK_TRUE;
  VkBool32 drawBackground = VK_TRUE;

  std::string depthWrite = "C:/Users/dlwog/OneDrive/Desktop/VkMain-out/source/shader/depth_write.frag";
  std::string gBufferWrite = "C:/Users/dlwog/OneDrive/Desktop/VkMain-out/source/shader/def_geo_write.frag";

  std::string fragGBufferAlbedoRender =
    "C:/Users/dlwog/OneDrive/Desktop/VkMain-out/source/shader/def_albedoRender.frag";
  std::string fragGBufferPositionRender =
    "C:/Users/dlwog/OneDrive/Desktop/VkMain-out/source/shader/def_positionRendering.frag";
  std::string fragGBufferNormalRender =
    "C:/Users/dlwog/OneDrive/Desktop/VkMain-out/source/shader/def_normalRendering.frag";

  std::string fragDepthRender = "C:/Users/dlwog/OneDrive/Desktop/VkMain-out/source/shader/def_depthRendering.frag";
  std::string vertPath = "C:/Users/dlwog/OneDrive/Desktop/VkMain-out/source/shader/vertex.vert";
  std::string vertexQuad = "C:/Users/dlwog/OneDrive/Desktop/VkMain-out/source/shader/quad.vert";
  VkViewport viewport{};
  VkRect2D scissor{};

  struct FrameAttachment
  {
    int gBufferPositon = 0;
    int gBufferNormal = 0;
    int gBufferAlbedo = 0;
    int gBufferRoughness = 0;

    int DepthBuffer = 0;
    int ShaderBuffer = 0;
    int lightningBuffer = 0;
    int postProcessBuffer = 0;

    glm::mat4 modelMatrix;
    glm::vec4 vec4;
    glm::vec4 vec3;
  } renderAttachment;

  ResourceManager& pResourceManager;
  VkDeviceSize offsets = 0;
};
#endif
