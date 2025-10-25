#version 450
#extension GL_EXT_nonuniform_qualifier: require


layout(location = 0) in vec3 fragPosition;
layout(location = 1) in vec3 fragNormal;
layout(location = 2) in vec2 fragUV;

layout(location = 2) out vec4 gAlbedo;
layout(location = 0) out vec4 gPosition;
layout(location = 1) out vec4 gNormal;


layout (set = 0, binding = 2) uniform sampler2D bindlessTexture[];

layout(push_constant) uniform PushData {
    int gBufferPositon;
    int gBufferNormal;
    int gBufferAlbedo;
    int gBufferRoughness;
    int depthBuffer;
    int shadowBuffer;
    int lightningBuffer;
    int postProcessBuffer;
} pc;

void main()
{
    gPosition = vec4(fragPosition, 1.0);
    gNormal = vec4(normalize(fragNormal) * 0.5 + 0.5, 1.0);
    gAlbedo = texture(albedoTexture, fragUV);
}
