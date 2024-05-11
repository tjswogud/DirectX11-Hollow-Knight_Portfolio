cbuffer ColorBuffer : register(b0)
{
    float4 color;
};

struct VertexOutput
{
    float4 pos : SV_POSITION;
    float2 uv : uv;
};

Texture2D map     : register(t0); // bitmap 같은거라고 보면된다.
SamplerState samp : register(s0); // 설정값

float4 PS(VertexOutput input) : SV_TARGET
{
    float4 tex = map.Sample(samp, input.uv);
    
    return tex * color;
}