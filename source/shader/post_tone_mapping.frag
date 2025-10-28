#version 450
#extension GL_EXT_nonuniform_qualifier: require
layout (location = 0) in vec2 uv;
layout(location = 0) out vec4 outColor;
layout (set = 0, binding = 2) uniform sampler2D bindlessTexture[];
layout(push_constant) uniform PushData {
    int gBufferPositon;
    int gBufferNormal;
    int gBufferAlbedo;
    int gBufferRoughness;
    int DepthBuffer;
    int ShaderBuffer;
    int lightningBuffer;
    int bloomingExtract;
    int bloomingBlur;
    int ToneMapping;
    int gammaCollection;
} pc;

void main() {
    vec3 hdrColor =texture(bindlessTexture[pc.bloomingBlur], uv).rgb;
    vec3 mapped = hdrColor / (hdrColor + vec3(1.0));
    outColor = vec4(mapped, 1.0);
}
