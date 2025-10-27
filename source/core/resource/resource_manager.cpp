#include "resource_manager.hpp"
#include "../render/renderpass_builder.hpp"
#include "../GPU/context.hpp"


void ResourceManager::setLight()
{
}
ResourceManager::ResourceManager() = default;
ResourceManager::~ResourceManager() = default;
void ResourceManager::init()
{
  // std::unique_ptr<Material> base = std::make_unique<Material>();
  // base->name = "base";
  // materials_[base->name] = std::move(base);
  auto lightBuf =
    gpu::VkGraphBuilder::buildHostBuffer(sizeof(lightUBO), BufferType::UNIFORM);

  lightBuilder.bufferContext = lightBuf;
  Light light;
  light.transform.position ;
  lightBuilder.uploadData();
  currentCamBuffer.resize(gpu::ctx__->renderingContext.maxInflight__);
  for (int i = 0; i < gpu::ctx__->renderingContext.maxInflight__; i++)
  {
    currentCamBuffer[i] = gpu::VkGraphBuilder::buildHostBuffer(sizeof(CameraUBO),
                                                               BufferType::UNIFORM);
    currentCamBuffer[i].set = gpu::ctx__->pDescriptorAllocator->descriptorSets[i];
    gpu::ctx__->pDescriptorAllocator->writeUbo(currentCamBuffer[i].bufferh_,
                                               currentCamBuffer[i].size_,
                                               currentCamBuffer[i].set,
                                               gpu::CAMERA_BINDING,
                                               0,
                                               1);
    lightBuilder.bufferContext.set = currentCamBuffer[i].set;
    gpu::ctx__->pDescriptorAllocator->writeUbo(lightBuilder.bufferContext.bufferh_,
                                               lightBuilder.bufferContext.size_,
                                               lightBuilder.bufferContext.set,
                                               gpu::GLOBAL_LIGHT,
                                               0,
                                               1);
    gpu::ctx__->pDescriptorAllocator->update();
  }
}


void ResourceManager::updateMaincamState(uint32_t update)
{
  camera.update();
  currentCamBuffer[update].data_ = &(camera.ubo);
  currentCamBuffer[update].size_ = sizeof(camera.ubo);
  currentCamBuffer[update].uploadData();
  lightBuilder.uploadData();
}

void ResourceManager::addModel(gpu::MeshBuffer* meshBuffer,
                               std::string name)
{
  std::unique_ptr<Model> model = std::make_unique<Model>();
  model->name = name;
  model->mesh = meshBuffer;
  pRenderPassBuilder_->drawHandle_.push_back(model.get());
  models_[name] = std::move(model);
}

void ResourceManager::uploadMesh(std::string path)
{
  std::string modelPath = path;
  spdlog::info("Loading {} ", modelPath.c_str());
  auto tempMesh = importer_.loadModel(modelPath.c_str());
  gpu::ctx__->pResourceAllocator->buildMeshNode(tempMesh.get());
  tempMesh->nodeName_ = path;
  meshes_[path] = std::move(tempMesh);
}

void ResourceManager::uploadTexture(std::string path)
{
  std::unique_ptr<gpu::VkTexture> texture = std::make_unique<gpu::VkTexture>();
  texture->type_ = gpu::ResourceType::TEXTURE;
  texture->filepath__ = path;
  auto ptr = texture.get();
  gpu::ctx__->pResourceAllocator->buildTexture(texture.get());
  texture->descriptorSet__ = gpu::ctx__->pDescriptorAllocator->descriptorSets;
  gpu::ctx__->pDescriptorAllocator->uploadBindlessTextureSet(texture.get());
  gpu::ctx__->pDescriptorAllocator->update();
  textures_[path] = std::move(texture);
}
