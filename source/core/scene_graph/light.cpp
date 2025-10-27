#include "light.hpp"
#include "context.hpp"

LightBuilder::LightBuilder()
{
  ubo.lightCount = 0;
}

void LightBuilder::build(const Light& light)
{
  if (ubo.lightCount >= MAX_LIGHTS) return;
  GPULight& gpu = ubo.lights[ubo.lightCount];
  ubo.lightCount += 1;
  gpu.position = glm::vec4(light.transform.position, static_cast<float>(light.type));
  glm::vec3 dir = glm::normalize(light.transform.rotation * glm::vec3(0, 0, -1));
  gpu.direction = glm::vec4(dir, light.angle);
  gpu.color = glm::vec4(light.color, light.intensity);
  gpu.view = glm::lookAt(light.transform.position,
                         dir,
                         glm::vec3(0, 1, 0));
  gpu.proj = glm::ortho(
                        0.0f,
                        static_cast<float>(gpu::ctx__->pSwapChainContext->extent__.width),
                        0.0f, // bottom
                        static_cast<float>(gpu::ctx__->pSwapChainContext->extent__.height),
                        -1.0f, // near
                        1.0f   // far
                       );
}

void LightBuilder::uploadData()
{
  bufferContext.data_ = &ubo;
  bufferContext.size_ = sizeof(GPULight);
  bufferContext.uploadData();
}
