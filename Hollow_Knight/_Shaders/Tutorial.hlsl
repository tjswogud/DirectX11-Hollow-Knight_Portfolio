//Semantic : 매개변수 및 함수 반환형의 정보를 어떻게 사용할 지 이름을 붙이는 것

struct VertexInput
{
    float4 pos   : POSITION;
    float4 color : COLOR;
};

struct VertexOutput
{
    float4 pos   : SV_POSITION;
    float4 color : COLOR;
};

VertexOutput VS(VertexInput input)
{	
    VertexOutput output;
    
    output.pos   = input.pos;
    output.color = input.color;
    
	return output;
}

float4 PS(VertexOutput input) : SV_TARGET
{
    return input.color;
}