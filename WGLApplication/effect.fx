uniform float4x4 worldViewProjection;


void VShader(
    float3 iPosition : ATTR0,
    float3 iColor : ATTR1,
    
    out float4 position : POSITION,
    out float3 color : COLOR0)
{
    position = mul(worldViewProjection, float4(iPosition, 1.0f));
    color = iColor;
}

float4 PShader(in float3 color : COLOR0) : COLOR
{
    return float4(color, 1.0);
}


technique glsl
{
    pass
    {
        VertexProgram = compile glslv VShader();
        FragmentProgram = compile glslf PShader();
    }
}