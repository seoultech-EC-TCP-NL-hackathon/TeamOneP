#ifndef RENDERER_HPP
#define RENDERER_HPP
#include "../resource/resource_manager.hpp"
#include "../../../extern/examples/renderer_resource.hpp"
#include "../GPU/context.hpp"
#include <../scene_graph/mesh.hpp>
#include "unique.hpp"
#include "ui/ui.hpp"

class RenderpassBuilder
{
  friend class ResourceManager;
  friend class UI;
  friend class EventManager;
  friend class Engine;

  public:
  RenderpassBuilder();
  void init();
  ~RenderpassBuilder() = default;
  void uploadGBufferWritePass();
  void uploadLightningPass();
  void uploadDepthOnlyPass();
  void gBufferImageRer();
  void uploadUiDraw();
  void draw(VkCommandBuffer cmd, uint32_t currentFrame);

  private:
  void buildPass();
  void updateFrameConstant();
  void pushModelConstant(VkCommandBuffer command, ModelConstant* modelConstant);
  void pushFrameConstant(VkCommandBuffer cmdBuffer);
  std::vector<Model*> drawHandle_;
  std::vector<std::unique_ptr<gpu::RenderPass>> depthOnlyPass;
  std::vector<std::unique_ptr<gpu::RenderPass>> gBufferPass;
  std::vector<std::unique_ptr<gpu::RenderPass>> uiDrawPass;
  std::vector<std::unique_ptr<gpu::RenderPass>> shadowPass;
  std::vector<std::unique_ptr<gpu::RenderPass>> lightningPass;
  std::vector<std::unique_ptr<gpu::RenderPass>> swapchainRenderPass;


  std::vector<std::unique_ptr<gpu::VkFrameAttachment>> swapchainAttachment_;
  std::vector<std::unique_ptr<gpu::VkFrameAttachment>> depthAttachmentHandle_;
  std::vector<std::unique_ptr<gpu::VkFrameAttachment>> shadowAttachmentHandle_;
  std::vector<std::unique_ptr<gpu::VkFrameAttachment>> gBufferAlbedoHandle_;
  std::vector<std::unique_ptr<gpu::VkFrameAttachment>> gBufferNormalHandle_;
  std::vector<std::unique_ptr<gpu::VkFrameAttachment>> gBufferPositionHandle_;
  std::vector<std::unique_ptr<gpu::VkFrameAttachment>> gBufferRoughnessHandle_;
  std::vector<std::unique_ptr<gpu::VkFrameAttachment>> gBufferMetalicHandle_;
  std::vector<std::unique_ptr<gpu::VkFrameAttachment>> lightningAttachmentHandle_;
  std::vector<std::unique_ptr<gpu::VkFrameAttachment>> shadowBufferHandle_;

  gpu::Pipeline depthRenderingPipeline__;
  gpu::Pipeline albedoRenderingPipeline__;
  gpu::Pipeline normalRenderingPipeline__;
  gpu::Pipeline positionRenderingPipeline__;
  gpu::Pipeline roughnessRenderingPipeline__;
  gpu::Pipeline lightningRenderingPipeline__;


  gpu::Pipeline gBufferWritePipeline__;
  gpu::Pipeline depthWritePipeline__;
  gpu::Pipeline lightningWritePipeline__;

  gpu::PipelineLayout pipelineLayout_h;

  PFN_vkCmdSetPolygonModeEXT vkCmdSetPolygonModeEXT;
  VkPolygonMode polygonMode = VK_POLYGON_MODE_FILL;
  VkBool32 depthTest = VK_TRUE;
  VkBool32 drawBackground = VK_TRUE;

  std::string depthWrite =
    "C:/Users/dlwog/OneDrive/Desktop/VkMain-out/source/shader/depth_write.frag";
  std::string gBufferWrite =
    "C:/Users/dlwog/OneDrive/Desktop/VkMain-out/source/shader/def_geo_write.frag";
  std::string lightningWrite =
    "C:/Users/dlwog/OneDrive/Desktop/VkMain-out/source/shader/def_lightning_write.frag";


  std::string fragGBufferAlbedoRender =
    "C:/Users/dlwog/OneDrive/Desktop/VkMain-out/source/shader/def_albedoRender.frag";
  std::string fragGBufferPositionRender =
    "C:/Users/dlwog/OneDrive/Desktop/VkMain-out/source/shader/def_positionRender.frag";
  std::string fragGBufferNormalRender =
    "C:/Users/dlwog/OneDrive/Desktop/VkMain-out/source/shader/def_normalRender.frag";
  std::string fragGBufferRoughnessRender =
    "C:/Users/dlwog/OneDrive/Desktop/VkMain-out/source/shader/def_RoughnessRender.frag";
  std::string fragLightingRender =
    "C:/Users/dlwog/OneDrive/Desktop/VkMain-out/source/shader/def_lightningRender.frag";

  std::string fragDepthRender =
    "C:/Users/dlwog/OneDrive/Desktop/VkMain-out/source/shader/def_depthRender.frag";
  std::string vertPath =
    "C:/Users/dlwog/OneDrive/Desktop/VkMain-out/source/shader/vertex.vert";
  std::string vertexQuad =
    "C:/Users/dlwog/OneDrive/Desktop/VkMain-out/source/shader/quad.vert";

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

    int cubeTex = -1;
  } renderAttachment;
};
#endif
