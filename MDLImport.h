#pragma once


#include "Structures.h"
#include "RIFF.h"
#include "P3DMaterial.h"
#include "PBRMaterial.h"

using namespace std;

class RIFF;

class MDLImport
{

public:
	MDLImport(const TCHAR * filename, ImpInterface * i, Interface * gi, BOOL suppressPrompts);
	
	~MDLImport();

	double				deg2rad(double degrees);
	std::wstring		GetRegKey(HKEY hKey, std::wstring subKey, std::wstring valueName);
	int					GetPaths();
	SModelDefXML		ReadModelDef();
	void				SetControllerKeys(Control * cont, SXANK * keys, int type, int ctt, int ct);
	std::string			BytesToGUID(byte b[16]);
	std::wstring		SetAnim(INode * node, int CurrNode);
	INode*				DrawPart(SPART * part, int LOD, int PartNo, std::wstring nameAnim, int nodeIndex, std::wstring LODStr);
	Matrix3				AddTM(STRAN tran, Matrix3 tm);
	Matrix3				CalcTransform(int StartIndex, int useTMO);
	std::vector<float>	GetArrFromString(LPWSTR str);
	INode *				CreateBone(int CurrNode, int ParentNodeIndex, INode * ParentBone);
	int					CheckParts(int CurrNode);
	bool				FindGraph(int CurrNode, int findGraph, std::vector<int>* grafs);
	BOOL				CreateNode(int CurrNode, int ParentNodeIndex, INode * ParentNode, INode * ParentBone, INode * ParentPart, int LOD, std::wstring nameAnim);
	BOOL				SetSkin();
	BOOL				objFileRead(const TCHAR * filename, Mesh * mesh);
	bool FindAndCopyTextures();
	bool				CreateMtlLib();
	INode *				CreateDummy(std::wstring name);
	//INode* node = NULL;
	INode* rootNode = NULL;

	

	ImpInterface* i;
	Interface* gi;
	wstring* filename;

	wstring ModelName = L"";

	INode* OneNode;
	INode* BoneNode;
	Matrix3 tmO = Matrix3(1);
	Matrix3 tmR = Matrix3(1);

	

	std::vector<SParts>* NodeParts = new std::vector<SParts>();
	vector<INode*>* Bones = new std::vector<INode*>();
	vector<Mtl*>* Mtls = new std::vector<Mtl*>();
	vector<std::wstring>* Textures = new std::vector<std::wstring>();
	//BitmapTex* bmt = NULL;

	int NodeIndex = -1;
	int Parts = 0;

	wstring ModelDefXML = L"";// (new std::wstring(L""));
	wstring EffectPath = L"";// (new wstring(L""));
	wstring ImageTool = L"";// (new wstring(L""));

	SModelDefXML ModelXML;
	SModelDefXML ModelXMLOut;

	wstring StartUD = L"FSXML = <?xml version=\"1.0\" encoding=\"ISO-8859-1\" ?> <FSMakeMdlData version=\"9.0\"> ";
	wstring EndUD = L" </FSMakeMdlData>";

	int pi;
	

	RIFF* riff;
protected:
	void DelMem(void** p);
	vector<SAnimation>* AnimationXML = NULL;
	vector<SPartInfo>* PartInfoXML = NULL;
	std::vector<UINT>* BadSec = NULL;
};

