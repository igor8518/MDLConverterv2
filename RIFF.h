#pragma once

#include "Structures.h"
#include "MDLImport.h"
#include "ReadStream.h"
#include "WriteStream.h"

class MDLImport;

class RIFF
{

private:
	ReadStream* RIFFStream = NULL;
	WriteStreamText* RIFFText = NULL;
	UINT64 Seek = 0;
	
public:
	
	MDLImport* mdlImport;
	RIFF(MDLImport* mdlImport, const TCHAR* filename, ImpInterface * i, Interface * gi, int Type);
	~RIFF();
	wstring ModelName = L"";
	std::string ShortCode(std::string Code);
	std::vector<std::string> ConvertVisAnim(std::string std, int maxCount, int NamePar, int type);
	HRESULT ReadSectionsHierarhy();
	static UINT UINT2(char Name[4]);
	HRESULT ReadSection(int parent = 0);
	ImpInterface * i; 
	Interface * gi;
	
	
	SRIFFData RIFFData;
	SLODEData LODEData;
	SMDLH MDLH;
	SMDLG MDLG;
	SBBOX BBOX;
	float RADI;

	std::vector<std::wstring>* TEXT;
	std::vector<SMAT3>* MAT3;
	std::vector<SEMT1>* EMT1;
	std::vector<SIND3>* IND3;
	std::vector<SINDE>* INDE;
	std::vector<SVERB>* VERB;
	std::vector<SLODT>* LODT;
	std::vector<STRAN>* TRAN;
	std::vector<SSCEN>* SCEN;
	std::vector<SSGAL>* SGAL;
	std::vector<SSGBR>* SGBR;
	std::vector<SSGBN>* SGBN;
	std::vector<SSGVL>* SGVL;
	std::vector<SVISI>* VISI;
	std::vector<SAMAP>* AMAP;
	std::vector<SXANI>* XANI;
	std::vector<SREFP>* REFP;
	std::vector<SATTO>* ATTO;


	


	
	SXANI* CurrXANI = NULL;
	SXANS* CurrXANS = NULL;
	SLODT CurrLOD;
	SVERB CurrVERB;
	std::string MDLN;
	int UniVISI = 0;
	int UniXAPI = 0;
};

//extern BOOL DrawPart(RIFF* riff, SPART* part);
