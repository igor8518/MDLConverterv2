#pragma once



#include "Structures.h"


//SIMPLE TYPE


struct RIFFMATE
{
	int    material_flags;			//
	int    material_flags_2;		//
	int    diffuse_texture_index;	//?texDiffuseMap
	int    detail_texture_index;	//texDetailMap
	int    bumpmap_texture_index;	//?texBumpMap
	int    specular_texture_index;	//?texSpecularMap
	int    emissive_texture_index;	//?texEmissiveMap
	int    reflection_texture_index;//?texReflectionMap
	int    fresnel_texture_index;	//texFresnelRamp     
	float  diffuse_color_R;			//?colorDiffuse
	float  diffuse_color_G;			//
	float  diffuse_color_B;			//
	float  diffuse_color_A;			//
	float  specular_color_R;		//?colorSpecular
	float  specular_color_G;		//
	float  specular_color_B;		//
	float  specular_color_A;		//
	float  specular_power;			//?specularpower
	float  detail_map_scale_U;		//iDetailScaleU
	float  bump_map_scale;			//iBumpScale
	float  reflection_scale;		//iEnvLevelScale
	float  precipitation_offset;	//fPrecipOffset = 0.0
	float  specular_map_power_scale;//fSpecMapPowerScale = 64
	float  specular_bloom_floor;	//fSpecularBloomFloor = 0.9
	float  ambient_light_scale;		//fAmbientLightScale = 1.0
	int    source_blend;			//iSrcBlend = 2 (srcColor)
	int    destination_blend;		//iDstBlend = 1 (one)
	int    alpha_test_function;		//iAlphaTestMode
	float  alpha_test_threshold;	//fAlphaTestLevel
	float  final_alpha_multiply;	//fFinalAlphaWriteValue
	float  z_bias;					//
};

struct SEMT1_1
{
	float TemperatureScale;//fTemperatureScale
	float DetailOffsetU; //fDetailOffsetU
	float DetailOffsetV; //fDetailOffsetV
	float DetailRotation; //fDetailRotation
	float DetailScaleV; //iDetailScaleV
	float DetailBlendWeight; //fDetailBlendWeight
	float cDetailColor_R; //cDetailColor
	float cDetailColor_G; 
	float cDetailColor_B;
	float cDetailColor_A;
	int DiffuseUVChannel;
	int DetailUVChannel;
	int SpecularUVChannel;
	int BumpUVChannel;
	int EmissiveUVChannel;
	int unk16;
	int unk17;
	int unk18;
	int unk19;
	int unk20;
	int unk21;
	int unk22;
	int unk23;
	int unk24;
	int unk25;
	int unk26;
	int unk27;
	int unk28;
	int unk29;
	int unk30;
	int unk31;
};


//material_flags
#define material_is_specular							0x00000001 //!bNoBaseMaterialSpecular
#define material_has_a_diffuse_texture					0x00000002 //--
#define material_has_a_bumpmap_texture					0x00000004 //--
#define material_has_a_specular_texture					0x00000008 //--
#define material_has_a_detail_texture					0x00000010 //bHasDetailMap
#define material_has_a_reflection_texture				0x00000020 //--
#define Use_global_environment_map_as_reflection		0x00000040 //
#define material_has_an_emissive_texture				0x00000080 //--
#define material_has_a_FresnelRamp_texture_Reflection	0x00000100 //bFresnelReflection
#define material_has_a_FresnelRamp_texture_Diffuse		0x00000200 //bFresnelDiffuse
#define material_has_a_FresnelRamp_texture_Specular		0x00000400 //bFresnelSpecular
#define Apply_offset_to_start_of_Precipitation			0x00000800 //bUsePrecipOffset
#define Take_into_account_Precipitation					0x00001000 //bUsePrecip
#define Blend_environment_by_inverse_of_diffuse_alpha	0x00002000 //bBlendInvBaseAlpha
#define Blend_environment_by_specular_map_alpha			0x00004000 //bBlendInvSpecAlpha
#define Assume_vertical_normal							0x00008000 //bAssumeVerticalNormal
#define Z_Write_alpha									0x00010000 //bZWriteAlpha
#define No_Z_Write										0x00020000 //bNoZWrite
#define Bloom_material_by_copying						0x00040000 //bBloomCopy
#define Bloom_material_modulating_by_alpha				0x00080000 //bBloomModulate
#define Volume_shadow									0x00100000 //
#define No_shadow										0x00200000 //bNoShadow
#define Z_Test_Alpha									0x00400000 //bZTestAlpha
#define Emissive_Mode_Blend								0x00800000 //iEmissiveMode "AdditiveNightOnly", "Blend", "MultiplyBlend", "Additive", "AdditiveNightOnlyUserControlled", "BlendUserControlled", "MultiplyBlendUserControlled", "AdditiveUserControlled"
#define Set_final_alpha_value_at_render_time			0x01000000 //bFinalAlphaWrite

