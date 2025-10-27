#ifndef RESOURCE_MANAGER
#define RESOURCE_MANAGER

#include <unordered_map>
#include <../resource/importer.hpp>
#include "../scene_graph/material.hpp"
#include "../scene_graph/model.hpp"
#include "vk_memory_allocator.hpp"
#include "vk_host_buffer.h"
#include "../scene_graph/camera_state.hpp"
#include "../scene_graph/mesh.hpp"
#include "../scene_graph/light.hpp"

using Key = std::string;
using bindingIndex = uint32_t;

class ResourceManager
{
  friend class Engine;
  friend class RenderpassBuilder;
  friend class EventManager;
  friend class UI;

  public:
  gpu::DescriptorSetLayout layout;
  ResourceManager();
  ~ResourceManager();
  void init();
  void updateMaincamState(uint32_t currentFrame);
  void addModel(gpu::MeshBuffer* meshBuffer, std::string name);
  void uploadMesh(VkCommandBuffer command, std::string path);
  void uploadMesh(std::string path);
  void uploadTexture(std::string path);
  void setLight();
  LightBuilder lightBuilder;
  std::vector<gpu::VkHostBuffer> currentCamBuffer;
  Model selectedModel{};
  ImporterEx importer_;
  uint32_t maxInflight_ = 3;
  bindingIndex currentBinding_ = 0;

  private:
  UserCamera camera;
  RenderpassBuilder* pRenderPassBuilder_;
  std::unordered_map<Key, std::unique_ptr<Model>> models_;
  std::unordered_map<Key, std::unique_ptr<gpu::MeshBuffer>> meshes_;
  std::unordered_map<Key, std::unique_ptr<Material>> materials_;
  std::unordered_map<Key, std::unique_ptr<gpu::Texture>> textures_;
};

#endif
