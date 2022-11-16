Texture2D<float4> Texture : register(t0);
sampler TextureSampler : register(s0);


float4 main(float4 color : COLOR0, float2 texCoord : TEXCOORD0) : SV_Target0
{

    float4 c = Texture.Sample(TextureSampler, texCoord);

    return float4((0.2126f * c.r + 0.7152f * c.g + 0.0722f * c.b), (0.2126f * c.r + 0.7152f * c.g + 0.0722f * c.b), (0.2126f * c.r + 0.7152f * c.g + 0.0722f * c.b),1);
}


