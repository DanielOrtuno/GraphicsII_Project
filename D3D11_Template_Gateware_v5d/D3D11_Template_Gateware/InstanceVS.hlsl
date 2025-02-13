#pragma pack_matrix(row_major)

cbuffer cameraBuffer : register( b0 )
{
	float4x4 viewMatrix;
	float4x4 projMatrix;
};

cbuffer meshBuffer : register( b1 )
{
	float4x4 worldMatrix;
	float4 color;
	bool enableTexture;
	float time;
	bool dir;
	bool z;
};

struct VERTEX
{
	float4 pos : POSITION;
	float3 uv : TEXTURECOORD;
	float3 normal : NORMAL;
	float4 instData : INSTANCEPOS;
	float4 colorTint : INSTANCECOLOR;
};

struct OUTPUT
{
	float4 pos : SV_POSITION;
	float3 normal : NORMAL;
	float4 color : OCOLOR0;
	float4 worldPos : POSITION;
	float4 tintColor : OCOLOR1;
	bool useTexture : BOOL;
};

OUTPUT main(VERTEX input)
{
	OUTPUT output = (OUTPUT)0;

	float rot = input.instData.w * 3.14 / 180;

	float4x4 rotMatrix = { cos(rot),	0,	 sin(rot),	0,
								0,		1,		0	,	0,
							-sin(rot),	0,	 cos(rot),  0,
								0	,	0,		0	,	1 };

	rotMatrix = mul(worldMatrix, rotMatrix);

	output.pos = input.pos;


	output.normal = mul(input.normal, rotMatrix);
	//output.normal = mul(output.normal, rotMatrix);

	output.pos = mul(output.pos, rotMatrix);
	//output.pos = mul(output.pos, rotMatrix);


	output.pos.x += input.instData.x;
	output.pos.y += input.instData.y;
	output.pos.z += input.instData.z;

	output.worldPos = output.pos;

	output.pos = mul(output.pos, viewMatrix);
	output.pos = mul(output.pos, projMatrix);

	output.color.xyz = input.uv;
	
	output.useTexture = true;

	output.tintColor = input.colorTint;

	return output;
}