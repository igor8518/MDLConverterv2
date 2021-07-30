#include "PBRMaterial.h"





PBRMaterial* NewPBRMat()
{
	Class_ID PBRMat = { 0x7aa36351 , 0x6af37aff };
	Interface* gi = GetCOREInterface();
	PBRMaterial* pbr = new PBRMaterial();
	pbr->BaseMat = (Mtl*)gi->CreateInstance(MATERIAL_CLASS_ID, PBRMat);
	//IDxMaterial3* dxmtl = (IDxMaterial3*)pbr->BaseMat->GetInterface(IDXMATERIAL3_INTERFACE);

	if (pbr->BaseMat)
	{
		
		return pbr;
	}
	return NULL;

}

int PBRMaterial::ConvertPBRMaterials(SPBRM* pbrm, std::vector<BitmapTex*>* bt)
{
	int PID = -1;
	int PBNum = BaseMat->NumParamBlocks();
	//ShadeContext sc;
	//BaseMat->Shade(sc)
	//int refs = BaseMat->NumChildren();
	//Mtl* SubMat = BaseMat->GetSubMtl(0);
	//int SPBNum = SubMat->NumParamBlocks();
	//IParamBlock2* SPB = SubMat->GetParamBlock(0);
	//ParamBlockDesc2* sDesc = SPB->GetDesc();
	//int SNP = sDesc->Count();
	//const ParamDef* SPD;
	MSTR CN = BaseMat->ClassName();

	//Shader* shader = BaseMat->GetShader();
	

	IParamBlock2* PB = BaseMat->GetParamBlock(0);
	IParamBlock2* PB1 = BaseMat->GetParamBlock(1);
	IParamBlock2* PB2 = BaseMat->GetParamBlock(2);
	/*IParamBlock2* PB3 = BaseMat->GetParamBlock(3);
	IParamBlock2* PB4 = BaseMat->GetParamBlock(4);
	IParamBlock2* PB5 = BaseMat->GetParamBlock(5);
	IParamBlock2* PB6 = BaseMat->GetParamBlock(6);
	IParamBlock2* PB7 = BaseMat->GetParamBlock(7);
	IParamBlock2* PB8 = BaseMat->GetParamBlock(8);*/
	ParamBlockDesc2* desc = PB->GetDesc();
	ParamBlockDesc2* desc1 = PB1->GetDesc();
	ParamBlockDesc2* desc2 = PB2->GetDesc();
	/*ParamBlockDesc2* desc3 = PB3->GetDesc();
	ParamBlockDesc2* desc4 = PB4->GetDesc();
	ParamBlockDesc2* desc5 = PB5->GetDesc();
	ParamBlockDesc2* desc6 = PB6->GetDesc();
	ParamBlockDesc2* desc7 = PB7->GetDesc();
	ParamBlockDesc2* desc8 = PB8->GetDesc();*/
	int NP = desc->Count();
	int NP1 = desc1->Count();
	int NP2 = desc2->Count();
	/*int NP3 = desc3->Count();
	int NP4 = desc4->Count();
	int NP5 = desc5->Count();
	int NP6 = desc6->Count();
	int NP7 = desc7->Count();
	int NP8 = desc8->Count();*/
	ParamDef mc;
	const ParamDef* PD;
	const ParamDef* PD1;
	const ParamDef* PD2;
	/*const ParamDef* PD3;
	const ParamDef* PD4;
	const ParamDef* PD5;
	const ParamDef* PD6;
	const ParamDef* PD7;
	const ParamDef* PD8;*/

	/*for (int i = 0; i < SNP; i++) {
		SPD = sDesc->GetParamDefByIndex(i);
	}*/

	for (int i = 0; i < NP; i++) {
		PD = desc->GetParamDefByIndex(i);
	}
	for (int i = 0; i < NP1; i++) {
		PD1 = desc1->GetParamDefByIndex(i);
	}
	for (int i = 0; i < NP2; i++) {
		PD2 = desc2->GetParamDefByIndex(i);
	}
	/*for (int i = 0; i < NP3; i++) {
		PD3 = desc3->GetParamDefByIndex(i);
	}
	for (int i = 0; i < NP4; i++) {
		PD4 = desc4->GetParamDefByIndex(i);
	}
	for (int i = 0; i < NP5; i++) {
		PD5 = desc5->GetParamDefByIndex(i);
	}
	for (int i = 0; i < NP6; i++) {
		PD6 = desc6->GetParamDefByIndex(i);
	}
	for (int i = 0; i < NP7; i++) {
		PD7 = desc7->GetParamDefByIndex(i);
	}
	for (int i = 0; i < NP8; i++) {
		PD8 = desc8->GetParamDefByIndex(i);
	}*/

	alphaToCoverage = alpha_to_coverage & pbrm->material_flags ? true : false;
	PB2->SetValue(desc2->NameToIndex(L"bAlphaToCoverage"), 0, alphaToCoverage, 0);

	metallicHasOcclusion = metallic_has_occlusion & pbrm->material_flags ? true : false;
	PB2->SetValue(desc2->NameToIndex(L"bHasOcclusion"), 0, metallicHasOcclusion, 0);

	assumeVerticalNormal = assume_vertical_normal & pbrm->material_flags ? true : false;
	PB2->SetValue(desc2->NameToIndex(L"bAssumeVerticalNormal"), 0, assumeVerticalNormal, 0);

	doubleSided = double_sided & pbrm->material_flags ? true : false;
	PB2->SetValue(desc2->NameToIndex(L"bDoubleSided"), 0, doubleSided, 0);

	prelitVertices = prelit_vertices & pbrm->material_flags ? true : false;
	PB2->SetValue(desc2->NameToIndex(L"bPrelit"), 0, prelitVertices, 0);

	metallicHasReflectance = metallic_has_reflectance & pbrm->material_flags ? true : true; // TEST
	PB2->SetValue(desc2->NameToIndex(L"bHasReflectance"), 0, metallicHasReflectance, 0);
	
	
	PB->BeginEditParams(NULL, 0);
	albedoColor = { pbrm->albedo_color_R,pbrm->albedo_color_G,pbrm->albedo_color_B,pbrm->albedo_color_A };
	PB->SetValue(desc->NameToIndex(L"cAlbedo"), 0, albedoColor, 0);

	metallic = pbrm->metallic;
	PB->SetValue(desc->NameToIndex(L"fMetallic"), 0, metallic, 0);

	smoothness = pbrm->smoothness;
	PB->SetValue(desc->NameToIndex(L"fSmoothness"), 0, smoothness, 0);
	PB->EndEditParams(NULL, 0);

	renderMode = pbrm->renderMode+1;
	PB2->SetValue(desc2->NameToIndex(L"iRenderMode"), 0, renderMode, 0);

	smoothnessSource = pbrm->smoothnessSource + 1;
	PB2->SetValue(desc2->NameToIndex(L"iSmoothnessSource"), 0, smoothnessSource, 0);

	emissiveMode = pbrm->emissiveMode + 1;
	PB2->SetValue(desc2->NameToIndex(L"iEmissiveMode"), 0, emissiveMode, 0);

	maskedThreshold = pbrm->maskedThreshold;
	PB2->SetValue(desc2->NameToIndex(L"fMaskedThreshold"), 0, maskedThreshold, 0);

	if (pbrm->albedoTextureIndex >= 0)
	{
		BaseMat->SetSubTexmap(0, bt->at(pbrm->albedoTextureIndex));
	}
	if (pbrm->bumpTextureIndex >= 0)
	{
		BaseMat->SetSubTexmap(2, bt->at(pbrm->bumpTextureIndex));
	}
	if (pbrm->detailTextureIndex >= 0)
	{
		BaseMat->SetSubTexmap(4, bt->at(pbrm->detailTextureIndex));
	}
	if (pbrm->emissiveTextureIndex >= 0)
	{
		BaseMat->SetSubTexmap(3, bt->at(pbrm->emissiveTextureIndex));
	}
	if (pbrm->metallicTextureIndex >= 0)
	{
		BaseMat->SetSubTexmap(1, bt->at(pbrm->metallicTextureIndex));
	}

	/*

	diffuseUVchannel = pbrm->diffuseUVchannel;
	PB->SetValue(desc->NameToIndex(L"fMetallic"), 0, diffuseUVchannel, 0);

	metallicUVchannel = pbrm->metallicUVchannel;
	PB->SetValue(desc->NameToIndex(L"fMetallic"), 0, metallicUVchannel, 0);

	bumpUVchannel = pbrm->bumpUVchannel;
	PB->SetValue(desc->NameToIndex(L"fMetallic"), 0, bumpUVchannel, 0);

	emissiveUVchannel = pbrm->emissiveUVchannel;
	PB->SetValue(desc->NameToIndex(L"fMetallic"), 0, emissiveUVchannel, 0);

	detailUVchannel = pbrm->detailUVchannel;
	PB->SetValue(desc->NameToIndex(L"fMetallic"), 0, detailUVchannel, 0);*/

	zBias = pbrm->zBias;
	PB2->SetValue(desc2->NameToIndex(L"iDecalOrder"), 0, zBias, 0);

	//BaseMat->Update(0, Interval{ 0,100 });

	/*detailScaleX = pbrm->detailScaleX;
	PB->SetValue(desc->NameToIndex(L"fMetallic"), 0, detailScaleX, 0);

	detailScaleY = pbrm->detailScaleY;
	PB->SetValue(desc->NameToIndex(L"fMetallic"), 0, detailScaleY, 0);

	normalScaleX = pbrm->normalScaleX;
	PB->SetValue(desc->NameToIndex(L"fMetallic"), 0, normalScaleX, 0);

	normalScaleY = pbrm->normalScaleY;
	PB->SetValue(desc->NameToIndex(L"fMetallic"), 0, normalScaleY, 0);*/



	return 0;
}

PBRMaterial::PBRMaterial()
{
}
