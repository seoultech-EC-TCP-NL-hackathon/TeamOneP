#version 450

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
    vec3 rough = texture(bindlessTexture[pc.gBufferRoughness], uv).r;
    outColor = vec4(rough, 1.0);
}
