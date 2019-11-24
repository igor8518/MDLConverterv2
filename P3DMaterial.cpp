#include "P3DMaterial.h"





P3DMaterial * NewP3DMat()
{
	Class_ID P3DMat = { 0x7e8caded , 0xb6928000 };
	Interface *gi = GetCOREInterface();
	P3DMaterial* p3d = new P3DMaterial();
	p3d->BaseMat = (StdMat2*)gi->CreateInstance(MATERIAL_CLASS_ID, P3DMat);

	if (p3d->BaseMat)
	{
		return p3d;
	}
	return NULL;

}

int P3DMaterial::ConvertPrepar3DMaterials(SMAT3 * mate, SEMT1* emate, std::vector<BitmapTex*>* bt)
{
	int PID = -1;
	IParamBlock2 *PB = BaseMat->GetParamBlock(0);
	ParamBlockDesc2* desc = PB->GetDesc();
	int NP = desc->Count();
	ParamDef mc;
	PB->SetValue(desc->NameToIndex(L"bNoSpecularBloom"), 0, bNoSpecularBloom, 0);

	bNoBaseMaterialSpecular = material_is_specular & mate->material_flags ? false : true;
	PB->SetValue(desc->NameToIndex(L"bNoBaseMaterialSpecular"), 0, bNoBaseMaterialSpecular, 0);

	bmaterial_has_a_diffuse_texture = material_has_a_diffuse_texture & mate->material_flags ? true : false;
	bmaterial_has_a_bumpmap_texture = material_has_a_bumpmap_texture & mate->material_flags ? true : false;
	bmaterial_has_a_specular_texture = material_has_a_specular_texture & mate->material_flags ? true : false;

	bHasDetailMap = material_has_a_detail_texture & mate->material_flags ? true : false;
	PB->SetValue(desc->NameToIndex(L"bHasDetailMap"), 0, bHasDetailMap, 0);

	bmaterial_has_a_reflection_texture = material_has_a_reflection_texture & mate->material_flags ? true : false;
	bUse_global_environment_map_as_reflection = Use_global_environment_map_as_reflection & mate->material_flags ? true : false;
	bmaterial_has_an_emissive_texture = material_has_an_emissive_texture & mate->material_flags ? true : false;

	bFresnelReflection = material_has_a_FresnelRamp_texture_Reflection & mate->material_flags ? true : false;
	PB->SetValue(desc->NameToIndex(L"bFresnelReflection"), 0, bFresnelReflection, 0);

	bFresnelDiffuse = material_has_a_FresnelRamp_texture_Diffuse & mate->material_flags ? true : false;
	PB->SetValue(desc->NameToIndex(L"bFresnelDiffuse"), 0, bFresnelDiffuse, 0);

	bFresnelSpecular = material_has_a_FresnelRamp_texture_Specular & mate->material_flags ? true : false;
	PB->SetValue(desc->NameToIndex(L"bFresnelSpecular"), 0, bFresnelSpecular, 0);

	if (bFresnelReflection || bFresnelDiffuse || bFresnelSpecular)
	{
		bHasFresnelRamp = true;
	}
	PB->SetValue(desc->NameToIndex(L"bHasFresnelRamp"), 0, bHasFresnelRamp, 0); 

	bUsePrecipOffset = Apply_offset_to_start_of_Precipitation & mate->material_flags ? true : false;
	PB->SetValue(desc->NameToIndex(L"bUsePrecipOffset"), 0, bUsePrecipOffset, 0);

	bUsePrecip = Take_into_account_Precipitation & mate->material_flags ? true : false;
	PB->SetValue(desc->NameToIndex(L"bUsePrecip"), 0, bUsePrecip, 0);

	bBlendInvBaseAlpha = Blend_environment_by_inverse_of_diffuse_alpha & mate->material_flags ? true : false;
	PB->SetValue(desc->NameToIndex(L"bBlendInvBaseAlpha"), 0, bBlendInvBaseAlpha, 0);

	bBlendInvSpecAlpha = Blend_environment_by_specular_map_alpha & mate->material_flags ? true : false;
	PB->SetValue(desc->NameToIndex(L"bBlendInvSpecAlpha"), 0, bBlendInvSpecAlpha, 0);

	bAssumeVerticalNormal = Assume_vertical_normal & mate->material_flags ? true : false;
	PB->SetValue(desc->NameToIndex(L"bAssumeVerticalNormal"), 0, bAssumeVerticalNormal, 0);

	bZWriteAlpha = Z_Write_alpha & mate->material_flags ? true : false;
	PB->SetValue(desc->NameToIndex(L"bZWriteAlpha"), 0, bZWriteAlpha, 0);

	bNoZWrite = No_Z_Write & mate->material_flags ? true : false;
	PB->SetValue(desc->NameToIndex(L"bNoZWrite"), 0, bNoZWrite, 0);

	bBloomCopy = Bloom_material_by_copying & mate->material_flags ? true : false;
	PB->SetValue(desc->NameToIndex(L"bBloomCopy"), 0, bBloomCopy, 0);

	bBloomModulate = Bloom_material_modulating_by_alpha & mate->material_flags ? true : false;
	PB->SetValue(desc->NameToIndex(L"bBloomModulate"), 0, bBloomModulate, 0);

	bVolume_shadow = Volume_shadow & mate->material_flags ? true : false;
	PB->SetValue(desc->NameToIndex(L"bVolume_shadow"), 0, bVolume_shadow, 0);

	bNoShadow = No_shadow & mate->material_flags ? true : false;
	PB->SetValue(desc->NameToIndex(L"bNoShadow"), 0, bNoShadow, 0);

	bZTestAlpha = Z_Test_Alpha & mate->material_flags ? true : false;
	PB->SetValue(desc->NameToIndex(L"bZTestAlpha"), 0, bZTestAlpha, 0);

	bFinalAlphaWrite = Set_final_alpha_value_at_render_time & mate->material_flags ? true : false;
	PB->SetValue(desc->NameToIndex(L"bFinalAlphaWrite"), 0, bFinalAlphaWrite, 0);

	bSkinned = Skinned_mesh & mate->material_flags ? true : false;
	PB->SetValue(desc->NameToIndex(L"bSkinned"), 0, bSkinned, 0);

	bAllowBloom = Allow_bloom & mate->material_flags ? true : false;
	PB->SetValue(desc->NameToIndex(L"bAllowBloom"), 0, bAllowBloom, 0);

	bAllowEmissiveBloom = Allow_emissive_bloom & mate->material_flags ? true : false;
	PB->SetValue(desc->NameToIndex(L"bAllowEmissiveBloom"), 0, bAllowEmissiveBloom, 0);

	bBlendDiffuseBaseAlpha = Blend_diffuse_by_diffuse_alpha & mate->material_flags ? true : false;
	PB->SetValue(desc->NameToIndex(L"bBlendDiffuseBaseAlpha"), 0, bBlendDiffuseBaseAlpha, 0);

	bBlendDiffuseInvSpecAlpha = Blend_diffuse_by_inverse_of_specular_map_alpha & mate->material_flags ? true : false;
	PB->SetValue(desc->NameToIndex(L"bBlendDiffuseInvSpecAlpha"), 0, bBlendDiffuseInvSpecAlpha, 0);

	bPrelitVertices = Prelit_vertices & mate->material_flags ? true : false;
	PB->SetValue(desc->NameToIndex(L"bPrelitVertices"), 0, bPrelitVertices, 0);


	bBlendConstant = Blend_constant & mate->material_flags_2 ? true : false;
	PB->SetValue(desc->NameToIndex(L"bBlendConstant"), 0, bBlendConstant, 0);

	bForceTextureAddressWrap = Force_Texture_Address_Wrap & mate->material_flags_2 ? true : false;
	PB->SetValue(desc->NameToIndex(L"bForceTextureAddressWrap"), 0, bForceTextureAddressWrap, 0);

	bForceTextureAddressClamp = Force_Texture_Address_Clamp & mate->material_flags_2 ? true : false;
	PB->SetValue(desc->NameToIndex(L"bForceTextureAddressClamp"), 0, bForceTextureAddressClamp, 0);

	bDoubleSided = Double_sided & mate->material_flags_2 ? true : false;
	PB->SetValue(desc->NameToIndex(L"bDoubleSided"), 0, bDoubleSided, 0);

	bUseDetailAlphaAsBlendMask = UseDetailAlphaAsBlendMask & mate->material_flags_2 ? true : false;
	PB->SetValue(desc->NameToIndex(L"bUseDetailAlphaAsBlendMask"), 0, bUseDetailAlphaAsBlendMask, 0);


	iDetailScaleU = mate->detail_map_scale;
	PB->SetValue(desc->NameToIndex(L"iDetailScaleU"), 0, iDetailScaleU, 0);

	iBumpScale = mate->bump_map_scale;
	PB->SetValue(desc->NameToIndex(L"iBumpScale"), 0, iBumpScale, 0);

	iEnvLevelScale = mate->reflection_scale;
	PB->SetValue(desc->NameToIndex(L"iEnvLevelScale"), 0, iEnvLevelScale, 0);

	fPrecipOffset = mate->precipitation_offset;
	PB->SetValue(desc->NameToIndex(L"fPrecipOffset"), 0, fPrecipOffset, 0);

	fSpecMapPowerScale = mate->specular_map_power_scale;
	PB->SetValue(desc->NameToIndex(L"fSpecMapPowerScale"), 0, fSpecMapPowerScale, 0);

	fSpecularBloomFloor = mate->specular_bloom_floor;
	PB->SetValue(desc->NameToIndex(L"fSpecularBloomFloor"), 0, fSpecularBloomFloor, 0);

	fAmbientLightScale = mate->ambient_light_scale;
	PB->SetValue(desc->NameToIndex(L"fAmbientLightScale"), 0, fAmbientLightScale, 0);

	iSrcBlend = mate->source_blend;
	PB->SetValue(desc->NameToIndex(L"iSrcBlend"), 0, iSrcBlend, 0);

	iDstBlend = mate->destination_blend;
	PB->SetValue(desc->NameToIndex(L"iDstBlend"), 0, iDstBlend, 0);

	iAlphaTestMode = mate->alpha_test_function;
	PB->SetValue(desc->NameToIndex(L"iAlphaTestMode"), 0, iAlphaTestMode, 0);

	fAlphaTestLevel = mate->alpha_test_threshold;
	PB->SetValue(desc->NameToIndex(L"fAlphaTestLevel"), 0, fAlphaTestLevel, 0);

	fFinalAlphaWriteValue = mate->final_alpha_multiply;
	PB->SetValue(desc->NameToIndex(L"fFinalAlphaWriteValue"), 0, fFinalAlphaWriteValue, 0);

	fZBias = mate->zbias;
	PB->SetValue(desc->NameToIndex(L"fZBias"), 0, fZBias, 0);

	if (emate != NULL)
	{
		fTemperatureScale = emate->TemperatureScale;
		fDetailOffsetU = emate->DetailOffsetU;
		fDetailOffsetV = emate->DetailOffsetV;
		fDetailRotation = emate->DetailRotation;
		iDetailScaleV = emate->DetailScaleV;
		fDetailBlendWeight = emate->DetailBlendWeight;
		cDetailColor = Point4(emate->cDetailColor_R, emate->cDetailColor_G, emate->cDetailColor_B, emate->cDetailColor_A);
	}
	PB->SetValue(desc->NameToIndex(L"fTemperatureScale"), 0, fTemperatureScale, 0);
	PB->SetValue(desc->NameToIndex(L"fDetailOffsetU"), 0, fDetailOffsetU, 0);
	PB->SetValue(desc->NameToIndex(L"fDetailOffsetV"), 0, fDetailOffsetV, 0);
	PB->SetValue(desc->NameToIndex(L"fDetailRotation"), 0, fDetailRotation, 0);
	PB->SetValue(desc->NameToIndex(L"iDetailScaleV"), 0, iDetailScaleV, 0);
	PB->SetValue(desc->NameToIndex(L"fDetailBlendWeight"), 0, fDetailBlendWeight, 0);
	PB->SetValue(desc->NameToIndex(L"cDetailColor"), 0, cDetailColor, 0);
	
	if (Emissive_Mode_Blend & mate->material_flags)
	{
		iEmissiveMode = Blend;
	};
	if (Emissive_Mode_MultiplyBlend & mate->material_flags_2)
	{
		iEmissiveMode = MultiplyBlend;
	};
	if (Emissive_Mode_Additive & mate->material_flags_2)
	{
		iEmissiveMode = Additive;
	};
	if (Emissive_Mode_AdditiveNightOnlyUserControlled & mate->material_flags_2)
	{
		iEmissiveMode = AdditiveNightOnlyUserControlled;
	};
	if (Emissive_Mode_BlendUserControlled & mate->material_flags_2)
	{
		iEmissiveMode = BlendUserControlled;
	};
	if (Emissive_Mode_MultiplyBlendUserControlled & mate->material_flags_2)
	{
		iEmissiveMode = MultiplyBlendUserControlled;
	};
	if (Emissive_Mode_AdditiveUserControlled & mate->material_flags_2)
	{
		iEmissiveMode = AdditiveUserControlled;
	};
	PB->SetValue(desc->NameToIndex(L"iEmissiveMode"), 0, iEmissiveMode, 0);
	if (DetailBlendMode_Multiply & mate->material_flags_2)
	{
		iDetailBlendMode = Mode_Multiply;
	};
	if (DetailBlendMode_Blend & mate->material_flags_2)
	{
		iDetailBlendMode = Mode_Blend;
	};
	PB->SetValue(desc->NameToIndex(L"iDetailBlendMode"), 0, iDetailBlendMode, 0);

	//std::wstring widestr = std::wstring(bt->at(mate->diffuse_texture_index)->GetName().ToCStr());
	//const char* widecstr = bt->at(mate->diffuse_texture_index)->GetName().ToCStr()
	//std::string TexName = riff->TEXT->at(lMat.diffuse_texture_index);
	//std::wstring widestr = std::wstring(TexName.begin(), TexName.end());
	//const wchar_t* widecstr = widestr.c_str();
	//this->SetName(WStr(widecstr));
	if (bmaterial_has_a_diffuse_texture)
	{
		BaseMat->SetSubTexmap(3, bt->at(mate->diffuse_texture_index));
		if ((bZTestAlpha && ((iAlphaTestMode == greater) || (iAlphaTestMode == greaterEqual)) || ((iSrcBlend == srcAlpha) && (iDstBlend == invSrcAlpha))))
		{
			BaseMat->SetSubTexmap(8, bt->at(mate->diffuse_texture_index));
			//BaseMat->SetOpacity(fAlphaTestLevel / 255.0, 0);
		};
	}
	if (bmaterial_has_a_bumpmap_texture)
	{
		BaseMat->SetSubTexmap(10, bt->at(mate->bumpmap_texture_index));
	}
	if (bmaterial_has_a_specular_texture)
	{
		BaseMat->SetSubTexmap(4, bt->at(mate->specular_texture_index));
	}
	if (bmaterial_has_an_emissive_texture)
	{
		BaseMat->SetSubTexmap(7, bt->at(mate->emissive_texture_index));
	}
	if (bmaterial_has_a_reflection_texture)
	{
		BaseMat->SetSubTexmap(11, bt->at(mate->reflection_texture_index));
	}
	if (bHasFresnelRamp)
	{
		BaseMat->SetSubTexmap(0, bt->at(mate->fresnel_texture_index));
	}
	if (bHasDetailMap)
	{
		BaseMat->SetSubTexmap(1, bt->at(mate->detail_texture_index));
	}
	BaseMat->SetDiffuse(Color(mate->diffuse_color_R, mate->diffuse_color_G, mate->diffuse_color_B), 0);
	BaseMat->SetSpecular(Color(mate->specular_color_R, mate->specular_color_G, mate->specular_color_B), 0);
	return 0;
}

P3DMaterial::P3DMaterial()
{
}
