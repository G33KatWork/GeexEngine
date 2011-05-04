uniform float4x4 worldViewProjection;


void VShader(
    float3 iPosition : POSITION,
    float3 iColor : COLOR0,
    
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


technique hlsl
{
    pass
    {
        VertexProgram = compile hlslv VShader();
        FragmentProgram = compile hlslf PShader();
    }
}