#define Skinned_mesh									0x04000000 //bSkinned
#define Allow_bloom										0x08000000 //bAllowBloom
#define Allow_emissive_bloom							0x10000000 //bAllowEmissiveBloom
#define Blend_diffuse_by_diffuse_alpha					0x20000000 //bBlendDiffuseBaseAlpha
#define Blend_diffuse_by_inverse_of_specular_map_alpha	0x40000000 //bBlendDiffuseInvSpecAlpha
#define Prelit_vertices									0x80000000 //bPrelitVertices

//material_flags_2
#define Blend_constant									0x00000001 //bBlendConstant
#define Force_Texture_Address_Wrap						0x00000002 //bForceTextureAddressWrap
#define Force_Texture_Address_Clamp						0x00000004 //bForceTextureAddressClamp
#define Double_sided									0x00000008 //bDoubleSided
#define Emissive_Mode_AdditiveNightOnlyUserControlled	0x00000010 //iEmissiveMode
#define Emissive_Mode_BlendUserControlled				0x00000020 //iEmissiveMode
#define Emissive_Mode_MultiplyBlend						0x00000040 //iEmissiveMode
#define Emissive_Mode_MultiplyBlendUserControlled		0x00000080 //iEmissiveMode
#define Emissive_Mode_Additive							0x00000100 //iEmissiveMode
#define Emissive_Mode_AdditiveUserControlled			0x00000200 //iEmissiveMode
#define DetailBlendMode_Multiply							    0x00001000 // iDetailBlendMode
#define DetailBlendMode_Blend							    0x00002000 // iDetailBlendMode
#define UseDetailAlphaAsBlendMask						0x00004000 // bUseDetailAlphaAsBlendMask


enum DetailBlendMode
{
	Mode_Multiply = 1,
	Mode_Blend,
};

enum Blend
{
	zero = 1,
	one,
	srcColor,
	invSrcColor,
	srcAlpha,
	invSrcAlpha,
	destAlpha,
	invDestAlpha,
	destColor,
	invDestColor
};

enum Emmesive
{
	AdditiveNightOnly = 1,
	Blend,
	MultiplyBlend,
	Additive,
	AdditiveNightOnlyUserControlled,
	BlendUserControlled,
	MultiplyBlendUserControlled,
	AdditiveUserControlled,
};

enum Alpha_test
{
	never = 1,
	less,
	equal,
	lessEqual,
	greater,
	notEqual,
	greaterEqual,
	always
};

enum Props
{
	ebFresnelDiffuse = 1,						//bDiffuse
	ebFresnelReflection,					//bReflection 
	ebFresnelSpecular,					//bSpecular
	etexFresnelRamp,
	ebHasFresnelRamp,
	etexDetailMap,
	ebHasDetailMap,

	ebUsePrecip,		    				//bUsePrecip
	ebUsePrecipOffset,						//bUsePrecipOffset
	efPrecipOffset,							//POffset

	eiBumpScale,								//PBumpScale
	ecDetailColor,			//PDetailColor
	efDetailOffsetU,							//PDetailOffsetU
	efDetailOffsetV,							//PDetailOffsetV
	efDetailRotation,							//PDetailRotation
	eiDetailScaleU,							//PDetailScaleU    default:1 --keep naming convention and type for back - compat
	eiDetailScaleV,								//PDetailScaleV    
	ebConstrainScale,							//bConstrainScale 
	eiDetailBlendMode, 							//PDetailBlendMode
	efDetailBlendWeight,						//PDetailBlendWeight
	ebUseDetailAlphaAsBlendMask,		//bUseDetailAlphaAsBlendMask
	eiEnvLevelScale,							//ReflectScale
	efSpecMapPowerScale,						//SpecMapPowScale

