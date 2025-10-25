#include "resource_manager.hpp"
#include "../GPU/context.hpp"

void ResourceManager::setLight()
{
}

ResourceManager::ResourceManager(const ResourceManagerCreateInfo& info) :
  device_(info.device),
  allocator_(*info.allocator),
  maxInflight_(info.maxInflight)
{
  std::unique_ptr<Material> base = std::make_unique<Material>();
  base->name = "base";
  materials_[base->name] = std::move(base);
  auto lightBuf = gpu::VkGraphBuilder::buildHostBuffer(sizeof(lightUBO), BufferType::UNIFORM);
  lightBuilder.bufferContext = lightBuf;
  Light light;
  light.direction = glm::vec3(0, 0, 0);
  light.type = LightType::Point;
  light.intensity = 0.5;
  light.color = glm::vec3(0.3, 0.2, 0.5);
  Light light2;
  light.direction = glm::vec3(0, 0, 0);
  light.type = LightType::Point;
  light.intensity = 100;
  light.color = glm::vec3(0.3, 0.2, 0.5);
  Light light3;
  light.type = LightType::Point;
  light.direction = glm::vec3(0, 0, 0);
  light.intensity = 1000;
  light.color = glm::vec3(0.3, 0.2, 0.5);
  lightBuilder.build(light);
  lightBuilder.build(light2);
  lightBuilder.build(light3);
  lightBuilder.uploadData();
  currentCamBuffer.resize(info.maxInflight);

  for (int i = 0; i < gpu::ctx__->renderingContext.maxInflight__; i++)
  {
    currentCamBuffer[i] = gpu::VkGraphBuilder::buildHostBuffer(sizeof(CameraUBO),
                                                               BufferType::UNIFORM);
    currentCamBuffer[i].set = gpu::ctx__->pDescriptorAllocator->allocate(i);
    gpu::ctx__->pDescriptorAllocator->writeUbo(currentCamBuffer[i].bufferh_,
                                               currentCamBuffer[i].size_,
                                               currentCamBuffer[i].set,
                                               gpu::CAMERA_BINDING,
                                               0,
                                               1);
    lightBuilder.bufferContext.set = currentCamBuffer[i].set;

    //gpu::ctx__->pDescriptorAllocator->writeUbo(lightBuilder.bufferContext.bufferh_,
    //                                           lightBuilder.bufferContext.size_,
    //                                           lightBuilder.bufferContext.set,
    //                                           1,
    //                                           0,
    //                                           1);
    gpu::ctx__->pDescriptorAllocator->update();
  }
}

ResourceManager::~ResourceManager() = default;

void ResourceManager::updateMaincamState(uint32_t update)
{
  camera.update();
  currentCamBuffer[update].data_ = &(camera.ubo);
  currentCamBuffer[update].size_ = sizeof(camera.ubo);
  currentCamBuffer[update].uploadData();
}


std::unique_ptr<gpu::VkMeshBuffer> ResourceManager::uploadMesh(std::string path)
{
  std::string modelPath = path;
  spdlog::info("Loading {} ", modelPath.c_str());
  auto tempMesh = importer_.loadModel(modelPath.c_str());
  tempMesh->nodeName_ = path;
  return std::move(tempMesh);
}

std::unique_ptr<gpu::VkTexture> ResourceManager::uploadTexture(std::string path)
{
  std::unique_ptr<gpu::VkTexture> texture = std::make_unique<gpu::VkTexture>();
  texture->type_ = gpu::ResourceType::TEXTURE;
  texture->filepath__ = path;
  return std::move(texture);
}
