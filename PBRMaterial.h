#pragma once



#include "Structures.h"


//SIMPLE TYPE


struct RIFFPBR
{
	int    material_flags;			//
	float  albedo_color_R;			// Albedo color
	float  albedo_color_G;			//
	float  albedo_color_B;			//
	float  albedo_color_A;			//
	float  metallic;						//
	float  smoothness;					//
	int		 renderMode;					//  (0-Opaque;1-Masked;2-Translucent)
	int		 smoothnessSource;		//	(0-AlbedoAlpha;1-MetallicAlpha)
	int		 emissiveMode;				//	(0 - Additive; 1 - AdditiveNightOnly)
	float  maskedThreshold;			//
	int    albedoTextureIndex;	// Albedo texture
	int    metallicTextureIndex;// Metallic texture
	int    bumpTextureIndex;		// Bump texture
	int    emissiveTextureIndex;// Emissive texture
	int    detailTextureIndex;	// Detail texture  
	int		 diffuseUVchannel;		// 
	int		 metallicUVchannel;		//
	int		 bumpUVchannel;				//
	int		 emissiveUVchannel;		//
	int		 detailUVchannel;	  	//
	int  zBias;								//
	float	 detailScaleX;				//
	float	 detailScaleY;				//
	float	 normalScaleX;				//
	float	 normalScaleY;				//	
	int unk1;
	int unk2;
	int unk3;
	int unk4;
	int unk5;
	int unk6;
	int unk7;
	int unk8;
	int unk9;
	int unk10;
	int unk11;
	int unk12;
	int unk13;
	int unk14;
	int unk15;
	int unk16;
	int unk17;
	int unk18;
	int unk19;
	int unk20;
};


//material_flags
#define alpha_to_coverage								0x00000001 //
#define metallic_has_occlusion					0x00000002 //
#define assume_vertical_normal					0x00000004 //
#define double_sided										0x00000008 //
#define prelit_vertices									0x00000010 //
#define metallic_has_reflectance				0x00000020 //

enum RenderMode
{
	Opaque = 1,
	Masked,
	Translucent
};

enum SmoothnessSource
{
	AlbedoAlpha = 1,
	MetallicAlpha
};

enum EmissiveMode
{
	Additive2 = 1,
	AdditiveNightOnly2
};

enum Props2
{
	cAlbedo = 1,						
	fSmoothness,					
	fMetallic,

	Albedo,
	Metallic,
	Normal,
	Emissive,
	Detail,

	iRenderMode,
	fMaskedThreshold,
	bAlphaToCoverage,
	bHasOcclusion,
	bHasReflectance,
	iSmoothnessSource,
	iEmissiveMode,
	bAssumeVerticalNormal,						
	bPrelit,
	bDoubleSided,
	iDecalOrder,
	bIsPanelTexture,
	szMaterialScript
};

class PBRMaterial
{
public:
	Mtl* BaseMat = NULL;
	Shader* DXMat = NULL;

	virtual void GetClassName(MSTR& s) { s = MSTR(_M("Prepar3DPBR")); }

	Point4 albedoColor = { 255, 255, 255, 255 }; // Albedo color
	float  metallic = 0.0;						//
	float  smoothness = 0.0;					//
	int		 renderMode = Opaque;					//  (0-Opaque;1-Masked;2-Translucent)
	int		 smoothnessSource = MetallicAlpha;		//	(0-AlbedoAlpha;1-MetallicAlpha)
	int		 emissiveMode = Additive2;				//	(0 - Additive; 1 - AdditiveNightOnly)
	float  maskedThreshold = 0.0;			//
	BitmapTex* albedoTextureIndex = NULL;	// Albedo texture
	BitmapTex* metallicTextureIndex = NULL;// Metallic texture
	BitmapTex* bumpTextureIndex = NULL;		// Bump texture
	BitmapTex* emissiveTextureIndex = NULL;// Emissive texture
	BitmapTex* detailTextureIndex = NULL;	// Detail texture  
	int		 diffuseUVchannel = 1;		// 
	int		 metallicUVchannel = 1;		//
	int		 bumpUVchannel = 1;				//
	int		 emissiveUVchannel = 1;		//
	int		 detailUVchannel = 1;	  	//
	int  zBias = 1;								//
	float	 detailScaleX = 1.0;				//
	float	 detailScaleY = 1.0;				//
	float	 normalScaleX = 1.0;				//
	float	 normalScaleY = 1.0;				//	

	bool isPanelTexture = false;

	bool alphaToCoverage = false;				//
	bool metallicHasOcclusion = false;	//
	bool assumeVerticalNormal = false;	//
	bool doubleSided = false;						//
	bool prelitVertices = false;				//
	bool metallicHasReflectance = false;//
	
	std::string	szMaterialScript = "";

	int ConvertPBRMaterials(SPBRM* pbrm, std::vector<BitmapTex*>* bt);
	PBRMaterial();
};
PBRMaterial* NewPBRMat();



