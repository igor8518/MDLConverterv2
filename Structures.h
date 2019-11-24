#pragma once
#include "3dsmaxsdk_preinclude.h"
#include <MeshNormalSpec.h>
#include <notetrck.h>
#include <meshadj.h>
#include "resource.h"
#include <istdplug.h>
#include <iparamb2.h>
#include <iparamm2.h>
#include <maxtypes.h>
#include <dummy.h>
#include <simpobj.h>
#include <iskin.h>
#include <cstdlib>
#include <math.h>
#include <stdmat.h>

#include "resource.h"
#include <istdplug.h>
#include <iparamb2.h>
#include <iparamm2.h>
#include <maxtypes.h>
#include <impapi.h>

#include <cctype>
//SIMPLE TYPE


#include <impexp.h>
#include <direct.h>
#include <commdlg.h>

#include <triobj.h>
#include <impapi.h>

#include <cstdio>
#include <fstream>
#include <tchar.h>
#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <memory>

#include "pugixml-1.9\src\pugixml.hpp"

#define KEY_POS		3
#define KEY_ROT	4

using namespace std;

enum ModelType
{
	NONE,
	EXTERIOR,
	INTERUIOR
};

struct SSim
{
	std::string Variable = "";
	std::string Units = "";
	bool ScaleF = false;
	bool BiasF = false;
	float Scale = 1.0;
	float Bias = 0.0;
};
struct SParameter
{
	bool CodeF = false;
	bool SimF = false;
	bool LagF = false;
	std::string Code = "";
	SSim Sim;
	float Lag = 0.0;
};
struct SAnimationPart
{
	SParameter Parameter;
};
struct SVisible
{
	SParameter Parameter;
};



enum AnimType
{
	Standard,
	Sim
};
struct SAnimation
{
	std::string name;
	std::string guid;
	AnimType type;
	std::string typeParam;
	float length;
	std::string typeParam2;
};
struct SVisibleInRange
{
	bool MinValueB;
	bool MaxValueB;
	SParameter Parameter;
	int MinValue;
	int MaxValue;
};
struct SPartInfo
{
	std::string Name = "";
	std::string Copy = "";
	int AnimLength = 100;
	bool AnimationF = false;
	bool VisibleF = false;
	bool VisibleInRangeF = false;

	SAnimationPart Animation;
	SVisible Visible;
	SVisibleInRange VisibleInRange;

};

struct SParts
{
	INode* node;
	int LOD;
	int Part;
	std::vector<int>* Inds;
};
#pragma pack(push, 1)


struct SModelDefXML 
{
	vector<SAnimation>* AnimationXML;
	vector<SPartInfo>* PartInfoXML;
	vector<UINT>* BadSec;
};

struct RIFFSectionHeader
{
	char Name[4];
	UINT Size;

};

