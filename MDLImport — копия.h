#pragma once


#include "Structures.h"
#include "RIFF.h"
#include "P3DMaterial.h"

using namespace std;

class RIFF;

class MDLImport
{

public:
	MDLImport(const TCHAR * filename, ImpInterface * i, Interface * gi, BOOL suppressPrompts);
	~MDLImport();

	double				deg2rad(double degrees);
	std::wstring*		GetRegKey(HKEY hKey, std::wstring subKey, std::wstring valueName);
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
	INode* node = NULL;
	INode* rootNode = NULL;

	

	unique_ptr<ImpInterface> i;
	unique_ptr<Interface> gi;
	unique_ptr<wstring> filename;

	unique_ptr<wstring> ModelName;// = L"";

	unique_ptr<INode> OneNode;
	unique_ptr<INode> BoneNode;
	unique_ptr<Matrix3> tmO;// = Matrix3(1);
	unique_ptr<Matrix3> tmR;// = Matrix3(1);

	

	unique_ptr<std::vector<SParts>> NodeParts;// = new std::vector<SParts>();
	unique_ptr<vector<INode*>> Bones;// = new std::vector<INode*>();
	unique_ptr<vector<StdMat2*>> Mtls;// = new std::vector<StdMat2*>();
	unique_ptr<vector<std::wstring>> Textures;// = new std::vector<std::wstring>();
	//BitmapTex* bmt = NULL;

	int NodeIndex = -1;
	int Parts = 0;

	unique_ptr<wstring> ModelDefXML;// (new wstring(L""));// (new std::wstring(L""));
	unique_ptr<wstring> EffectPath;//  (new wstring(L""));// (new wstring(L""));
	unique_ptr<wstring> ImageTool;//   (new wstring(L""));// (new wstring(L""));

	SModelDefXML ModelXML;
	SModelDefXML ModelXMLOut;

	unique_ptr<wstring> StartUD;// = L"FSXML = <?xml version=\"1.0\" encoding=\"ISO-8859-1\" ?> <FSMakeMdlData version=\"9.0\"> ";
	unique_ptr<wstring> EndUD;// = L" </FSMakeMdlData>";

	unique_ptr<int> pi;
	

	RIFF* riff;
protected:
	unique_ptr<vector<SAnimation>> AnimationXML;
	unique_ptr<vector<SPartInfo>> PartInfoXML;
	unique_ptr<std::vector<UINT>> BadSec;
};

