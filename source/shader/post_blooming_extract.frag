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
    vec3 color = texture(bindlessTexture[pc.bloomingExtract], uv).rgb;
    float brightness = max(max(color.r, color.g), color.b);
    vec3 bloom = (brightness > 1.0) ? color : vec3(0.0);
    outColor = vec4(bloom, 1.0);
}
