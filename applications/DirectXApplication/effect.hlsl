struct VIn
{
    float4 position : POSITION;
    float4 color : COLOR;
};

struct VOut
{
    float4 position : SV_POSITION;
    float4 color : COLOR;
};

struct POut
{
    float4 Color : COLOR0;
};


float4x4 worldViewProjection;


VOut VShader(VIn vin)
{
    VOut output;

    output.position = vin.position;
    output.position = mul(vin.position, worldViewProjection);
    output.color = vin.color;

    return output;
}

POut PShader(VOut vout) : SV_TARGET
{
    POut pout;
    
    pout.Color = vout.color;
    return pout;
}


technique hlsl
{
    pass Pass0
    {        
        VertexShader = compile vs_2_0 VShader();
        PixelShader = compile ps_2_0 PShader();
    }
}