struct SRIFFData
{
	char Version[4];

};
struct SMDLH
{
	int Magic;
	float Version;

};
struct SMDLG
{
	unsigned long data1;
	unsigned short data2;
	unsigned short data3;
	unsigned char data4[8];

};
struct SBBOX
{
	float xmin;
	float ymin;
	float zmin;
	float xmax;
	float ymax;
	float zmax;
};
struct SIND3
{
	int ind1;
	int ind2;
	int ind3;
};
struct SINDE
{
	short ind1;
	short ind2;
	short ind3;
};
struct SMAT3
{
	int material_flags;
	int material_flags_2;
	int diffuse_texture_index;
	int detail_texture_index;
	int bumpmap_texture_index;
	int specular_texture_index;
	int emissive_texture_index;
	int reflection_texture_index;
	int fresnel_texture_index;
	float diffuse_color_R;
	float diffuse_color_G;
	float diffuse_color_B;
	float diffuse_color_A;
	float specular_color_R;
	float specular_color_G;
	float specular_color_B;
	float specular_color_A;
	float specular_power;
	float detail_map_scale;
	float bump_map_scale;
	float reflection_scale;
	float precipitation_offset;
	float specular_map_power_scale;
	float specular_bloom_floor;
	float ambient_light_scale;
	int source_blend;
	int destination_blend;
	int alpha_test_function;
	float alpha_test_threshold;
	float final_alpha_multiply;
	float zbias;
};
struct SEMT1
{
	float TemperatureScale;
	float DetailOffsetU;
	float DetailOffsetV;
	float DetailRotation;
	float DetailScaleV;
	float DetailBlendWeight;
	float cDetailColor_R;
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
struct SVERT
{
	float position_x;
	float position_y;
	float position_z;
	float normal_x;
	float normal_y;
	float normal_z;
	float texture_mapping_x;
	float texture_mapping_y;
};
struct SPART
{
	int  type; //(1 = Triangle List, 2 = Triangle Fan, 3 = Triangle Strip)
	int  scenegraph_reference;
	int  material_index;
	int  vertex_buffer_index;
	int  vertex_offset;
	int  vertex_count;
	int  index_offset;
	int  index_count;
	int  mouse_rectangle_ref;     //(? )
};
struct SREFP
{
	int scenegraph_reference;
	std::string name;
};
struct SATTO
{
	int  Magic1;
	short type;
	short length;
	short offAttachPoint;
	short unk1;
	int unk2;
	int unk3;
	int unk4;
	int unk5;
	std::string fxName;
	std::string params;
	std::string attachPoint;
	int Magic2;
};
struct SBMAP
{
	long index;
};
struct SSKIN
{
	byte bn[4];
	byte weight[4];
};
struct SVERB
{
	std::vector<SVERT>* VERT;
	std::vector<SBMAP>* BMAP;
	std::vector<SSKIN>* SKIN;
};
struct CSVERB
{
	std::vector<SVERT>* VERT;
	std::vector<SBMAP>* BMAP;
	std::vector<SSKIN>* SKIN;
};
struct SLODT
{
	int LOD;
	std::vector<SPART>* PART;
};
struct STRAN
{
	float m00;
	float m01;
	float m02;
	float m03;
	float m10;
	float m11;
	float m12;
	float m13;
	float m20;
	float m21;
	float m22;
	float m23;
	float m30;
	float m31;
	float m32;
	float m33;
};
struct SSCEN
{
	short child_node_index;
	short peer_node_index;
	short amap_offset;
	short parent;
	INode* parentNode;
};
struct SAMAP
{
	int type;
	int matrix;
};
struct SSGAL
{
	short xanim;
};
struct SSGBR
{
	short bone_index;
};
struct SSGBN
{
	std::string bone_name;
};
struct SSGVL
{
	short vis_index;
};
struct SXANKH
{
	byte type;
	float time;
};
struct SXANKT
{
	float x;
	float y;
	float z;
};
struct SXANKR
{
	float q0;
	float q1;
	float q2;
	float q3;
};
struct SXANK
{
	byte type;
	float time;
	float x;
	float y;
	float z;
	float q0;
	float q1;
	float q2;
	float q3;
};
struct SXANS
{
	int animation_type;
	int animation_ID;
	float animation_length;
	std::vector<SXANK>* XANK;
};
struct SXAPS
{
	std::string code;
	std::string variable;
	std::string units;
	std::string bias;
	std::string lag;
};
struct SXAPI
{
	std::string name;
	bool CodeF = false;
	bool SimF = false;
	bool LagF = false;
	std::string Code = "";
	SSim Sim;
	int Lag;
};
struct SVISI
{
	bool Default;
	std::string name;
	bool CodeF = false;
	bool SimF = false;
	bool LagF = false;
	std::string Code = "";
	SSim Sim;
	int Lag;
};
struct SXANI
{
	byte guid[16];
	float animation_length; //?
	char type[16]; //"Sim"
	std::string *typeParam;// "AutoPlay
	std::vector<SXANS>* XANS;
	SXAPI XAPI;
};
#pragma pack(pop)


struct SLODEData
{
	UINT LOD;

};