	ebBlendInvBaseAlpha,					//specialEnvInvBaseAlpha      
	ebBlendInvSpecAlpha,						//specialEnvInvSpecAlpha   
	ebBlendDiffuseBaseAlpha,				//bBlendDiffuseBaseAlpha      
	ebBlendDiffuseInvSpecAlpha,				//bBlendDiffuseInvSpecAlpha   
	ebMaskDiffuseBlendsByDetailBlendMask,	//bMaskDiffuseBlendsByDetailBlendMask   
	ebUseGlobalEnv,						//specialUseGlobalEnv     

	ebUseEmissiveAlphaAsHeatMap,			//specialEmissiveAlphaHeat    
	efTemperatureScale,						//TemperatureScale   

	eiSrcBlend,								//SrcBlend
	eiDstBlend,								//DstBlend

	ebAllowBloom,								//bAllowBloom  
	ebBloomCopy,   						//bBloomCopy 
	ebBloomModulate,						//bBloomModulate    
	ebNoSpecularBloom,						//bNoSpecularBloom   
	ebAllowEmissiveBloom,					//bAllowEmissiveBloom
	efSpecularBloomFloor,					//SpecularBloomFloor 
	efAmbientLightScale,					//AmbientLightScale 

	eiEmissiveMode,							//EmissiveMode       

	ebZTestAlpha,							//bZTestAlpha      
	eiAlphaTestMode,								//AlphaTestMode     
	efAlphaTestLevel,							//AlphaTestLevel     

	ebFinalAlphaWrite,						//bFinalAlphaWrite   
	efFinalAlphaWriteValue,					//FinalAlphaWriteValue 
	ebMaskFinalAlphaBlendByDetailBlendMask,	//bMaskFinalAlphaBlendByDetailBlendMask 

	ebAssumeVerticalNormal,					//bAssumeVerticalNormal      
	ebZWriteAlpha,							//bZWriteAlpha            
	ebNoZWrite,							//bNoZWrite                    
	ebNoShadow,								//bNoShadow                    
	ebPrelitVertices,						//bPrelitVertices         
	ebNoBaseMaterialSpecular,				//bNoBaseMaterialSpecular     
	ebSkinned,								//bSkinned                   
	ebDoubleSided,							//bDoubleSided              

	ebBlendConstant,						//bBlendConstant   
	ebForceTextureAddressWrap,				//bForceTextureAddressWrap  
	ebForceTextureAddressClamp,				//bForceTextureAddressClamp 

	ebIsPanelTexture,				//bIsPanelTexture         
	ebIsNNumberTexture,					//bIsNNumberTexture  

	efZBias,									// ZBias 
};

class P3DMaterial
{
public:
	StdMat2 *BaseMat = NULL;;
	virtual void GetClassName(MSTR& s) { s = MSTR(_M("P3DMaterial")); }
	bool		bFresnelDiffuse = false;						//bDiffuse
	bool		bFresnelReflection = false;						//bReflection 
	bool		bFresnelSpecular = false;						//bSpecular
	BitmapTex*	texFresnelRamp = NULL;
	bool		bHasFresnelRamp = false; 
	BitmapTex*	texDetailMap = NULL;
	bool		bHasDetailMap = false;

	bool		bUsePrecip = false;			    				//bUsePrecip
	bool		bUsePrecipOffset = false;						//bUsePrecipOffset
	float		fPrecipOffset = 0.0;							//POffset

	int			iBumpScale = 1;									//PBumpScale
	Point4		cDetailColor = { 255,255,255,255 };				//PDetailColor
	float		fDetailOffsetU = 0.0;							//PDetailOffsetU
	float		fDetailOffsetV = 0.0;							//PDetailOffsetV
	float		fDetailRotation = 0.0;							//PDetailRotation
	int			iDetailScaleU = 1;  							//PDetailScaleU    default:1 --keep naming convention and type for back - compat
	int			iDetailScaleV = 1;								//PDetailScaleV    
	bool		bConstrainScale = true;							//bConstrainScale 
	int			iDetailBlendMode = 1; 							//PDetailBlendMode
	float		fDetailBlendWeight = 1.0;						//PDetailBlendWeight
	bool		bUseDetailAlphaAsBlendMask = false;			//bUseDetailAlphaAsBlendMask
	int			iEnvLevelScale = 100;							//ReflectScale
	float		fSpecMapPowerScale = 64.0;						//SpecMapPowScale

