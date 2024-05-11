struct VertexOutput
{
    float4 pos : SV_POSITION;
    float4 color : COLOR;
};

float4 PS(VertexOutput input) : SV_TARGET
{
    return input.color;
}