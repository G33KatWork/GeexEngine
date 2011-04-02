float4x4 worldViewProjection;
texture testTexture;


sampler Sampler = sampler_state
{
    Texture   = (testTexture);
    MipFilter = LINEAR;
    MinFilter = LINEAR;
    MagFilter = LINEAR;
};


struct VertexShaderInput
{
    float3 position : POSITION;
    float2 texture0 : TEXCOORD0;
};

struct VertexShaderOutput
{
    float4 position : POSITION;
    float2 texture0 : TEXCOORD0;
};


VertexShaderOutput VShader(VertexShaderInput vin)
{
    VertexShaderOutput output;
    
    output.position = mul(float4(vin.position, 1.0f), worldViewProjection);
    output.texture0 = vin.texture0;
    
    return output;
}

float4 PShader(VertexShaderOutput vout) : COLOR0
{
    return tex2D(Sampler, vout.texture0);
}


technique Simplest
{
    pass Pass0
    {
        Lighting = FALSE;
        
        Sampler[0] = (Sampler);
        
        VertexShader = compile vs_1_1 VShader();
        PixelShader = compile ps_2_0 PShader();
    }
}