	bool		bBlendInvBaseAlpha = false;						//specialEnvInvBaseAlpha      
	bool		bBlendInvSpecAlpha = false;						//specialEnvInvSpecAlpha   
	bool		bBlendDiffuseBaseAlpha = false;					//bBlendDiffuseBaseAlpha      
	bool		bBlendDiffuseInvSpecAlpha = false;				//bBlendDiffuseInvSpecAlpha   
	bool		bMaskDiffuseBlendsByDetailBlendMask = false;	//bMaskDiffuseBlendsByDetailBlendMask   
	bool		bUseGlobalEnv = false;							//specialUseGlobalEnv     

	bool		bUseEmissiveAlphaAsHeatMap = false;				//specialEmissiveAlphaHeat    
	float		fTemperatureScale = 1.0;						//TemperatureScale   

	int			iSrcBlend = one;								//SrcBlend
	int			iDstBlend = zero;								//DstBlend

	bool		bAllowBloom = true;								//bAllowBloom  
	bool		bBloomCopy = false;     						//bBloomCopy 
	bool		bBloomModulate = false;							//bBloomModulate    
	bool		bNoSpecularBloom = false;//?						//bNoSpecularBloom   
	bool		bAllowEmissiveBloom = false;					//bAllowEmissiveBloom
	float		fSpecularBloomFloor = 0.9;						//SpecularBloomFloor 
	float		fAmbientLightScale = 1.0;						//AmbientLightScale 

	int			iEmissiveMode = AdditiveNightOnly;							//EmissiveMode       

	bool		bZTestAlpha = false;							//bZTestAlpha      
	int			iAlphaTestMode = 1;								//AlphaTestMode     
	float		fAlphaTestLevel = 0.0;							//AlphaTestLevel     

	bool		bFinalAlphaWrite = false;						//bFinalAlphaWrite   
	float		fFinalAlphaWriteValue = 1.0;					//FinalAlphaWriteValue 
	bool		bMaskFinalAlphaBlendByDetailBlendMask = false;//?	//bMaskFinalAlphaBlendByDetailBlendMask 

	bool		bAssumeVerticalNormal = false;					//bAssumeVerticalNormal      
	bool		bZWriteAlpha = false;							//bZWriteAlpha            
	bool		bNoZWrite = false;								//bNoZWrite                    
	bool		bNoShadow = false;								//bNoShadow                    
	bool		bPrelitVertices = false;						//bPrelitVertices         
	bool		bNoBaseMaterialSpecular = false;				//bNoBaseMaterialSpecular     
	bool		bSkinned = false;								//bSkinned                   
	bool		bDoubleSided = false;							//bDoubleSided              

	bool		bBlendConstant = false;							//bBlendConstant   
	bool		bForceTextureAddressWrap = false;				//bForceTextureAddressWrap  
	bool		bForceTextureAddressClamp = false;				//bForceTextureAddressClamp 

	bool		bIsPanelTexture = false;	//?					//bIsPanelTexture         
	bool		bIsNNumberTexture = false;	//?					//bIsNNumberTexture  

	float		fZBias = 0.0;									// ZBias 

	std::string	szMaterialScript = "";
	//?					//txtMaterialScript 


	bool bmaterial_has_a_diffuse_texture = false;
	bool bmaterial_has_a_bumpmap_texture = false;
	bool bmaterial_has_a_specular_texture = false;
	bool bmaterial_has_a_reflection_texture = false;
	bool bUse_global_environment_map_as_reflection = false;
	bool bmaterial_has_an_emissive_texture = false;
	bool bVolume_shadow = false;
	int ConvertPrepar3DMaterials(SMAT3 * mate, SEMT1 * emate, std::vector<BitmapTex*>* bt);
	P3DMaterial();
};
P3DMaterial *NewP3DMat();



