#version 450
#extension GL_EXT_nonuniform_qualifier: require

layout (location = 0) in vec2 uv;
layout (location = 0) out vec4 outColor;

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

void main() {
    vec3 albedo = texture(bindlessTexture[pc.gBufferAlbedo], uv).xyz;
    outColor = vec4(albedo, 1.0);
}
