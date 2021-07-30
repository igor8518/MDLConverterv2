#include "MDLImport.h"
using namespace std;

std::wstring MDLImport::GetRegKey(HKEY hKey, std::wstring subKey, std::wstring valueName)
{
	HKEY rKey;
	WCHAR Reget[512];
	DWORD RegetPath = sizeof(Reget);
	RegOpenKeyEx(hKey, subKey.c_str(), 0, KEY_QUERY_VALUE, &rKey);
	RegQueryValueEx(rKey, valueName.c_str(), NULL, NULL, LPBYTE(Reget), &RegetPath);
	RegCloseKey(rKey);
	if (Reget[lstrlen(Reget) - 1] == L'\\')
	{
		Reget[lstrlen(Reget) - 1] = L'\0';
	}
	return wstring(Reget);
}


int MDLImport::GetPaths()
{
	wstring value = L"";

	value = GetRegKey(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Lockheed Martin\\Prepar3D v5", L"SetupPath");
	if (value == L"")
	{
		return -1;
	}
	EffectPath = value + L"\\Effects\\";
	value = GetRegKey(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Lockheed Martin\\Prepar3D v5 SDK", L"SetupPath");
	if (value == L"")
	{
		return -1;
	}
	ImageTool = value + L"\\ImageTool.exe";
	ModelDefXML = value + L"\\Modeling\\3ds Max\\bin\\modeldef.xml";

	return 0;
}

SModelDefXML MDLImport::ReadModelDef()
{
	SModelDefXML lModelDefXml;
	if (AnimationXML) {
		AnimationXML->clear();
	} 
	else {
		AnimationXML = new std::vector<SAnimation>();
	}
	if (PartInfoXML) {
		PartInfoXML->clear();
	}
	else {
		PartInfoXML = new std::vector<SPartInfo>();
	}
	//BadSec.reset(new std::vector<UINT>());
	

	pugi::xml_document doc;
	pugi::xml_parse_result result = doc.load_file(ModelDefXML.c_str());
	pugi::xml_node ModelInfo = doc.child("ModelInfo");


	for (pugi::xml_node Animation = ModelInfo.child("Animation"); Animation; Animation = Animation.next_sibling("Animation"))
	{
		SAnimation AnimTemp;
		AnimTemp.name = Animation.attribute("name").value();
		AnimTemp.guid = Animation.attribute("guid").value();

		AnimTemp.length = std::strcmp(Animation.attribute("length").value(), "") ? std::stof(Animation.attribute("length").value()) : 0.0;

		AnimTemp.type = std::strcmp(Animation.attribute("type").value(), "Standard") ? Sim : Standard;
		AnimTemp.typeParam = Animation.attribute("typeParam").value();
		AnimTemp.typeParam2 = Animation.attribute("typeParam2").value();
		AnimationXML->push_back(AnimTemp);
	}
	for (pugi::xml_node PartInfo = ModelInfo.child("PartInfo"); PartInfo; PartInfo = PartInfo.next_sibling("PartInfo"))
	{
		SPartInfo PartTemp;
		PartTemp.Name = PartInfo.child("Name").child_value();
		if (PartInfo.child("Copy"))
		{
			PartTemp.Copy = PartInfo.child("Copy").child_value();
		}
		if (PartInfo.child("AnimLength"))
		{
			PartTemp.AnimLength = std::atoi(PartInfo.child("AnimLength").child_value());
		}
		pugi::xml_node AnimXML = PartInfo.child("Animation");
		if (AnimXML)
		{
			PartTemp.AnimationF = true;
			if (AnimXML.child("Parameter").child("Code"))
			{
				PartTemp.Animation.Parameter.CodeF = true;
				PartTemp.Animation.Parameter.Code = AnimXML.child("Parameter").child("Code").child_value();
			}
			if (AnimXML.child("Parameter").child("Sim"))
			{
				PartTemp.Animation.Parameter.SimF = true;
				if (AnimXML.child("Parameter").child("Sim").child("Variable"))
				{
					PartTemp.Animation.Parameter.Sim.Variable = AnimXML.child("Parameter").child("Sim").child("Variable").child_value();
				}
				if (AnimXML.child("Parameter").child("Sim").child("Units"))
				{
					PartTemp.Animation.Parameter.Sim.Units = AnimXML.child("Parameter").child("Sim").child("Units").child_value();
				}
				if (AnimXML.child("Parameter").child("Sim").child("Scale"))
				{
					PartTemp.Animation.Parameter.Sim.ScaleF = true;
					PartTemp.Animation.Parameter.Sim.Scale = std::atof(AnimXML.child("Parameter").child("Sim").child("Scale").child_value());
				}
				if (AnimXML.child("Parameter").child("Sim").child("Bias"))
				{
					PartTemp.Animation.Parameter.Sim.BiasF = true;
					PartTemp.Animation.Parameter.Sim.Bias = std::atoi(AnimXML.child("Parameter").child("Sim").child("Bias").child_value());
				}
			}
			if (AnimXML.child("Parameter").child("Lag"))
			{
				PartTemp.Animation.Parameter.LagF = true;
				PartTemp.Animation.Parameter.Lag = atoi(AnimXML.child("Parameter").child("Lag").child_value());
			}
		}
		pugi::xml_node VisXML = PartInfo.child("Visibility");
		if (VisXML)
		{
			PartTemp.VisibleF = true;
			if (VisXML.child("Parameter").child("Code"))
			{
				PartTemp.Visible.Parameter.CodeF = true;
				PartTemp.Visible.Parameter.Code = VisXML.child("Parameter").child("Code").child_value();
			}
			if (VisXML.child("Parameter").child("Sim"))
			{
				PartTemp.Visible.Parameter.SimF = true;
				if (VisXML.child("Parameter").child("Sim").child("Variable"))
				{
					PartTemp.Visible.Parameter.Sim.Variable = VisXML.child("Parameter").child("Sim").child("Variable").child_value();
				}
				if (VisXML.child("Parameter").child("Sim").child("Units"))
				{
					PartTemp.Visible.Parameter.Sim.Units = VisXML.child("Parameter").child("Sim").child("Units").child_value();
				}
				if (VisXML.child("Parameter").child("Sim").child("Scale"))
				{
					PartTemp.Visible.Parameter.Sim.ScaleF = true;
					PartTemp.Visible.Parameter.Sim.Scale = std::atof(VisXML.child("Parameter").child("Sim").child("Scale").child_value());
				}
				if (VisXML.child("Parameter").child("Sim").child("Bias"))
				{
					PartTemp.Visible.Parameter.Sim.BiasF = true;
					PartTemp.Visible.Parameter.Sim.Bias = std::atoi(VisXML.child("Parameter").child("Sim").child("Bias").child_value());
				}
			}
			if (AnimXML.child("Parameter").child("Lag"))
			{
				PartTemp.Visible.Parameter.LagF = true;
				PartTemp.Visible.Parameter.Lag = atoi(AnimXML.child("Parameter").child("Lag").child_value());
			}
		}
		pugi::xml_node VisRXML = PartInfo.child("VisibleInRange");
		if (VisRXML)
		{
			PartTemp.VisibleInRangeF = true;
			if (VisRXML.child("Parameter").child("Code"))
			{
				PartTemp.VisibleInRange.Parameter.CodeF = true;
				PartTemp.VisibleInRange.Parameter.Code = VisRXML.child("Parameter").child("Code").child_value();
			}
			if (VisRXML.child("Parameter").child("Sim"))
			{
				PartTemp.VisibleInRange.Parameter.SimF = true;
				if (VisRXML.child("Parameter").child("Sim").child("Variable"))
				{
					PartTemp.VisibleInRange.Parameter.Sim.Variable = VisRXML.child("Parameter").child("Sim").child("Variable").child_value();
				}
				if (VisRXML.child("Parameter").child("Sim").child("Units"))
				{
					PartTemp.VisibleInRange.Parameter.Sim.Units = VisRXML.child("Parameter").child("Sim").child("Units").child_value();
				}
				if (VisRXML.child("Parameter").child("Sim").child("Scale"))
				{
					PartTemp.VisibleInRange.Parameter.Sim.ScaleF = true;
					PartTemp.VisibleInRange.Parameter.Sim.Scale = std::atof(VisRXML.child("Parameter").child("Sim").child("Scale").child_value());
				}
				if (VisRXML.child("Parameter").child("Sim").child("Bias"))
				{
					PartTemp.VisibleInRange.Parameter.Sim.BiasF = true;
					PartTemp.VisibleInRange.Parameter.Sim.Bias = std::atoi(VisRXML.child("Parameter").child("Sim").child("Bias").child_value());
				}
			}
			if (AnimXML.child("Parameter").child("Lag"))
			{
				PartTemp.VisibleInRange.Parameter.LagF = true;
				PartTemp.VisibleInRange.Parameter.Lag = atoi(AnimXML.child("Parameter").child("Lag").child_value());
			}
		}
		PartInfoXML->push_back(PartTemp);
	}
	lModelDefXml.AnimationXML	= AnimationXML;
	lModelDefXml.PartInfoXML	= PartInfoXML;
	lModelDefXml.BadSec			= BadSec;
	return lModelDefXml;
}

MDLImport::MDLImport(const TCHAR* filename, ImpInterface* i, Interface* gi, BOOL suppressPrompts)
{
	this->i = i;
	this->gi = gi;
	this->filename = new wstring(filename);

	//pi = new int(1);
	/*ModelDefXML = wstring(L"");
	EffectPath = new wstring(L"");
	ImageTool = new wstring(L"");
	StartUD = wstring(L"FSXML = <?xml version=\"1.0\" encoding=\"ISO-8859-1\" ?> <FSMakeMdlData version=\"9.0\"> ");
	EndUD = wstring(L" </FSMakeMdlData>");*/
	//tmO = Matrix3();
	BadSec = new vector<UINT>();
	//Textures = new vector<std::wstring>();
	//NodeParts = new std::vector<SParts>();
	Mtls = new std::vector<Mtl*>();

	GetPaths();
	ModelXML = ReadModelDef();

	riff = new RIFF(this, filename, i, gi, 1);



	ModelName = riff->ModelName;

	tmO.RotateX(deg2rad(90.0));
	//FindAndCopyTextures();
	CreateMtlLib();

	INode* nodeExt = CreateDummy(ModelName);

	for (int j = 0; j < riff->LODT->size(); j++)
	{
		INode* nodeLOD = CreateDummy(ModelName + L"_LOD_" + std::to_wstring(riff->LODT->at(j).LOD));
		nodeExt->AttachChild(nodeLOD);
		CreateNode(0, -1, nodeLOD, NULL, NULL, j, L"");
		SetSkin();
	}


	
}

void MDLImport::DelMem(void** p)
{
	if (*p) {
		delete *p;
		*p = NULL;
	}
}


MDLImport::~MDLImport()
{
	DelMem((void**)&AnimationXML);
	DelMem((void**)&PartInfoXML);
	DelMem((void**)&riff);
	DelMem((void**)&BadSec);
	DelMem((void**)&Mtls);
}



double MDLImport::deg2rad(double degrees) {
	return degrees * 4.0 * atan(1.0) / 180.0;
}




void MDLImport::SetControllerKeys(Control *cont, SXANK *keys, int type, int ctt, int ct)
{
	SXANK *ptr = keys;
	//int ct = 0;
	ILinPoint3Key pkey;
	ILinRotKey rkey;
	IKey *k;

	// Set up 'k' to point at the right derived class
	switch (type) {
	case KEY_POS: k = &pkey; break;
	case KEY_ROT: k = &rkey; break;
	default: return;
	}

	// Count how many keys we got.
	//ct = 1;

	// Special case where there is only one key at frame 0.
	// Just set the controller's value
	if (ct == 2 && keys->time == 0) {
		switch (type) {

		case KEY_POS: {
			Point3 p(
				keys->x,
				keys->y,
				keys->z);
			cont->SetValue(0, &p);
			break;
		}
		case KEY_ROT: {
			Quat q(
				keys->q0,
				keys->q1,
				keys->q2,
				keys->q3
			);
			cont->SetValue(0, &q);
			break;
		}
		}
		return;
	}
	// Make sure we can get the interface and have some keys
	IKeyControl *ikeys = GetKeyControlInterface(cont);
	if (!ikeys) return;

	// Allocate the keys in the table
	ikeys->SetNumKeys(ctt);

	ptr = keys;
	//while (ptr) 

	{
		// Set the common values
		k->time = ptr->time * GetTicksPerFrame();

		// Set the key type specific values
		switch (type) {

		case KEY_POS:
			pkey.val[0] = ptr->x;
			pkey.val[1] = ptr->y;
			pkey.val[2] = -ptr->z;
			break;

		case KEY_ROT:
			rkey.val[3] = -ptr->q3;
			rkey.val[2] = ptr->q2;
			rkey.val[1] = -ptr->q1;
			rkey.val[0] = -ptr->q0;

			break;
		}
		ikeys->SetKey(ct, k);
	}
}



std::string MDLImport::BytesToGUID(byte b[16])
{
	char ss[37];
	sprintf(ss, "% 2.2X% 2.2X% 2.2X% 2.2X-% 2.2X% 2.2X-% 2.2x% 2.2x-% 2.2X% 2.2X-% 2.2X% 2.2X% 2.2X% 2.2X% 2.2X% 2.2X",
		b[3],
		b[2],
		b[1],
		b[0],
		b[5],
		b[4],
		b[7],
		b[6],
		b[8],
		b[9],
		b[10],
		b[11],
		b[12],
		b[13],
		b[14],
		b[15]);
	ss[36] = '\0';
	return std::string(ss, 37);
}


std::wstring MDLImport::SetAnim(INode* node, int CurrNode)
{

	int xanimInd = riff->SGAL->at(riff->SCEN->at(CurrNode).amap_offset / 8).xanim;
	std::wstring nameAnim = L"";
	if (xanimInd >= 0)
	{
		Control* c;
		c = node->GetTMController()->GetPositionController();
		if (c && c->ClassID() != Class_ID(LININTERP_POSITION_CLASS_ID, 0)) {
			Control *tcb = (Control*)riff->gi->CreateInstance(
				CTRL_POSITION_CLASS_ID,
				Class_ID(LININTERP_POSITION_CLASS_ID, 0));
			if (!node->GetTMController()->SetPositionController(tcb)) {
				tcb->DeleteThis();
			}
		}

		c = node->GetTMController()->GetRotationController();
		if (c && c->ClassID() != Class_ID(LININTERP_ROTATION_CLASS_ID, 0)) {
			Control *tcb = (Control*)riff->gi->CreateInstance(
				CTRL_ROTATION_CLASS_ID,
				Class_ID(LININTERP_ROTATION_CLASS_ID, 0));
			if (!node->GetTMController()->SetRotationController(tcb)) {
				tcb->DeleteThis();
			}
		}
		nameAnim = L"NA";
		for (int i = 0; i < riff->XANI->size(); i++)
		{

			for (int j = 0; j < riff->XANI->at(i).XANS->size(); j++)
			{
				SXANS xans = riff->XANI->at(i).XANS->at(j);
				if (xanimInd == riff->XANI->at(i).XANS->at(j).animation_ID)
				{

					if (node->GetTMController())
					{
						if (nameAnim == L"NA")
						{
							SuspendAnimate();
							AnimateOn();
							std::string ss = BytesToGUID(riff->XANI->at(i).guid);


							nameAnim = std::wstring(riff->XANI->at(i).XAPI.name.begin(), riff->XANI->at(i).XAPI.name.end());


							/////////////////////////////////////


							Control *TControl = node->GetTMController();
							DefNoteTrack* nt = new DefNoteTrack();
							TControl->AddNoteTrack(nt);
							nt->AddNewKey(0, 0);
							nt->AddNewKey(0, 0);
							NoteKeyTab keys;
							keys.Init();
							std::wstring anStart = L"ANIM_START = \"" + nameAnim + L"\"";
							std::wstring anEnd = L"ANIM_END = \"" + nameAnim + L"\"";
							NoteKey* nk = new NoteKey(0, anStart.c_str());
							nk->time = 0;
							keys.Append(1, &nk);

							nk = new NoteKey(0, anEnd.c_str());

							nk->time = riff->XANI->at(i).animation_length * GetTicksPerFrame();
							keys.Append(1, &nk);

							nt->keys = keys;
						}
						////////////////////////////////////////


						for (int k = 0; k < xans.XANK->size(); k++)
						{
							if (xans.XANK->at(k).type == 4)
							{
								Control *rotControl = node->GetTMController()->GetRotationController();
								if (rotControl)
								{
									SetControllerKeys(
										rotControl,
										&xans.XANK->at(k),
										KEY_ROT,
										xans.XANK->size(), k);

								}

							}
							else
							{
								Control *posControl = node->GetTMController()->GetPositionController();
								if (posControl)
								{
									SetControllerKeys(
										posControl,
										&xans.XANK->at(k),
										KEY_POS,
										xans.XANK->size(), k);
								}
							}
						}
					}
				}
				ResumeAnimate();
			}
		}

	}
	return nameAnim;
}

INode* MDLImport::DrawPart(SPART* part, int LOD, int PartNo, std::wstring nameAnim, int nodeIndex, std::wstring LODStr)
{

	TriObject* object = NULL;
	Mesh* mesh = NULL;
	MeshNormalSpec* ns = NULL;

	std::vector<SVERT>* vert = NULL;
	std::vector<Point3>* tempVert = NULL;
	std::vector<Point3>* tempNVert = NULL;
	std::vector<Point3>* tempTVert = NULL;
	std::vector<Point3>* tempVertN = NULL;

	std::vector<SIND3>* inde = NULL;
	std::vector<int>* tempInd = NULL;
	std::vector<int>* tempNInd = NULL;
	std::vector<int>* tempTInd = NULL;

	AdjEdgeList* el = NULL;
	AdjFaceList* fl = NULL;
	FaceElementList* fe = NULL;

	Point3 tp = {0, 0, 0};
	Point3 tpn = {0, 0, 0};

	int CurrVerb = 0;
	int fi = 0;

	SParts lNodeParts;
	std::wstring NameVis = L"";
	std::wstring XMLVis = L"";
	
	NodeIndex++;
	
	object = CreateNewTriObject();
	if (!object)
		return FALSE;

	
	mesh = &object->GetMesh();
	CurrVerb = part->vertex_buffer_index;
	vert = riff->VERB->at(CurrVerb).VERT;
	inde = riff->IND3;

	tempVert = new std::vector<Point3>();
	tempVertN = new std::vector<Point3>();
  //
	tempInd = new std::vector<int>(part->index_count);
	for (int ii = 0; ii < part->vertex_count; ii++)
	{
		bool find = false;
		int iii = 0;

		tp = {
			vert->at(ii + part->vertex_offset).position_x,
			vert->at(ii + part->vertex_offset).position_y,
			-vert->at(ii + part->vertex_offset).position_z
		};
		tpn = {
			vert->at(ii + part->vertex_offset).normal_x,
			vert->at(ii + part->vertex_offset).normal_y,
			-vert->at(ii + part->vertex_offset).normal_z
		};
		
		for (iii = 0; iii < tempVert->size(); iii++)
		{
			if (tp == tempVert->at(iii))
			{
				if (tpn == tempVertN->at(iii))
				{
					find = true;
					break;
				}
			}
		}
		if (!find)
		{
			tempVert->push_back(tp);
			tempVertN->push_back(tpn);
			tempInd->at(ii) = fi;
			fi++;
		}
		else
		{
			tempInd->at(ii) = iii;
		}
	}

	tempTVert = new std::vector<Point3>();
	tempTInd = new std::vector<int>(part->vertex_count);
	fi = 0;
	for (int ii = 0; ii < part->vertex_count; ii++)
	{
		bool find = false;
		int iii = 0;

		tp = {
			vert->at(ii + part->vertex_offset).texture_mapping_x,
			vert->at(ii + part->vertex_offset).texture_mapping_y,
			float(0.0)
		};
		
		for (iii = 0; iii < tempTVert->size(); iii++)
		{
			if (tp == tempTVert->at(iii))
			{
				find = true;
				break;
			}
		}
		if (!find)
		{
			tempTVert->push_back(tp);
			tempTInd->at(ii) = fi;
			fi++;
		}
		else
		{
			tempTInd->at(ii) = iii;
		}
	}

	tempNVert = new std::vector<Point3>();
	tempNInd = new std::vector<int>(part->vertex_count);
	fi = 0;
	for (int ii = 0; ii < part->vertex_count; ii++)
	{
		bool find = false;
		int iii = 0;

		tp = {
			vert->at(ii + part->vertex_offset).normal_x,
			vert->at(ii + part->vertex_offset).normal_y,
			-vert->at(ii + part->vertex_offset).normal_z
		};
		
		for (iii = 0; iii < tempNVert->size(); iii++)
		{
			if (tp == tempNVert->at(iii))
			{
				find = true;
				break;
			}
		}
		if (!find)
		{
			tempNVert->push_back(tp);
			tempNInd->at(ii) = fi;
			fi++;
		}
		else
		{
			tempNInd->at(ii) = iii;
		}
	}
	
	mesh->SpecifyNormals();
	ns = mesh->GetSpecifiedNormals();
	ns->ClearNormals();
	ns->SetNumNormals(tempNVert->size());
	ns->CheckNormals();

	mesh->setNumVerts(tempVert->size());
	
	mesh->setNumTVerts(tempTVert->size());

	for (int ii = 0; ii < tempVert->size(); ii++)
	{
		mesh->setVert(ii, tempVert->at(ii));
	}
	
	for (int ii = 0; ii < tempTVert->size(); ii++)
	{
		mesh->setTVert(ii, tempTVert->at(ii));
	}
	for (int ii = 0; ii < tempNVert->size(); ii++)
	{
		ns->Normal(ii) = tempNVert->at(ii);
		ns->SetNormalExplicit(ii, true);
	}
	mesh->setNumFaces(part->index_count / 3);
	
	mesh->setNumTVFaces(part->index_count / 3);
	ns->SetNumFaces(part->index_count / 3);
	for (int ii = 0; ii < (part->index_count / 3); ii++)
	{
    int indd3 = inde->at(ii + part->index_offset / 3).ind3;
    int indd2 = inde->at(ii + part->index_offset / 3).ind2;
    int indd1 = inde->at(ii + part->index_offset / 3).ind1;
		mesh->faces[ii].setVerts(
			tempInd->at(indd3),
			tempInd->at(indd2),
			tempInd->at(indd1));
		mesh->faces[ii].setEdgeVisFlags(1, 1, 1);

		
		mesh->tvFace[ii].setTVerts(
			tempTInd->at((inde->at(ii + part->index_offset / 3).ind3)),
			tempTInd->at((inde->at(ii + part->index_offset / 3).ind2)),
			tempTInd->at((inde->at(ii + part->index_offset / 3).ind1)));

		//RVertex* rv = mesh->getRVertPtr(tempTInd->at((inde->at(ii + part->index_offset / 3).ind1)));
		//rv->rn.addNormal(tempNVert->at(tempNInd->at((inde->at(ii + part->index_offset / 3).ind1))));
		//rv = mesh->getRVertPtr(tempTInd->at((inde->at(ii + part->index_offset / 3).ind2)));
		//rv->rn.addNormal(tempNVert->at(tempNInd->at((inde->at(ii + part->index_offset / 3).ind2))));
		//rv = mesh->getRVertPtr(tempTInd->at((inde->at(ii + part->index_offset / 3).ind3)));
		//rv->rn.addNormal(tempNVert->at(tempNInd->at((inde->at(ii + part->index_offset / 3).ind3))));

		
		mesh->setNormal(tempTInd->at((inde->at(ii + part->index_offset / 3).ind1)), tempNVert->at(tempNInd->at((inde->at(ii + part->index_offset / 3).ind1))));
		mesh->setNormal(tempTInd->at((inde->at(ii + part->index_offset / 3).ind2)), tempNVert->at(tempNInd->at((inde->at(ii + part->index_offset / 3).ind2))));
		mesh->setNormal(tempTInd->at((inde->at(ii + part->index_offset / 3).ind3)), tempNVert->at(tempNInd->at((inde->at(ii + part->index_offset / 3).ind3))));

		MeshNormalFace &nf = ns->Face(ii);
		nf.SpecifyAll();
		nf.SetNormalID(0, tempNInd->at((inde->at(ii + part->index_offset / 3).ind3)));
		nf.SetNormalID(1, tempNInd->at((inde->at(ii + part->index_offset / 3).ind2)));
		nf.SetNormalID(2, tempNInd->at((inde->at(ii + part->index_offset / 3).ind1)));

	}

	el = new AdjEdgeList(*mesh);
	fl = new AdjFaceList(*mesh, *el);
	fe = new FaceElementList(*mesh, *fl);
	for (int i = 0; i < fe->elem.Count(); i++)
	{
		mesh->faces[i].setSmGroup(fe->elem[i]);
	}
	for (int ii = 0; ii < tempVert->size(); ii++)
	{
		mesh->setNormal(ii, tempVertN->at(ii));
	}

	
	//node = tr;
	//delete tr;
	//tr = NULL;
	//delete object;
	//object = NULL;
	INode* node = riff->gi->CreateObjectNode(object);

	if (!node) {
		//object.release();
		return FALSE;
	}
	node->SetMtl(Mtls->at(part->material_index));
	//Mtl* editMat = node->GetMtl();

	lNodeParts.LOD = LOD;
	lNodeParts.node = node;
	lNodeParts.Part = PartNo;
	lNodeParts.Inds = tempInd;
	NodeParts->push_back(lNodeParts);

	
	mesh->buildNormals();
	//mesh->buildBoundingBox();
	//mesh->InvalidateEdgeList();
	mesh->InvalidateGeomCache();
	mesh->InvalidateTopologyCache();


	
	node->SetWireColor(RGB(255, 255, 255));
	//nameAnim = SetAnim(riff, node, nodeIndex);
	if (nameAnim == L"")
	{
		if (riff->SGVL->at(nodeIndex).vis_index >= 0)
		{
			NameVis = std::wstring(riff->VISI->at(riff->SGVL->at(nodeIndex).vis_index).name.begin(), riff->VISI->at(riff->SGVL->at(nodeIndex).vis_index).name.end());
			XMLVis = StartUD + L"<Visibility name=\"" + NameVis + L"\"></Visibility>" + EndUD;
			node->SetUserPropBuffer(XMLVis.c_str());
			node->SetName(std::wstring(NameVis + L"_" + std::to_wstring(NodeIndex) + L"_" + std::to_wstring(nodeIndex) + L"_P" + LODStr).c_str());
		}
		else
		{
			node->SetName(std::wstring(L"Node_" + std::to_wstring(NodeIndex) + L"_" + std::to_wstring(nodeIndex) + L"_P" + LODStr).c_str());
		}
	}
	else
	{
		node->SetName(std::wstring(nameAnim + L"_" + std::to_wstring(NodeIndex) + L"_" + std::to_wstring(nodeIndex) + L"_P" + LODStr).c_str());
	}
	return node;
}

Matrix3 MDLImport::AddTM(STRAN tran, Matrix3 tm)
{
	Matrix3 tm1
	({
		Point3(tran.m00, tran.m01, -tran.m02),
		Point3(tran.m10, tran.m11, -tran.m12),
		Point3(-tran.m20, -tran.m21, tran.m22),
		Point3(tran.m30, tran.m31, -tran.m32)
	});
	return tm * tm1;

}

Matrix3 MDLImport::CalcTransform(int StartIndex, int useTMO = 0)
{

	SAMAP amap = riff->AMAP->at(riff->SCEN->at(StartIndex).amap_offset / 8);
	STRAN tran = riff->TRAN->at(amap.matrix);
	Matrix3 tm;
	tm.IdentityMatrix();
	if (useTMO == 1)
	{
		tm.RotateX(deg2rad(-90.0));
	}
	else if (useTMO == 2)
	{
		tm.RotateX(deg2rad(90.0));
	}

	tm = AddTM(tran, tm);
	int parent = riff->SCEN->at(StartIndex).parent;
	while (parent != -1)
	{
		SAMAP amap = riff->AMAP->at(riff->SCEN->at(parent).amap_offset / 8);
		STRAN tran = riff->TRAN->at(amap.matrix);
		tm = AddTM(tran, tm);
		parent = riff->SCEN->at(parent).parent;
	};

	tm = tm * tmO;

	return tm;
}

std::vector<float> MDLImport::GetArrFromString(LPWSTR str)
{
	std::vector<float> a;
	for (LPWSTR p = _wcstok(str, L","); p; p = _wcstok(NULL, L",")) {
		a.push_back(_wtof(p));
	}
	return a;
}

INode* MDLImport::CreateBone(int CurrNode, int ParentNodeIndex, INode* ParentBone)
{
	INode* node;
	Object*  object;
	//Object* object;
	object = (Object*)riff->gi->CreateInstance(GEOMOBJECT_CLASS_ID, BONE_OBJ_CLASSID);
	node = riff->gi->CreateObjectNode(object);
	node->SetBoneNodeOnOff(TRUE, 0);
	node->ShowBone(2);
	node->SetRenderable(FALSE);
	//object->GetParamBlock()->SetValue()
	float LengthParent = 0.5;
	if (riff->SGBR->at(ParentNodeIndex).bone_index >= 0)
	{
		if ((riff->SGBR->at(ParentNodeIndex).bone_index == 0) ||
			(riff->SGBR->at(ParentNodeIndex).bone_index == 1))
		{
			int m = 0;
		}

		SAMAP amap = riff->AMAP->at(riff->SCEN->at(CurrNode).amap_offset / 8);
		STRAN tran = riff->TRAN->at(amap.matrix);
		Matrix3 tmt;
		tmt.IdentityMatrix();
		tmt = AddTM(tran, tmt);
		Point3 VecLength = tmt.GetTrans();
		LengthParent = VecLength.FLength();
		Interval* interval = new Interval(0, 0);
		float* LengthC = new float(0.0);
		MaxSDK::AssetManagement::AssetUser* au = new MaxSDK::AssetManagement::AssetUser();
		ParentBone->GetObjectRef()->GetParamBlock(boneobj_params)->GetValue(boneobj_length, TimeValue(0), *LengthC, *interval);
		if (*LengthC < LengthParent)
		{
			ParentBone->GetObjectRef()->GetParamBlock(boneobj_params)->SetValue(boneobj_width, 0, LengthParent / 2);
			ParentBone->GetObjectRef()->GetParamBlock(boneobj_params)->SetValue(boneobj_height, 0, LengthParent / 2);
			ParentBone->GetObjectRef()->GetParamBlock(boneobj_params)->SetValue(boneobj_length, 0, LengthParent);
		}
		delete LengthC;
	}
	object->GetParamBlock(boneobj_params)->SetValue(boneobj_width, 0, LengthParent / 2);
	object->GetParamBlock(boneobj_params)->SetValue(boneobj_height, 0, LengthParent / 2);
	object->GetParamBlock(boneobj_params)->SetValue(boneobj_length, 0, LengthParent);

	while (Bones->size() <= riff->SGBR->at(CurrNode).bone_index)
	{
		Bones->push_back(NULL);
	}
	Bones->at(riff->SGBR->at(CurrNode).bone_index) = node;
	if (!node) {
		delete object;
		return FALSE;
	}
	return node;

}
int MDLImport::CheckParts(int CurrNode)
{
	int count = 0;
	for (int j = 0; j < riff->LODT->size(); j++)
	{
		for (int i = 0; i < riff->LODT->at(j).PART->size(); i++)
		{
			SPART *part = &riff->LODT->at(j).PART->at(i);

			if (part->type == 1)
			{
				if (part->scenegraph_reference == CurrNode)
				{

					count++;
				}
			}
		}
	}
	return count;
}
bool MDLImport::FindGraph(int CurrNode, /*INode* parentNode,*/ int findGraph, std::vector<int>* grafs)
{
	/*if (Hierarchy == NULL)
	{
	Hierarchy = new std::vector<SHierarchy>();
	}
	*/
	int cn = CurrNode;
	//INode* node = NULL;
	bool fg = false;
	if (cn == findGraph)
	{
		grafs->push_back(cn);
		return true;
	}

	while (cn >= 0)
	{

		/*Object* object;
		object = new  DummyObject();
		node = riff->gi->CreateObjectNode(object);
		node->SetName(std::wstring(L"SG_" + std::to_wstring(CurrNode)).c_str());
		parentNode->AttachChild(node);*/

		fg = FindGraph(riff->SCEN->at(cn).child_node_index,/* node*/findGraph, grafs);
		if (fg)
		{
			grafs->push_back(cn);
			return true;
		}
		cn = riff->SCEN->at(cn).peer_node_index;
		if (cn == findGraph)
		{
			grafs->push_back(cn);
			return true;
		}
	}

	return false;

}
BOOL MDLImport::CreateNode(int CurrNode, int ParentNodeIndex, INode * ParentNode, INode * ParentBone, INode* ParentPart, int LOD, std::wstring nameAnim = L"")
{

	INode* LastPartNode;

	std::vector<INode*>* Nodes = new std::vector<INode*>();
	enum
	{
		BONE_WIDTH,
		BONE_HEIGHT,
		BONE_TAPER,
		BONE_LENGTH,
	};


	while (CurrNode >= 0)
	{
		std::vector<int>* grafs = new std::vector<int>();

		Nodes->clear();
		OneNode = NULL;
		LastPartNode = NULL;
		int countParts = 0;

		std::wstring LODStr = L"";
	
		LODStr = std::wstring(L"_" + std::to_wstring(riff->LODT->at(LOD).LOD));

		for (int i = 0; i < riff->LODT->at(LOD).PART->size(); i++)
		{
			SPART *part = &riff->LODT->at(LOD).PART->at(i);

			if (part->type == 1)
			{
				if (part->scenegraph_reference == CurrNode)
				{
					countParts++;

					INode* NodePart = DrawPart(part, LOD, i, nameAnim, CurrNode, LODStr);
					Nodes->push_back(NodePart);

					if (riff->SGVL->at(CurrNode).vis_index >= 0)
					{
						std::wstring NameVis = std::wstring(riff->VISI->at(riff->SGVL->at(CurrNode).vis_index).name.begin(), riff->VISI->at(riff->SGVL->at(CurrNode).vis_index).name.end());
						std::wstring XMLVis = StartUD + L"<Visibility name=\"" + NameVis + L"\"></Visibility>" + EndUD;
						NodePart->SetUserPropBuffer(XMLVis.c_str());
						if (nameAnim == L"")
						{
							nameAnim = NameVis;
						}
						NodePart->SetName(std::wstring(NameVis + L"_" + std::to_wstring(NodeIndex) + L"_" + std::to_wstring(CurrNode) + L"_P" + LODStr).c_str());
					}
					if (ParentNode != NULL)
					{
						ParentNode->AttachChild(NodePart);
					}
					OneNode = NodePart;
					LastPartNode = NodePart;
				}
			}
		}

		int attoi = -1;
		for (int ap = 0; ap < riff->REFP->size(); ap++)
		{

			if (riff->REFP->at(ap).scenegraph_reference == CurrNode)
			{
				attoi = 0;
				for (attoi = 0; attoi < riff->ATTO->size(); attoi++)
				{
					if (!std::strcmp(riff->ATTO->at(attoi).attachPoint.c_str(), riff->REFP->at(ap).name.c_str()))
					{
						break;
					}
				}
				if ((riff->ATTO->size() > 0) && (attoi != riff->ATTO->size()))
				{
					countParts++;
					NodeIndex++;
					INode *node;
					std::wstring NameFX = std::wstring(riff->ATTO->at(attoi).fxName.begin(), riff->ATTO->at(attoi).fxName.end());
					std::wstring EffectFile = EffectPath + NameFX + L".fx";
					//std::string EffectFileA = EffectPathA + riff->ATTO->at(attoi).fxName + ".fx";
					if (GetPrivateProfileInt(L"Particle.0", L"Type", 0, EffectFile.c_str()) == 28)
					{
						LPWSTR scaleS = new wchar_t[64];
						GetPrivateProfileString(L"Particle.0", L"X Scale", L"1.0 ,1.0", scaleS, 64, EffectFile.c_str());
						std::vector<float> scalesX = GetArrFromString(scaleS);
						GetPrivateProfileString(L"ParticleAttributes.0", L"Color End", L"255, 255, 255, 80", scaleS, 64, EffectFile.c_str());
						std::vector<float> ColorI = GetArrFromString(scaleS);
						GetPrivateProfileString(L"ParticleAttributes.0", L"Inner Cone Angle", L"1.0", scaleS, 64, EffectFile.c_str());
						std::vector<float> ICA = GetArrFromString(scaleS);
						GetPrivateProfileString(L"ParticleAttributes.0", L"Outer Cone Angle", L"45.0", scaleS, 64, EffectFile.c_str());
						std::vector<float> OCA = GetArrFromString(scaleS);

						GenLight *gl = (GenLight *)CreateInstance(LIGHT_CLASS_ID, Class_ID(SPOT_LIGHT_CLASS_ID, 0));
						gl->SetHotspot(0, ICA[0]);
						gl->SetFallsize(0, OCA[0]);
						gl->SetRGBColor(0, Point3(ColorI[0] / 255, ColorI[1] / 255, ColorI[2] / 255));
						gl->SetIntensity(0, ColorI[3] * scalesX[0] / 1000.0);
						gl->SetConeDisplay(TRUE);
						gl->SetShadow(FALSE);
						gl->SetUseLight(1);

						INode *nodegl = riff->gi->CreateObjectNode(gl);

						nodegl->SetWireColor(RGB(ColorI[0], ColorI[1], ColorI[2]));

						GenSphere *gs = (GenSphere *)CreateInstance(GEOMOBJECT_CLASS_ID, Class_ID(SPHERE_CLASS_ID, 0));
						gs->SetParams(0.0001, 4, TRUE, FALSE, 0.0, FALSE, FALSE);
						node = riff->gi->CreateObjectNode(gs);
						node->SetRenderable(FALSE);

						Matrix3 tm;
						tm.IdentityMatrix();
						tm.RotateX(deg2rad(90.0));
						nodegl->SetNodeTM(0, tm);
						node->AttachChild(nodegl);
					}
					else
					{
						GenSphere *gs = (GenSphere *)CreateInstance(GEOMOBJECT_CLASS_ID, Class_ID(SPHERE_CLASS_ID, 0));
						gs->SetParams(0.5, 4, TRUE, FALSE, 0.0, FALSE, FALSE);
						node = riff->gi->CreateObjectNode(gs);
						node->SetRenderable(FALSE);

					}

					if (ParentNode != NULL)
					{
						ParentNode->AttachChild(node);
					}
					if (ParentPart != NULL)
					{
						ParentPart->AttachChild(node);
					}
					Nodes->push_back(node);


					//node->SetNodeTM(0, CalcTransform(riff, CurrNode, 0));

					node->SetWireColor(RGB(246, 7, 255));
					OneNode = node;
					std::wstring NameAtach = std::wstring(riff->ATTO->at(attoi).attachPoint.begin(), riff->ATTO->at(attoi).attachPoint.end()) + LODStr;
					std::wstring ParamAttach = std::wstring(riff->ATTO->at(attoi).params.begin(), riff->ATTO->at(attoi).params.end());
					//node->SetName(std::wstring(NameAtach + L"_" + std::to_wstring(NodeIndex) +L"_"+ std::to_wstring(ParentNodeIndex) +L"_A").c_str());
					node->SetName(NameAtach.c_str());
					if (attoi != riff->ATTO->size())
					{
						std::wstring XMLAttach = StartUD + L"<Attachpoint name = \"" + NameAtach + L"\"> <AttachedObject> <Effect effectName=\"" + NameFX + L"\" effectParams=\"" + ParamAttach + L"\"/> </AttachedObject> </Attachpoint>" + EndUD;
						node->SetUserPropBuffer(XMLAttach.c_str());
					}
				}
			}
		}

		bool FlagPart = true;
		Matrix3 tmP;
		INode *node;
		BoneNode = NULL;
		bool FindPart = false;
		bool FindRefp = false;
		bool FindBone = false;

		for (int pn = 0; pn < riff->LODT->at(LOD).PART->size(); pn++)
		{
			FindPart = FindGraph(CurrNode, riff->LODT->at(LOD).PART->at(pn).scenegraph_reference, grafs);
		}
		for (int bn = 0; bn < riff->SGBR->size(); bn++)
		{
			if (riff->SGBR->at(bn).bone_index != -1)
			{
				FindBone = FindGraph(CurrNode, bn, grafs);
			}
		}
		for (int en = 0; en < riff->REFP->size(); en++)
		{
			FindRefp = FindGraph(CurrNode, riff->REFP->at(en).scenegraph_reference, grafs);
		}
		if (std::find(grafs->begin(), grafs->end(), CurrNode) != grafs->end())
		{

			if (riff->SGBR->at(CurrNode).bone_index >= 0)
			{
				NodeIndex++;
				node = CreateBone(CurrNode, ParentNodeIndex, ParentBone);
				nameAnim = SetAnim(node, CurrNode);
				node->SetNodeTM(0, CalcTransform(CurrNode));
				if (ParentBone != NULL)
				{
					ParentBone->AttachChild(node);
				}
				else if (ParentNode != NULL)
				{
					ParentNode->AttachChild(node);
				}
				for (int i = 0; i < Nodes->size(); i++)
				{
					node->AttachChild(Nodes->at(i));
					MSTR str;
					Nodes->at(i)->GetUserPropBuffer(str);
					std::wstring sstr = std::wstring(str);
					int find = sstr.find(L"Attachpoint");
					if (find > 0)
					{
						Nodes->at(i)->SetNodeTM(0, CalcTransform(CurrNode, 1));
					}
					else
					{
						Nodes->at(i)->SetNodeTM(0, CalcTransform(CurrNode, 0));
					}
				}
				node->SetWireColor(RGB(255, 255, 255));
				if (riff->SGBN->size() > 0)
				{
					if (riff->SGBN->at(CurrNode).bone_name == "")
					{
						node->SetName(std::wstring(L"Bone_NN_" + std::to_wstring(NodeIndex) + L"_" + std::to_wstring(CurrNode)).c_str());
					}
					else
					{
						std::wstring BoneName = std::wstring(riff->SGBN->at(CurrNode).bone_name.begin(), riff->SGBN->at(CurrNode).bone_name.end());
						node->SetName(std::wstring(BoneName).c_str());// +L"_" + std::to_wstring(CurrNode)).c_str());
					}
				}
				else
				{
					node->SetName(std::wstring(L"Bone_NN_" + std::to_wstring(NodeIndex) + L"_" + std::to_wstring(CurrNode)).c_str());
				}
				OneNode = node;
				BoneNode = node;
			}

			else if (countParts != 1)
			{

				NodeIndex++;
				node = CreateDummy(L"");

				if (ParentNode != NULL)
				{
					ParentNode->AttachChild(node);
				}
				nameAnim = SetAnim(node, CurrNode);
				node->SetNodeTM(0, CalcTransform(CurrNode));
				for (int i = 0; i < Nodes->size(); i++)
				{

					//nameAnim = SetAnim(riff, Nodes->at(i), CurrNode);
					node->AttachChild(Nodes->at(i));
					MSTR str;
					Nodes->at(i)->GetUserPropBuffer(str);
					std::wstring sstr = std::wstring(str);
					int find = sstr.find(L"Attachpoint");
					if (find > 0)
					{
						Nodes->at(i)->SetNodeTM(0, CalcTransform(CurrNode, 1));
					}
					else
					{
						Nodes->at(i)->SetNodeTM(0, CalcTransform(CurrNode, 0));
					}
				}

				OneNode = node;
				if (riff->SGVL->at(CurrNode).vis_index >= 0)
				{
					std::wstring NameVis = std::wstring(riff->VISI->at(riff->SGVL->at(CurrNode).vis_index).name.begin(), riff->VISI->at(riff->SGVL->at(CurrNode).vis_index).name.end());
					std::wstring XMLVis = StartUD + L"<Visibility name=\"" + NameVis + L"\"></Visibility>" + EndUD;
					OneNode->SetUserPropBuffer(XMLVis.c_str());
					if (nameAnim == L"")
					{
						nameAnim = NameVis;
					}
					OneNode->SetName(std::wstring(NameVis + L"_" + std::to_wstring(NodeIndex) + L"_" + std::to_wstring(CurrNode) + L"_D" + LODStr).c_str());
				}
				if (nameAnim == L"")
				{
					OneNode->SetName(std::wstring(L"Node_" + std::to_wstring(NodeIndex) + L"_" + std::to_wstring(CurrNode) + L"_D" + LODStr).c_str());
				}
				else
				{
					OneNode->SetName(std::wstring(nameAnim + L"_" + std::to_wstring(NodeIndex) + L"_" + std::to_wstring(CurrNode) + L"_D" + LODStr).c_str());
				}
				if (riff->SGBR->at(CurrNode).bone_index >= 0)
				{

				}


			}
			else
			{

				nameAnim = SetAnim(OneNode, CurrNode);
				MSTR str;
				OneNode->GetUserPropBuffer(str);
				std::wstring sstr = std::wstring(str);
				int find = sstr.find(L"Attachpoint");
				if (find > 0)
				{
					OneNode->SetNodeTM(0, CalcTransform(CurrNode, 1));
				}
				else
				{
					OneNode->SetNodeTM(0, CalcTransform(CurrNode, 0));
				}


			}

		}


		if (NodeIndex == 0)
		{
			rootNode = OneNode;
		}
		CreateNode(riff->SCEN->at(CurrNode).child_node_index, CurrNode, OneNode, BoneNode, LastPartNode, LOD, nameAnim);
		CurrNode = riff->SCEN->at(CurrNode).peer_node_index;
		grafs->clear();
		delete(grafs);
		grafs = NULL;
	}

	return true;

}

enum NodeType
{
	DUMMY,
	BONE,
	ATTACH,
	PART

};
struct SNode
{
	NodeType Type;
	std::vector<int>* parts;
};
struct SHierarchy
{
	std::vector<SNode>* Nodes;
};
std::vector<SHierarchy>* Hierarchy;



BOOL MDLImport::SetSkin()
{
	for (int i = 0; i < NodeParts->size(); i++)
	{
		int CurrVerb = riff->LODT->at(NodeParts->at(i).LOD).PART->at(NodeParts->at(i).Part).vertex_buffer_index;
		if (riff->VERB->at(CurrVerb).SKIN != NULL)
		{
			if (i == 7)
			{
				int m = 0;
			}
			//ISkinImportData *skin = (ISkinImportData*)riff->gi->CreateInstance(OSM_CLASS_ID, Class_ID(9815843, 87654));

			Modifier* skin = (Modifier*)riff->gi->CreateInstance(SClass_ID(OSM_CLASS_ID), SKIN_CLASSID);
			ISkinImportData* SkinInterface = (ISkinImportData*)skin->GetInterface(I_SKINIMPORTDATA);



			//Modifier* mod = (Modifier*)skin;
			GetCOREInterface12()->AddModifier(*NodeParts->at(i).node, *skin);
			//riff->i->AddModifier(*NodeParts->at(i).node, *skin);
			for (int bi = 0; bi < riff->VERB->at(CurrVerb).BMAP->size(); bi++)
			{
				SkinInterface->AddBoneEx(Bones->at(riff->VERB->at(CurrVerb).BMAP->at(bi).index), true);
			}
			int StartVert = riff->LODT->at(NodeParts->at(i).LOD).PART->at(NodeParts->at(i).Part).vertex_offset;
			int CountVert = riff->LODT->at(NodeParts->at(i).LOD).PART->at(NodeParts->at(i).Part).vertex_count;
			GetCOREInterface()->ForceCompleteRedraw();
			NodeParts->at(i).node->EvalWorldState(GetCOREInterface()->GetTime());
			for (int si = StartVert; si < (CountVert + StartVert); si++)
			{
				//std::vector<INode*>* lbones = new std::vector<INode*>();
				//std::vector<float>* lweights = new std::vector<float>();
				Tab<INode*> lbones;
				Tab<float> lweights;
				lbones.SetCount(0);
				lweights.SetCount(0);
				for (int sii = 0; sii < 4; sii++)
				{
					if (riff->VERB->at(CurrVerb).SKIN->at(si).weight[sii] != 0)
					{
						float w = riff->VERB->at(CurrVerb).SKIN->at(si).weight[sii] / 255.0;
						lbones.Append(1, &Bones->at(riff->VERB->at(CurrVerb).BMAP->at(riff->VERB->at(CurrVerb).SKIN->at(si).bn[sii]).index));
						lweights.Append(1, &w);
					}
				}
				if ((si - StartVert) == 71)
				{
					int m = 0;
				}
				bool hr = SkinInterface->AddWeights(NodeParts->at(i).node, NodeParts->at(i).Inds->at(si - StartVert), lbones, lweights);
				if (hr)
				{
					int m = 0;
				}

			}
		}
	}
	return TRUE;
}

BOOL MDLImport::objFileRead(const TCHAR *filename, Mesh *mesh)
{
	float size, h;

	h = 0.5 * 5;

	// Число вершин и граней в меш
	mesh->setNumVerts(8);
	mesh->setNumFaces(12);
	// Координаты вершин
	mesh->setVert(0, Point3(-h, -h, -h));
	mesh->setVert(1, Point3(h, -h, -h));
	mesh->setVert(2, Point3(-h, h, -h));
	mesh->setVert(3, Point3(h, h, -h));
	mesh->setVert(4, Point3(-h, -h, h));
	mesh->setVert(5, Point3(h, -h, h));
	mesh->setVert(6, Point3(-h, h, h));
	mesh->setVert(7, Point3(h, h, h));
	// Состав граней
	mesh->faces[0].setVerts(0, 2, 3);
	mesh->faces[1].setVerts(3, 1, 0);
	mesh->faces[2].setVerts(4, 5, 7);
	mesh->faces[3].setVerts(7, 6, 4);
	mesh->faces[4].setVerts(0, 1, 5);
	mesh->faces[5].setVerts(5, 4, 0);
	mesh->faces[6].setVerts(1, 3, 7);
	mesh->faces[7].setVerts(7, 5, 1);
	mesh->faces[8].setVerts(3, 2, 6);
	mesh->faces[9].setVerts(6, 7, 3);
	mesh->faces[10].setVerts(2, 0, 4);
	mesh->faces[11].setVerts(4, 6, 2);
	// Группы сглаживания
	mesh->faces[0].setSmGroup(2);
	mesh->faces[1].setSmGroup(2);
	mesh->faces[2].setSmGroup(4);
	mesh->faces[3].setSmGroup(4);
	mesh->faces[4].setSmGroup(8);
	mesh->faces[5].setSmGroup(8);
	mesh->faces[6].setSmGroup(16);
	mesh->faces[7].setSmGroup(16);
	mesh->faces[8].setSmGroup(32);
	mesh->faces[9].setSmGroup(32);
	mesh->faces[10].setSmGroup(64);
	mesh->faces[11].setSmGroup(64);
	// Устанавливаем видимость внешних ребер граней (диагональные ребра не видны)
	for (int k = 0; k < 12; k++) {
		mesh->faces[k].setEdgeVisFlags(1, 1, 0);
		mesh->faces[k].setMatID(1);
	}
	// Назначаем UVW-координаты
	Matrix3 tm(1);
	tm.Scale(Point3(h, h, h));
	tm = Inverse(tm);
	mesh->ApplyUVWMap(MAP_BOX, 1.0f, 1.0f, 1.0f, 0, 0, 0, 0, tm);
	mesh->InvalidateTopologyCache();

	return TRUE;
}
bool MDLImport::FindAndCopyTextures()
{
	std::wstring wp = *filename;
	std::wstring base_dir1 = wp.substr(0, wp.find_last_of(L"/\\") + 1);
	std::wstring base = wp.substr(0, wp.find_last_of(L"/\\"));
	base = base.substr(0, base.find_last_of(L"/\\") + 1);
	std::wstring base_dir2 = base.substr(0, wp.find_last_of(L"/\\") + 1) + L"texture\\";

	std::wstring TextureCFG = base_dir2 + L"texture.cfg";
	
	std::wstring texName;
	std::wstring texNameBMP;
	std::wstring texNameDDS;
	std::wstring texNameTGA;
	std::wstring texNameOrig;

	//LPWSTR TPath = new wchar_t(255);
	LPWSTR TPath = L"";

	std::wstring base_out = wp.substr(0, wp.find_last_of(L"/\\") + 1) + L"Textures_" + ModelName + L"\\";
	CreateDirectory(base_out.c_str(), NULL);
	for (int i = 0; i < riff->TEXT->size(); i++)
	{
		texName = riff->TEXT->at(i).substr(0, riff->TEXT->at(i).find_last_of(L"."));
		texNameBMP = texName + L".bmp";
		texNameDDS = texName + L".dds";
		texNameTGA = texName + L".tga";
		texNameOrig = riff->TEXT->at(i);

		int j = 0;
		
		while (true)
		{

			//GetPrivateProfileString(L"fltsim", (L"fallback." + std::to_wstring(j)).c_str(), L"", TPath, 255, TextureCFG.c_str());
			if ((std::wstring(TPath) == L"") && (j > 0))
			{
				break;
			}
			WIN32_FIND_DATAW wfd;
			//std::wstring texName = riff->TEXT->at(i).substr(0, riff->TEXT->at(i).find_last_of(L"."));
			std::wstring teststr = base_dir2 + TPath + L"\\" + texNameOrig;
			bool find = false;
			HANDLE hFindO = FindFirstFile((base_dir2 + TPath + L"\\" + texNameOrig).c_str(), &wfd);
			if (INVALID_HANDLE_VALUE != hFindO)
			{
				find = true;
			}
			HANDLE hFindB = FindFirstFile((base_dir2 + TPath + L"\\" + texNameBMP).c_str(), &wfd);
			if (INVALID_HANDLE_VALUE != hFindB)
			{
				texNameOrig = texNameBMP;
				find = true;
			}
			HANDLE hFindD = FindFirstFile((base_dir2 + TPath + L"\\" + texNameDDS).c_str(), &wfd);
			if (INVALID_HANDLE_VALUE != hFindD)
			{
				texNameOrig = texNameDDS;
				find = true;
			}
			if (find)
			{
				/*std::wstring nvtool = L"\"C:\\Program Files (x86)\\DDS Converter 2\\nvdxt.exe\"";
				//std::wstring CMD = L"\"" + ImageTool + L"\" -nogui -nomip -vflip -dds -o \"" + base_out + texNameOrig + L"\" \"" + base_dir2 + TPath + L"\\" + texNameOrig + L"\"";
				std::wstring CMD = nvtool + L" -file \"" + base_dir2 + TPath + L"\\" + texNameOrig + L"\"" + L" -nomipmap -flip -output \"" + base_out + texNameOrig +L"";
				//ShellExecute(0, L"open", L"cmd.exe", CMD.c_str(), 0, SW_HIDE);
				STARTUPINFO si;
				PROCESS_INFORMATION pi;

				ZeroMemory(&si, sizeof(si));
				si.cb = sizeof(si);
				ZeroMemory(&pi, sizeof(pi));
				DWORD ExitCode = 0;
				bool Rlst = CreateProcess(NULL, LPWSTR(CMD.c_str()), NULL, NULL, false, NORMAL_PRIORITY_CLASS, NULL, NULL, &si, &pi);
				if (Rlst)
				{
					//Ждем завершения инициализации.
					WaitForInputIdle(pi.hProcess, INFINITE);
					//Ждем завершения процесса.
					WaitForSingleObject(pi.hProcess, INFINITE);
					//Получаем код завершения.
					GetExitCodeProcess(pi.hProcess, &ExitCode);
					//Закрываем дескриптор процесса.
					CloseHandle(pi.hThread);
					//Закрываем дескриптор потока.
					CloseHandle(pi.hProcess);
				}
				//Иначе
				else
				{
					//В случае ошибки - выводим на экран сообщение.
					int Error = GetLastError();
					//MessageBox(0, SysErrorMessage(Error), mtError, MB_OK, 0);
				}*/
				break;
			}
			j++;
		}
		Textures->push_back(base_out + texNameOrig);
	}
	return true;
}


bool MDLImport::CreateMtlLib()
{
	std::vector<BitmapTex*>* bt = new std::vector<BitmapTex*>();
	std::wstring wp = *filename;
	std::wstring base_dir = wp.substr(0, wp.find_last_of(L"/\\") + 1)+L"Textures_"+ ModelName+L"\\";
	FindAndCopyTextures();
	/*for (int i = 0; i < Textures->size(); i++)
	{
		std::wstring TexName = Textures->at(i);*/
	BitmapTex* bmt = NULL;
	for (int i = 0; i < Textures->size(); i++)
	{
		//std::wstring TexName = riff->TEXT->at(i);
		//std::wstring widestr = base_dir + std::wstring(TexName.begin(), TexName.end());
		//const wchar_t* widecstr = widestr.c_str();
		/*int e = 0;
		__try
		{*/
		bmt = NewDefaultBitmapTex();
		/*}
		__except(e)
		{
			MessageBox(0, (LPWSTR)e, L"Error", 0);
		}*/
		
		bmt->SetAlphaAsMono(true);
		StdUVGen *uv = bmt->GetUVGen();
//#if _DEBUG
		auto pos = Textures->at(i).rfind(L".");
		if (pos == std::wstring::npos)
			pos = -1;
		wstring ext = std::wstring(Textures->at(i).begin() + pos, Textures->at(i).end());
		std::transform(ext.begin(), ext.end(), ext.begin(), ::toupper);
		if (ext == L".DDS") {
			uv->SetVScl(-1.0, 0);
		}
//#else
		//uv->SetVScl(1.0, 0);
//#endif

		bmt->SetMapName(Textures->at(i).c_str());
		bt->push_back(bmt);
		//delete bmt;
		//bmt = NULL;
	}
	for (int i = 0; i < riff->MAT3->size(); i++)
	{
		SMAT3 lMat = riff->MAT3->at(i);
		P3DMaterial* mtl = NewP3DMat();
		if (riff->EMT1->size() > 0)
		{
			SEMT1 leMat = riff->EMT1->at(i);
			mtl->ConvertPrepar3DMaterials(&lMat, &leMat, bt);
		}
		else
		{
			mtl->ConvertPrepar3DMaterials(&lMat, NULL, bt);
		}

		if (riff->TEXT->size() > 0)
		{
			std::wstring TexName = Textures->at(lMat.diffuse_texture_index);
			//std::wstring widestr = std::wstring(TexName.begin(), TexName.end());
			//const wchar_t* widecstr = widestr.c_str();
			mtl->BaseMat->SetName(WStr(TexName.c_str()));
		}
		Mtls->push_back(mtl->BaseMat);
	}

	for (int i = 0; i < riff->PBRM->size(); i++)
	{
		SPBRM lMat = riff->PBRM->at(i);
		PBRMaterial* mtl = NewPBRMat();
		mtl->ConvertPBRMaterials(&lMat, bt);

		if (riff->TEXT->size() > 0)
		{
			if (lMat.albedoTextureIndex >= 0) {
				std::wstring TexName = Textures->at(lMat.albedoTextureIndex);
				//std::wstring widestr = std::wstring(TexName.begin(), TexName.end());
				//const wchar_t* widecstr = widestr.c_str();
				mtl->BaseMat->SetName(WStr(TexName.c_str()));
			}
			else {
				mtl->BaseMat->SetName(WStr(L"Mat #No_name"));
			}
		}
		Mtls->push_back(mtl->BaseMat);
	}
	return true;
}
INode* MDLImport::CreateDummy(std::wstring name)
{
	INode* node;
	Object* object;
	object = new  DummyObject();
	node = riff->gi->CreateObjectNode(object);
	node->SetName(name.c_str());
	if (!node) {
		delete object;
		return NULL;
	}
	return node;
}
