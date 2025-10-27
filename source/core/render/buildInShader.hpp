#ifndef MYPROJECT_BUILDINSHADER_HPP
#define MYPROJECT_BUILDINSHADER_HPP
#include <string>


namespace shader
{
  std::string depthWrite =
    "C:/Users/dlwog/OneDrive/Desktop/VkMain-out/source/shader/depth_write.frag";
  std::string gBufferWrite =
    "C:/Users/dlwog/OneDrive/Desktop/VkMain-out/source/shader/def_geo_write.frag";
  std::string vertexWrite =
      "C:/Users/dlwog/OneDrive/Desktop/VkMain-out/source/shader/vertex.vert";
  std::string quadWrite =
    "C:/Users/dlwog/OneDrive/Desktop/VkMain-out/source/shader/quad.vert";

  std::string fragGBufferAlbedoRender =
    "C:/Users/dlwog/OneDrive/Desktop/VkMain-out/source/shader/def_albedoRendering.frag";
  std::string fragGBufferPositionRender =
    "C:/Users/dlwog/OneDrive/Desktop/VkMain-out/source/shader/def_positionRendering.frag";
  std::string fragGBufferNormalRender =
    "C:/Users/dlwog/OneDrive/Desktop/VkMain-out/source/shader/def_normalRendering.frag";
  std::string fragDepthRender =
    "C:/Users/dlwog/OneDrive/Desktop/VkMain-out/source/shader/def_depthRender.frag";
  std::string fragShadowRender = " ";


}


#endif //MYPROJECT_BUILDINSHADER_HPP
