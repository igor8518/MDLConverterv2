---------------------------------------------------------------------------
-- Prepar3D Extended Material Properties
---------------------------------------------------------------------------
plugin material Prepar3DPBR
    name:"Prepar3D PBR"
    classID:#(0x7aa36351, 0x6af37aff)
    extends:DirectX_9_Shader replaceUI:true
(
		parameters basicproperties rollout:basicproperties
		(
			cAlbedo type:#point4  ui:PAlbedoColor default:white
			fSmoothness	type:#float	ui:Smoothness	default:0
			fMetallic type:#float ui:Metallic	default:0
		)
		
		parameters maps rollout:maps
        (
			Albedo type:#texturemap ui:chooseAlbedo
			Metallic type:#texturemap ui:chooseMetallic
			Normal type:#texturemap ui:chooseNormal
			Emissive type:#texturemap ui:chooseEmissive
			Detail type:#texturemap ui:chooseDetail
		) 
		
        parameters properties rollout:properties
        (
			iRenderMode type:#integer ui:RenderMode default:1
                
			fMaskedThreshold   type:#float    ui:MaskedThreshold	default:0
			bAlphaToCoverage	type:#boolean  ui:AlphaToCoverage	default:false
			
			bHasOcclusion type:#boolean	ui:HasOcclusion	default:false
			bHasReflectance type:#boolean	ui:HasReflectance	default:false
			
			iSmoothnessSource type:#integer ui:SmoothnessSource default:2
			
			iEmissiveMode type:#integer ui:EmissiveMode default:1

			bAssumeVerticalNormal	type:#boolean	ui:bAssumeVerticalNormal	default:false
			bPrelit	type:#boolean	ui:bPrelit	default:false
			bDoubleSided	type:#boolean	ui:bDoubleSided	default:false
			iDecalOrder	type:#integer	ui:DecalOrder	default:0

			bIsPanelTexture	type:#boolean	ui:bIsPanelTexture	default:false
				
			szMaterialScript	type:#string	ui:txtMaterialScript	default:("")
        )
		
		rollout basicproperties "Basic Properties"
		(
			label lbl_AlbedoColor "Albedo:" align:#left across:2
			colorPicker PAlbedoColor "" align:#left width:80 height:60 offset:[0,0]
			spinner Metallic "Metallic:" align:#left offset:[0,0] type:#float width:100 range:[0.0,1.0,0.0] scale:0.01
			spinner Smoothness "Smoothness:" align:#left offset:[0,0] type:#float width:100 range:[0.0,1.0,0.0] scale:0.01
			
			on PAlbedoColor changed val do
			(
				delegate.g_Albedo = val
			)
			
			on Smoothness changed val do
			(
				delegate.g_Smoothness = val
			)
			
			on Metallic changed val do
			(
				delegate.g_Metallic = val
			)
		)
		
		rollout maps "Maps"
		(

			label lbl_Albedo "Albedo:" align:#left across:2
			mapbutton chooseAlbedo "None" align:#left width:110 offset:[0,0]
			
			label lbl_Metallic "Metallic:" align:#left across:2
			mapbutton chooseMetallic "None" align:#left width:110 offset:[0,0]
			
			label lbl_Normal "Normal:" align:#left across:2
			mapbutton chooseNormal "None" align:#left width:110 offset:[0,0]
			
			label lbl_Emissive "Emissive:" align:#left across:2
			mapbutton chooseEmissive "None" align:#left width:110 offset:[0,0]
			
			label lbl_Detail "Detail:" align:#left across:2
			mapbutton chooseDetail "None" align:#left width:110 offset:[0,0]
		)

        rollout properties "Properties"
        (
			group "Blend Properties"
			(
				dropdownlist RenderMode "Render Mode:" items:#("Opaque", "Masked", "Translucent")
			)
				
			group "Masked Properties"
			(
				spinner MaskedThreshold "MaskedThreshold:" align:#left offset:[0,0] type:#float width:100 range:[0.0,1.0,0.0] scale:0.01
				checkbox AlphaToCoverage "Use AlphaToCoverage"
			)
				
			group "Metallic Properties"
			(
				checkbox HasOcclusion "Metallic Map Has Occlusion"
				checkbox HasReflectance "Metallic Map Has Reflectance"
			)
				
			group "Smoothness Properties"
			(
				dropdownlist SmoothnessSource "Smoothness Source:" items:#("AlbedoAlpha" , "MetallicAlpha")
			)
				
			group "Emissive Properties"
			(
				dropdownlist EmissiveMode "Emissive Mode:" items:#("Additive" , "AdditiveNightOnly")
			)
                
			group "Script Properties"
			(
				editText txtMaterialScript "Script:" align:#left
				button buttonBrowseScript "Browse..." align:#right
			)

			group "Enhanced Properties"
			(
				checkbox bAssumeVerticalNormal "Assume vertical normal"
				checkbox bPrelit "Prelit"
				checkbox bDoubleSided "Double sided"
				spinner DecalOrder "Decal Order:" align:#left offset:[0,0] type:#integer width:100 range:[0,255,0] scale:1
			)

			group "Aircraft Properties"
			(
				checkbox bIsPanelTexture "Is virtual cockpit panel texture"
			)
			
			on RenderMode selected val do
			(
				if val == 2 then
				(
					delegate.g_Masked = true
				)
				else
				(
					delegate.g_Masked = false
				)
			)
			
			on MaskedThreshold changed val do
			(
				delegate.g_MaskedThreshold = val
			)
			
			on HasOcclusion changed val do
			(
				delegate.g_MetallicHasOcclusion = val
			)
            
			on HasReflectance changed val do
			(
				delegate.g_MetallicHasReflectance = val
			)
			
			on SmoothnessSource selected val do
			(
				if val == 1 then
				(
					delegate.g_AlbedoHasSmoothness = true
				)
				else
				(
					delegate.g_AlbedoHasSmoothness = false
				)
			)
			
			on EmissiveMode selected val do
			(
				if val == 2 then
				(
					delegate.g_EmissiveNightOnly = true
				)
				else
				(
					delegate.g_EmissiveNightOnly = false
				)
			)
			
			on buttonBrowseScript pressed do
			(
				local scriptFile = getOpenFileName caption:"Please locate the material script you would like to apply." types:"LUA Script files (*.lua)|*.lua"
                    
				if scriptFile != undefined then
				(
					txtMaterialScript.text = (getFileNameFile scriptFile as string) + ".lua"
				)
			)
			
			on bAssumeVerticalNormal changed val do
			(
				delegate.g_AssumeVerticalNormal = val
			)
			
			on bPrelit changed val do
			(
				delegate.g_Prelit = val
			)
        )
		
		--This function should never change properties if they are not different.
		fn UpdateDirectXProperties =
		(
			if Albedo != undefined then
			(
				try
				(
					if delegate.g_AlbedoTexture == undefined or delegate.g_AlbedoTexture.filename != Albedo.filename then
						delegate.g_AlbedoTexture = Albedo.bitmap
					
					if delegate.g_UseAlbedoTexture != true then 
						delegate.g_UseAlbedoTexture = true
				)
				catch
				(
					if delegate.g_UseAlbedoTexture != false then
						delegate.g_UseAlbedoTexture = false
				)
				
				if Albedo.coordinates.mapChannel == 1 and delegate.g_AlbedoUV2Channel2 != false then
				(
					delegate.g_AlbedoUV2Channel2 = false
				)
				else if Albedo.coordinates.mapChannel == 2 and delegate.g_AlbedoUV2Channel2 != true then
				(
					delegate.g_AlbedoUV2Channel2 = true
				)
				
				fileType = getFilenameType Albedo.filename
				if fileType == ".dds" then
				(
					if delegate.g_AlbedoFlipV != true then
						delegate.g_AlbedoFlipV = true
				)
				else
				(
					if delegate.g_AlbedoFlipV != false then
						delegate.g_AlbedoFlipV = false
				)
				
				if delegate.g_AlbedoTileU != Albedo.coordinates.U_Tiling then
					delegate.g_AlbedoTileU = Albedo.coordinates.U_Tiling
				
				if delegate.g_AlbedoTileV != Albedo.coordinates.V_Tiling then
					delegate.g_AlbedoTileV = Albedo.coordinates.V_Tiling
			)
			else
			(
				if delegate.g_UseAlbedoTexture != false then
					delegate.g_UseAlbedoTexture = false
				
				if delegate.g_AlbedoTexture != undefined and delegate.g_AlbedoTexture.filename != "" then
					delegate.g_AlbedoTexture.filename = ""
			)
				
			if Metallic != undefined then
			(
				try
				(
					if delegate.g_MetallicTexture == undefined or delegate.g_MetallicTexture.filename != Metallic.filename then
						delegate.g_MetallicTexture = Metallic.bitmap
					
					if delegate.g_UseMetallicTexture != true then 
						delegate.g_UseMetallicTexture = true
				)
				catch
				(
					if delegate.g_UseMetallicTexture != false then 
						delegate.g_UseMetallicTexture = false
				)
				
				if Metallic.coordinates.mapChannel == 1 and delegate.g_MetallicUV2Channel2 != false then
				(
					delegate.g_MetallicUV2Channel2 = false
				)
				else if Metallic.coordinates.mapChannel == 2 and delegate.g_MetallicUV2Channel2 != true then
				(
					delegate.g_MetallicUV2Channel2 = true
				)
				
				fileType = getFilenameType Metallic.filename
				if fileType == ".dds" then
				(
					if delegate.g_MetallicFlipV != true then
						delegate.g_MetallicFlipV = true
				)
				else
				(
					if delegate.g_MetallicFlipV != false then
						delegate.g_MetallicFlipV = false
				)
			)
			else
			(
				if delegate.g_UseMetallicTexture != false then 
					delegate.g_UseMetallicTexture = false
				
				if delegate.g_MetallicTexture != undefined and delegate.g_MetallicTexture.filename != "" then
					delegate.g_MetallicTexture.filename = ""
			)
				
			if Normal != undefined then
			(
				try
				(
					if delegate.g_NormalTexture == undefined or delegate.g_NormalTexture.filename!= Normal.filename then
						delegate.g_NormalTexture = Normal.bitmap
										
					if delegate.g_UseNormalTexture != true then 
						delegate.g_UseNormalTexture = true
				)
				catch
				(
					if delegate.g_UseNormalTexture != false then 
						delegate.g_UseNormalTexture = false
				)

				if Normal.coordinates.mapChannel == 1 and delegate.g_NormalUV2Channel2 != false then
				(
					delegate.g_NormalUV2Channel2 = false
				)
				else if Normal.coordinates.mapChannel == 2 and delegate.g_NormalUV2Channel2 != true then
				(
					delegate.g_NormalUV2Channel2 = true
				)
				
				fileType = getFilenameType Normal.filename
				if fileType == ".dds" then
				(
					if delegate.g_NormalFlipV != true then
						delegate.g_NormalFlipV = true
				)
				else
				(
					if delegate.g_NormalFlipV != false then
						delegate.g_NormalFlipV = false
				)
				
				if delegate.g_NormalTileU != Normal.coordinates.U_Tiling then
					delegate.g_NormalTileU = Normal.coordinates.U_Tiling
				
				if delegate.g_NormalTileV != Normal.coordinates.V_Tiling then
					delegate.g_NormalTileV = Normal.coordinates.V_Tiling
			)
			else
			(
				if delegate.g_UseNormalTexture != false then
					delegate.g_UseNormalTexture = false
				
				if delegate.g_NormalTexture != undefined and delegate.g_NormalTexture.filename != "" then
					delegate.g_NormalTexture.filename = ""
			)
					
			if Emissive != undefined then
			(
				try
				(
					if delegate.g_EmissiveTexture == undefined or delegate.g_EmissiveTexture.filename != Emissive.filename then
						delegate.g_EmissiveTexture = Emissive.bitmap
										
					if delegate.g_UseEmissiveTexture != true then 
						delegate.g_UseEmissiveTexture = true
				)
				catch
				(
					if delegate.g_UseEmissiveTexture != false then
						delegate.g_UseEmissiveTexture = false
				)
				
				if Emissive.coordinates.mapChannel == 1 and delegate.g_EmissiveUV2Channel2 != false then
				(
					delegate.g_EmissiveUV2Channel2 = false
				)
				else if Emissive.coordinates.mapChannel == 2 and delegate.g_EmissiveUV2Channel2 != true then
				(
					delegate.g_EmissiveUV2Channel2 = true
				)
				
				fileType = getFilenameType Emissive.filename
				if fileType == ".dds" then
				(
					if delegate.g_EmissiveFlipV != true then
						delegate.g_EmissiveFlipV = true
				)
				else
				(
					if delegate.g_EmissiveFlipV != false then
						delegate.g_EmissiveFlipV = false
				)
			)
			else
			(
				if delegate.g_UseEmissiveTexture != false then
					delegate.g_UseEmissiveTexture = false
				
				if delegate.g_EmissiveTexture != undefined and delegate.g_EmissiveTexture.filename != "" then
					delegate.g_EmissiveTexture.filename = ""
			)
						
			if Detail != undefined then
			(
				try
				(
					if delegate.g_DetailTexture == undefined or delegate.g_DetailTexture.filename != Detail.filename then
						delegate.g_DetailTexture = Detail.bitmap
									
					if delegate.g_UseDetailTexture != true then 
						delegate.g_UseDetailTexture = true
				)
				catch
				(
					if delegate.g_UseDetailTexture != false then
						delegate.g_UseDetailTexture = false
				)

				if Detail.coordinates.mapChannel == 1 and delegate.g_DetailUV2Channel2 != false then
				(
					delegate.g_DetailUV2Channel2 = false
				)
				else if Detail.coordinates.mapChannel == 2 and delegate.g_DetailUV2Channel2 != true then
				(
					delegate.g_DetailUV2Channel2 = true
				)
				
				fileType = getFilenameType Detail.filename
				if fileType == ".dds" then
				(
					if delegate.g_DetailFlipV != true then
						delegate.g_DetailFlipV = true
				)
				else
				(
					if delegate.g_DetailFlipV != false then
						delegate.g_DetailFlipV = false
				)
				
				if delegate.g_DetailTileU != Detail.coordinates.U_Tiling then
					delegate.g_DetailTileU = Detail.coordinates.U_Tiling
				
				if delegate.g_DetailTileV != Detail.coordinates.V_Tiling then
					delegate.g_DetailTileV = Detail.coordinates.V_Tiling
			)
			else
			(
				if delegate.g_UseDetailTexture != false then
					delegate.g_UseDetailTexture = false
				
				if delegate.g_DetailTexture != undefined and delegate.g_DetailTexture.filename != "" then
					delegate.g_DetailTexture.filename = ""
			)
		)
        
		on create do
		(
			delegate.effectFile = acesArtTools + "MaxHLSL\PBRBase.fx"
			
			delegate.g_BrdfLutTexture = openBitmap (acesArtTools + "Images\PBRBrdfLut.bmp")
			delegate.g_RadianceCube = openBitmap (acesArtTools + "Images\GlobalEnvTest.dds")
			
			UpdateDirectXProperties()
		)
        
		on load do
		(
            -- Make sure the effectFile property is present
            if classOf delegate == DirectX_9_Shader then
            (
                delegate.effectFile = acesArtTools + "MaxHLSL\PBRBase.fx"
            
                delegate.g_BrdfLutTexture = openBitmap (acesArtTools + "Images\PBRBrdfLut.bmp")
                delegate.g_RadianceCube = openBitmap (acesArtTools + "Images\GlobalEnvTest.dds")
                
                UpdateDirectXProperties()
            )
		)
)

callbackItem = undefined
gc light:true
fn UpdatePBRMaterials ev nds =
(
	--format "UpdatePBRMaterials %\n" ev
	--st = timestamp()
    for n in nds do
    (
        obj = GetAnimByHandle n
        
        if IsValidNode obj then
        (
            if obj.material != undefined then
            (
                if classOf obj.material == Prepar3DPBR then
                (
                    obj.material.UpdateDirectXProperties()
                )
                else if classOf obj.material == multiMaterial then
                (
                    for subM in obj.material.materialList do
                    (
                        if classOf subM == Prepar3DPBR then
                        (
                            subM.UpdateDirectXProperties()
                        )
                    )
                )
            )
        )
    )
	--format "%ms \n" (timestamp()-st)
)
callbackItem = NodeEventCallback mouseUp:true delay:10 materialOtherEvent:UpdatePBRMaterials materialStructured:UpdatePBRMaterials