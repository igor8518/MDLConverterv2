#include "RIFF.h"




RIFF::RIFF(MDLImport* mdlImport, const TCHAR * filename, ImpInterface * i, Interface * gi, int Type)
{

	this->i = i;
	this->gi = gi;
	this->mdlImport = mdlImport;
	RIFFStream = new ReadStream(filename);
	TEXT = new std::vector<std::wstring>();
	MAT3 = new std::vector<SMAT3>();
	PBRM = new std::vector<SPBRM>();
	EMT1 = new std::vector<SEMT1>();
	IND3 = new std::vector<SIND3>();
	INDE = new std::vector<SINDE>();
	VERB = new std::vector<SVERB>();
	LODT = new std::vector<SLODT>();
	TRAN = new std::vector<STRAN>();
	SCEN = new std::vector<SSCEN>();
	SGAL = new std::vector<SSGAL>();
	SGBR = new std::vector<SSGBR>();
	SGBN = new std::vector<SSGBN>();
	SGVL = new std::vector<SSGVL>();
	VISI = new std::vector<SVISI>();
	AMAP = new std::vector<SAMAP>();
	XANI = new std::vector<SXANI>();
	REFP = new std::vector<SREFP>();
	ATTO = new std::vector<SATTO>();

	ReadSectionsHierarhy();
}
std::string RIFF::ShortCode(std::string Code)
{
	std::string sc = "";
	for (int i = 0; i < Code.length(); i++)
	{
		if ((Code[i] != ' ') &&
			(Code[i] != '\n') &&
			(Code[i] != '\t') &&
			(Code[i] != '\r'))
		{
			sc = sc + Code[i];
		}
	}
	return sc;
}

std::vector<std::string> RIFF::ConvertVisAnim(std::string str, int maxCount, int NamePar, int type)
{
	int ev = 0;
	std::vector<std::string> ReturnArr = std::vector<std::string>();
	std::string name = "";
	std::string sc = "";
	int fv = str.find('#', 0);
	if (fv == -1)
	{
		sc = ShortCode(str);
		int n1 = str.find(':');
		int n2 = str.find(',');
		name = str.substr(n1 + 1, n2 - n1 - 1);
		std::replace(name.begin(), name.end(), ' ', '_');
		std::replace(name.begin(), name.end(), ':', '_');
		ReturnArr.push_back(name);
		ReturnArr.push_back(str);
		int i;
		if (type == 0)
		{
			for (i = 0; i < mdlImport->ModelXML.PartInfoXML->size(); i++)
			{

				if (mdlImport->ModelXML.PartInfoXML->at(i).VisibleF)
				{
					if (mdlImport->ModelXML.PartInfoXML->at(i).Visible.Parameter.LagF == false)
					{
						if (std::strcmp(ShortCode(mdlImport->ModelXML.PartInfoXML->at(i).Visible.Parameter.Code).c_str(), sc.c_str()) == 0)
						{
							ReturnArr[0] = mdlImport->ModelXML.PartInfoXML->at(i).Name;
							break;
						}
					}

				}
			}
			if (i == mdlImport->ModelXML.PartInfoXML->size())
			{
				ReturnArr[0] = "custom_vis_" + ReturnArr[0];
				if (UniVISI < 10)
				{
					ReturnArr[0] = ReturnArr[0] + "_0" + std::to_string(UniVISI);
				}
				else
				{
					ReturnArr[0] = ReturnArr[0] + "_" + std::to_string(UniVISI);
				}
			}
		}
		if (type == 1)
		{
			for (i = 0; i < mdlImport->ModelXML.PartInfoXML->size(); i++)
			{
				if (mdlImport->ModelXML.PartInfoXML->at(i).AnimationF)
				{
					if (mdlImport->ModelXML.PartInfoXML->at(i).Animation.Parameter.LagF == false)
					{
						if (std::strcmp(ShortCode(mdlImport->ModelXML.PartInfoXML->at(i).Animation.Parameter.Code).c_str(), sc.c_str()) == 0)
						{
							ReturnArr[0] = mdlImport->ModelXML.PartInfoXML->at(i).Name;
							break;
						}
					}

				}
				
			}
			if (i == mdlImport->ModelXML.PartInfoXML->size())
			{
				ReturnArr[0] = "custom_anim_" + ReturnArr[0];
			}
		}
	}
	else
	{
		if (fv == 0)
		{
			int l1 = 0;
			int l2 = str.find('#', l1 + 1);
			std::string lag = str.substr(l1 + 1, l2 - l1 - 1);
			std::string code = str.substr(l2 + 1);
			sc = ShortCode(code);
			int n1 = str.find(':');
			int n2 = str.find(',');
			name = str.substr(n1 + 1, n2 - n1 - 1);
			std::replace(name.begin(), name.end(), ' ', '_');
			std::replace(name.begin(), name.end(), ':', '_');
			ReturnArr.push_back(name);
			ReturnArr.push_back(code);
			ReturnArr.push_back(lag);
			int i;
			if (type == 0)
			{
				for (i = 0; i < mdlImport->ModelXML.PartInfoXML->size(); i++)
				{

					if (mdlImport->ModelXML.PartInfoXML->at(i).VisibleF)
					{
						if (mdlImport->ModelXML.PartInfoXML->at(i).Visible.Parameter.LagF == true)
						{
							if (std::strcmp(ShortCode(mdlImport->ModelXML.PartInfoXML->at(i).Visible.Parameter.Code).c_str(), sc.c_str()) == 0)
							{
								if (mdlImport->ModelXML.PartInfoXML->at(i).Visible.Parameter.Lag == std::atof(lag.c_str()))
								{
									ReturnArr[0] = mdlImport->ModelXML.PartInfoXML->at(i).Name;
									break;
								}
							}
						}

					}
				}
				if (i == mdlImport->ModelXML.PartInfoXML->size())
				{
					ReturnArr[0] = "custom_vis_" + ReturnArr[0];
					if (UniVISI < 10)
					{
						ReturnArr[0] = ReturnArr[0] + "_0" + std::to_string(UniVISI);
					}
					else
					{
						ReturnArr[0] = ReturnArr[0] + "_" + std::to_string(UniVISI);
					}
				}
			}
			if (type == 1)
			{
				for (i = 0; i < mdlImport->ModelXML.PartInfoXML->size(); i++)
				{
					if (mdlImport->ModelXML.PartInfoXML->at(i).AnimationF)
					{
						if (mdlImport->ModelXML.PartInfoXML->at(i).Animation.Parameter.LagF == true)
						{
							if (std::strcmp(ShortCode(mdlImport->ModelXML.PartInfoXML->at(i).Animation.Parameter.Code).c_str(), sc.c_str()) == 0)
							{
								if (mdlImport->ModelXML.PartInfoXML->at(i).Animation.Parameter.Lag == std::atof(lag.c_str()))
								{
									ReturnArr[0] = mdlImport->ModelXML.PartInfoXML->at(i).Name;
									break;
								}
							}
						}

					}

				}
				if (i == mdlImport->ModelXML.PartInfoXML->size())
				{
					ReturnArr[0] = "custom_anim_" + ReturnArr[0];
				}
			}
		}
		else
		{
			std::string variable = str.substr(0, fv);
			std::string name = variable;
			std::replace(name.begin(), name.end(), ' ', '_');
			std::replace(name.begin(), name.end(), ':', '_');
			ReturnArr.push_back(name);
			ReturnArr.push_back(variable);
			int u1 = fv;
			int u2 = str.find('#', fv + 1);
			std::string unit = str.substr(u1+1, u2 - u1 - 1);
			ReturnArr.push_back(unit);
			int b1 = u2;
			int b2 = str.find('#', b1 + 1);
			std::string bias = "";
			std::string lag = "";
			if (b1 >= 0)
			{
				bias = str.substr(b1+1, b2 - b1 - 1);
				ReturnArr.push_back(bias);
				int l1 = b2;
				int l2 = str.find('#', l1 + 1);
				if (l1 >= 0)
				{
					lag = str.substr(l1+1, l2 - l1 - 1);
					ReturnArr.push_back(lag);
				}
			}
			int i;
			if (type == 0)
			{
				for (i = 0; i < mdlImport->ModelXML.PartInfoXML->size(); i++)
				{
					if (mdlImport->ModelXML.PartInfoXML->at(i).VisibleF)
					{
						if (std::strcmp((mdlImport->ModelXML.PartInfoXML->at(i).Visible.Parameter.Sim.Variable).c_str(), variable.c_str()) == 0)
						{
							if (std::strcmp((mdlImport->ModelXML.PartInfoXML->at(i).Visible.Parameter.Sim.Units).c_str(), unit.c_str()) == 0)
							{
								if (mdlImport->ModelXML.PartInfoXML->at(i).Visible.Parameter.Sim.BiasF == (ReturnArr.size() >= 4))
								{
									if (mdlImport->ModelXML.PartInfoXML->at(i).Visible.Parameter.Sim.Bias == std::atof(bias.c_str()))
									{
										if (mdlImport->ModelXML.PartInfoXML->at(i).Visible.Parameter.LagF == (ReturnArr.size() >= 5))
										{
											if (mdlImport->ModelXML.PartInfoXML->at(i).Visible.Parameter.Lag == std::atof(lag.c_str()))
											{
												ReturnArr[0] = mdlImport->ModelXML.PartInfoXML->at(i).Name;
												break;
											}
										}
									}
								}
							}
						}
					}


				}
			
				if (i == mdlImport->ModelXML.PartInfoXML->size())
				{
					ReturnArr[0] = "custom_vis_" + ReturnArr[0];
					if (UniVISI < 10)
					{
						ReturnArr[0] = ReturnArr[0] + "_0" + std::to_string(UniVISI);
					}
					else
					{
						ReturnArr[0] = ReturnArr[0] + "_" + std::to_string(UniVISI);
					}
				}
			}
			if (type == 1)
			{
				for (i = 0; i < mdlImport->ModelXML.PartInfoXML->size(); i++)
				{
					if (mdlImport->ModelXML.PartInfoXML->at(i).AnimationF)
					{
						if (std::strcmp((mdlImport->ModelXML.PartInfoXML->at(i).Animation.Parameter.Sim.Variable).c_str(), variable.c_str()) == 0)
						{
							if (std::strcmp((mdlImport->ModelXML.PartInfoXML->at(i).Animation.Parameter.Sim.Units).c_str(), unit.c_str()) == 0)
							{
								if (mdlImport->ModelXML.PartInfoXML->at(i).Animation.Parameter.Sim.BiasF == (ReturnArr.size() >= 4))
								{
									if (mdlImport->ModelXML.PartInfoXML->at(i).Animation.Parameter.Sim.Bias == std::atof(bias.c_str()))
									{
										if (mdlImport->ModelXML.PartInfoXML->at(i).Animation.Parameter.LagF == (ReturnArr.size() >= 5))
										{
											if (mdlImport->ModelXML.PartInfoXML->at(i).Animation.Parameter.Lag == std::atof(lag.c_str()))
											{
												ReturnArr[0] = mdlImport->ModelXML.PartInfoXML->at(i).Name;
												break;
											}
										}
									}
								}
							}
						}

					}

				}
				if (i == mdlImport->ModelXML.PartInfoXML->size())
				{
					ReturnArr[0] = "custom_anim_" + ReturnArr[0];
				}
			}
			
		}
	}
	return ReturnArr;
}

HRESULT RIFF::ReadSectionsHierarhy()
{
	ReadSection();
	return 0;
}

UINT RIFF::UINT2(char Name[4])
{
	return Name[3] + Name[2] * 0x100 + Name[1] * 0x10000 + Name[0] * 0x1000000;
}



HRESULT RIFF::ReadSection(int parent)
{
	RIFFSectionHeader Temp;
	RIFFStream->Read(&Temp, Seek, sizeof(Temp));
	Seek = Seek + sizeof(Temp);

	UINT64 EndSection = Seek + Temp.Size;

	char* str;

	switch (UINT2(Temp.Name))
	{
	case (UINT('RIFF')):
	{
		if (parent == 0)
		{
			RIFFStream->Read(&RIFFData, Seek, sizeof(RIFFData));
			Seek = Seek + sizeof(RIFFData);

		}
		while (Seek < EndSection)
		{
			ReadSection(parent + 1);
		}
		break;
	}
	case (UINT('MDLH')):
	{

		RIFFStream->Read(&MDLH, Seek, sizeof(MDLH));
		Seek = Seek + sizeof(MDLH);
		break;
	}
	case (UINT('RADI')):
	{

		RIFFStream->Read(&RADI, Seek, sizeof(RADI));
		Seek = Seek + sizeof(RADI);
		break;
	}
	case (UINT('TEXT')):
	{
		char str[64];
		while (Seek < EndSection)
		{
			RIFFStream->Read(&str, Seek, sizeof(str));
			Seek = Seek + sizeof(str);
			std::string s = std::string(str);
			TEXT->push_back(std::wstring(s.begin(),s.end()));
		}
		break;
	}
	case (UINT('MAT3')):
	{
		while (Seek < EndSection)
		{
			SMAT3 lMAT3;
			RIFFStream->Read(&lMAT3, Seek, sizeof(lMAT3));
			int temp = sizeof(lMAT3);
			Seek = Seek + sizeof(lMAT3);
			MAT3->push_back(lMAT3);
		}
		break;
	}
	case (UINT('PBRM')):
	{
		while (Seek < EndSection)
		{
			SPBRM lPBRM;
			RIFFStream->Read(&lPBRM, Seek, sizeof(lPBRM));
			int temp = sizeof(lPBRM);
			Seek = Seek + sizeof(lPBRM);
			PBRM->push_back(lPBRM);
		}
		break;
	}
	case (UINT('MATE')):
	{
		while (Seek < EndSection)
		{
			SMAT3 lMAT3;
			RIFFStream->Read(&lMAT3, Seek, sizeof(lMAT3) - 4);
			int temp = sizeof(lMAT3) - 4;
			Seek = Seek + sizeof(lMAT3) - 4;
			lMAT3.zbias = 0.0;
			MAT3->push_back(lMAT3);
		}
		break;
	}
	case (UINT('EMT1')):
	{
		while (Seek < EndSection)
		{
			SEMT1 lEMT1;
			RIFFStream->Read(&lEMT1, Seek, sizeof(lEMT1));
			int temp = sizeof(lEMT1);
			Seek = Seek + sizeof(lEMT1);
			EMT1->push_back(lEMT1);
		}
		break;

	}
	case (UINT('IND3')):
	{
		int count = 0;
		while (Seek < EndSection)
		{
			SIND3 lIND3;
			RIFFStream->Read(&lIND3, Seek, sizeof(lIND3));
			int temp = sizeof(lIND3);
			Seek = Seek + sizeof(lIND3);
			IND3->push_back(lIND3);
			count++;
		}
		break;
	}
	case (UINT('INDE')):
	{
		int count = 0;
		while (Seek < EndSection)
		{
			SINDE lINDE;
			SIND3 lIND3;
			RIFFStream->Read(&lINDE, Seek, sizeof(lINDE));
			int temp = sizeof(lINDE);
			Seek = Seek + sizeof(lINDE);
			lIND3.ind1 = lINDE.ind1;
			lIND3.ind2 = lINDE.ind2;
			lIND3.ind3 = lINDE.ind3;
			IND3->push_back(lIND3);
			count++;
		}
		break;
	}
	case (UINT('TRAN')):
	{
		int count = 0;
		while (Seek < EndSection)
		{
			STRAN lTRAN;
			RIFFStream->Read(&lTRAN, Seek, sizeof(lTRAN));
			int temp = sizeof(lTRAN);
			Seek = Seek + sizeof(lTRAN);
			TRAN->push_back(lTRAN);
			count++;
		}
		break;
	}
	case (UINT('SCEN')):
	{
		int count = 0;
		while (Seek < EndSection)
		{
			SSCEN lSCEN;
			lSCEN.parentNode = NULL;
			RIFFStream->Read(&lSCEN, Seek, sizeof(lSCEN) - 8);
			int temp = sizeof(lSCEN) - 8;
			Seek = Seek + sizeof(lSCEN) - 8;
			lSCEN.parent = -1;
			SCEN->push_back(lSCEN);
			count++;
		}
		short child, peer, thismatrix, parent;
		short xchild, xpeer, xthismatrix, xparent;
		for (int i = 0; i < SCEN->size(); i++)
		{
			child = SCEN->at(i).child_node_index;
			peer = SCEN->at(i).peer_node_index;
			thismatrix = SCEN->at(i).amap_offset;
			parent = SCEN->at(i).parent;
			if (SCEN->at(i).child_node_index != -1)
			{
				SCEN->at(child).parent = i;
			}
			if (SCEN->at(i).peer_node_index != -1)
			{
				SCEN->at(peer).parent = SCEN->at(i).parent;
			}
		}
		break;
	}
	case (UINT('AMAP')):
	{
		int count = 0;
		while (Seek < EndSection)
		{
			SAMAP lAMAP;
			RIFFStream->Read(&lAMAP, Seek, sizeof(lAMAP));
			int temp = sizeof(lAMAP);
			Seek = Seek + sizeof(lAMAP);
			AMAP->push_back(lAMAP);
			count++;
		}
		break;
	}
	case (UINT('SGAL')):
	{
		int count = 0;
		while (Seek < EndSection)
		{
			SSGAL lSGAL;
			RIFFStream->Read(&lSGAL, Seek, sizeof(lSGAL));
			int temp = sizeof(lSGAL);
			Seek = Seek + sizeof(lSGAL);
			SGAL->push_back(lSGAL);
			count++;
		}
		break;
	}
	case (UINT('SGBR')):
	{
		int count = 0;
		while (Seek < EndSection)
		{
			SSGBR lSGBR;
			RIFFStream->Read(&lSGBR, Seek, sizeof(lSGBR));
			int temp = sizeof(lSGBR);
			Seek = Seek + sizeof(lSGBR);
			SGBR->push_back(lSGBR);
			count++;
		}
		break;
	}
	case (UINT('SGVL')):
	{
		int count = 0;
		while (Seek < EndSection)
		{
			SSGVL lSGVL;
			RIFFStream->Read(&lSGVL, Seek, sizeof(lSGVL));
			int temp = sizeof(lSGVL);
			Seek = Seek + sizeof(lSGVL);
			SGVL->push_back(lSGVL);
			count++;
		}
		break;
	}
	case (UINT('MDLG')):
	{

		RIFFStream->Read(&MDLG, Seek, sizeof(MDLG));
		Seek = Seek + sizeof(MDLG);
		char str[100];
		sprintf(str, "{%X-%X-%X-%X%X-%X%X%X%X%X%X}",
			MDLG.data1,
			MDLG.data2,
			MDLG.data3,
			MDLG.data4[0],
			MDLG.data4[1],
			MDLG.data4[2],
			MDLG.data4[3],
			MDLG.data4[4],
			MDLG.data4[5],
			MDLG.data4[6],
			MDLG.data4[7]
		);
		break;
	}
	case (UINT('MDLN')):
	{
		char str[256];
		RIFFStream->Read(&str, Seek, Temp.Size);
		Seek = Seek + Temp.Size;
		MDLN = str;
		ModelName = std::wstring(MDLN.begin(), MDLN.end());

		break;
	}
	case (UINT('BBOX')):
	{
		RIFFStream->Read(&BBOX, Seek, sizeof(BBOX));
		Seek = Seek + sizeof(BBOX);
		break;
	}
	case (UINT('MDLD')):
	{
		while (Seek < EndSection)
		{
			ReadSection(parent + 1);
		}
		break;
	}
	case (UINT('VERB')):
	{
		//CurrVERB = new SVERB();
		int count = 0;

		while (Seek < EndSection)
		{
			ReadSection(parent + 1);
			count++;
		}
		VERB->push_back(CurrVERB);
		break;
	}
	case (UINT('VERT')):
	{

		if (CurrVERB.VERT != NULL)
		{
			VERB->push_back(CurrVERB);
		}
		CurrVERB = { NULL,NULL,NULL };
		//VERB->push_back(CurrVERB);
		int count = 0;
		CurrVERB.VERT = new std::vector<SVERT>();
		while (Seek < EndSection)
		{
			SVERT lVERT;
			RIFFStream->Read(&lVERT, Seek, sizeof(lVERT));
			int temp = sizeof(lVERT);
			Seek = Seek + sizeof(lVERT);
			CurrVERB.VERT->push_back(lVERT);
			count++;
		}
		break;
	}
	case (UINT('BMAP')):
	{
		int VERBIndex = 0;
		RIFFStream->Read(&VERBIndex, Seek, sizeof(VERBIndex));
		Seek = Seek + sizeof(VERBIndex);
		SBMAP lBMAP;
		CurrVERB.BMAP = new std::vector<SBMAP>();
		while (Seek < EndSection)
		{
			RIFFStream->Read(&lBMAP, Seek, sizeof(lBMAP));
			Seek = Seek + sizeof(lBMAP);
			CurrVERB.BMAP->push_back(lBMAP);
		}
		break;
	}
	case (UINT('SKIN')):
	{
		int VERBIndex = 0;
		RIFFStream->Read(&VERBIndex, Seek, sizeof(VERBIndex));
		Seek = Seek + sizeof(VERBIndex);
		SSKIN lSKIN;
		CurrVERB.SKIN = new std::vector<SSKIN>();
		while (Seek < EndSection)
		{
			RIFFStream->Read(&lSKIN, Seek, sizeof(lSKIN));
			Seek = Seek + sizeof(lSKIN);
			CurrVERB.SKIN->push_back(lSKIN);
		}
		break;
	}
	case (UINT('VISL')):
	{
		while (Seek < EndSection)
		{
			ReadSection(parent + 1);
		}
		break;
	}
	case (UINT('VISC')):
	{
		SVisible lVis;
		SVISI lVISI;
		std::string str = "";
		std::vector<char> lCode;
		std::vector<std::string> Result;
		str.resize(Temp.Size);
		RIFFStream->Read(&str[0], Seek, Temp.Size);
		Seek = Seek + Temp.Size;

		Result = ConvertVisAnim(str, 2, 2, 0);


		int ui = 0;
		for (ui = 0; ui < VISI->size(); ui++)
		{
			if (VISI->at(ui).CodeF)
			{
				if (VISI->at(ui).name == Result[0])
				{
					break;
				}
			}
		}
		if (ui < VISI->size())
		{
			VISI->push_back(VISI->at(ui));
		}
		else
		{
			lVISI.Default = 1;
			lVISI.CodeF = true;
			lVISI.Code = Result[1];
			lVISI.name = Result[0];
			if (Result.size() == 3)
			{
				lVISI.LagF = true;
				lVISI.Lag = std::atof(Result[2].c_str());
			}
			VISI->push_back(lVISI);
			UniVISI++;
		}

		break;
	}

	case (UINT('VINC')):
	{
		SVisible lVis;
		SVISI lVISI;
		std::string str = "";
		std::vector<char> lCode;
		std::vector<std::string> Result;
		str.resize(Temp.Size);
		RIFFStream->Read(&str[0], Seek, Temp.Size);
		Seek = Seek + Temp.Size;

		Result = ConvertVisAnim(str, 2, 2, 0);


		int ui = 0;
		for (ui = 0; ui < VISI->size(); ui++)
		{
			if (VISI->at(ui).CodeF)
			{
				if (VISI->at(ui).name == Result[0])
				{
					break;
				}
			}
		}
		if (ui < VISI->size())
		{
			VISI->push_back(VISI->at(ui));
		}
		else
		{
			lVISI.Default = false;
			lVISI.CodeF = true;
			lVISI.Code = Result[1];
			lVISI.name = Result[0];
			if (Result.size() == 3)
			{
				lVISI.LagF = true;
				lVISI.Lag = std::atof(Result[2].c_str());
			}
			VISI->push_back(lVISI);
			UniVISI++;
		}

		break;
	}
	case (UINT('VISS')):
	{
		SVisible lVis;
		SVISI lVISI;
		std::string str = "";
		std::vector<char> lCode;
		std::vector<std::string> Result;
		str.resize(Temp.Size);
		RIFFStream->Read(&str[0], Seek, Temp.Size);
		Seek = Seek + Temp.Size;

		Result = ConvertVisAnim(str, 4, 1, 0);

		int ui = 0;
		for (ui = 0; ui < VISI->size(); ui++)
		{
			if (VISI->at(ui).SimF)
			{
				if (VISI->at(ui).name == Result[0])
				{
					break;
				}
			}
		}
		if (ui < VISI->size())
		{
			VISI->push_back(VISI->at(ui));
		}
		else
		{
			lVISI.Default = 1;
			lVISI.SimF = true;
			lVISI.Sim.Variable = Result[1];
			lVISI.Sim.Units = Result[2];
			if (Result.size() == 4)
			{
				lVISI.Sim.Bias = std::atof(Result[3].c_str());
			}
			if (Result.size() == 5)
			{
				lVISI.LagF = true;
				lVISI.Lag = std::atof(Result[4].c_str());
			}
			lVISI.name = Result[0];
			VISI->push_back(lVISI);
			UniVISI++;
		}

		break;
	}
	case (UINT('XAPS')):
	{

		SModelDefXML lAnim;
		SXAPI lXAPI;
		std::string str = "";
		std::vector<char> lCode;
		std::vector<std::string> Result;
		str.resize(Temp.Size);
		RIFFStream->Read(&str[0], Seek, Temp.Size);
		Seek = Seek + Temp.Size;
		int i = 0;
		for (i = 0; i < mdlImport->ModelXML.AnimationXML->size(); i++)
		{
			if (!std::strcmp(strlwr((char*)(mdlImport->BytesToGUID(CurrXANI->guid).c_str())), strlwr((char*)(mdlImport->ModelXML.AnimationXML->at(i).guid.c_str()))))
			{
				break;
			}
		}
		
		Result = ConvertVisAnim(str, 4, 1, 1);

		lXAPI.SimF = true;
		lXAPI.Sim.Variable = Result[1];
		lXAPI.Sim.Units = Result[2];
		if (Result.size() == 4)
		{
			lXAPI.Sim.Bias = std::atof(Result[3].c_str());
		}
		if (Result.size() == 5)
		{
			lXAPI.LagF = true;
			lXAPI.Lag = std::atof(Result[4].c_str());
		}
		if (i < mdlImport->ModelXML.AnimationXML->size())
		{
			lXAPI.name = mdlImport->ModelXML.AnimationXML->at(i).name;
		}
		else
		{
			lXAPI.name = Result[0];
		}
		CurrXANI->XAPI = lXAPI;
		UniXAPI++;


		break;
	}
	case (UINT('XAPC')):
	{
		SAnimationPart lAnim;
		SXAPI lXAPI;
		std::string str = "";
		std::vector<char> lCode;
		std::vector<std::string> Result;
		str.resize(Temp.Size);
		RIFFStream->Read(&str[0], Seek, Temp.Size);
		Seek = Seek + Temp.Size;
		int i = 0;
		for (i = 0; i < mdlImport->ModelXML.AnimationXML->size(); i++)
		{
			if (!std::strcmp(strlwr((char*)(mdlImport->BytesToGUID(CurrXANI->guid).c_str())), strlwr((char*)(mdlImport->ModelXML.AnimationXML->at(i).guid.c_str()))))
			{
				break;
			}
		}
		Result = ConvertVisAnim(str, 2, 2, 1);

		lXAPI.CodeF = true;
		lXAPI.Code = Result[1];
		if (i < mdlImport->ModelXML.AnimationXML->size())
		{
			lXAPI.name = mdlImport->ModelXML.AnimationXML->at(i).name;
		}
		else
		{
			lXAPI.name = Result[0];
		}
		if (Result.size() == 3)
		{
			lXAPI.LagF = true;
			lXAPI.Lag = std::atof(Result[2].c_str());
		}
		CurrXANI->XAPI = lXAPI;
		UniXAPI++;


		break;
	}
	case (UINT('VINS')):
	{
		SVisible lVis;
		SVISI lVISI;
		std::string str = "";
		std::vector<char> lCode;
		std::vector<std::string> Result;
		str.resize(Temp.Size);
		RIFFStream->Read(&str[0], Seek, Temp.Size);
		Seek = Seek + Temp.Size;
		Result = ConvertVisAnim(str, 4, 1, 0);

		int ui = 0;
		for (ui = 0; ui < VISI->size(); ui++)
		{
			if (VISI->at(ui).SimF)
			{
				if (VISI->at(ui).name == Result[0])
				{
					break;
				}
			}
		}
		if (ui < VISI->size())
		{
			VISI->push_back(VISI->at(ui));
		}
		else
		{
			lVISI.Default = 0;
			lVISI.SimF = true;
			lVISI.Sim.Variable = Result[1];
			lVISI.Sim.Units = Result[2];
			if (Result.size() == 4)
			{
				lVISI.Sim.Bias = std::atof(Result[3].c_str());
			}
			if (Result.size() == 5)
			{
				lVISI.LagF = true;
				lVISI.Lag = std::atof(Result[4].c_str());
			}
			lVISI.name = Result[0];
			VISI->push_back(lVISI);
			UniVISI++;
		}
		break;
	}

	case (UINT('SGBN')):
	{
		SSGBN lSGBN;
		std::vector<char> lBoneName;
		lBoneName.resize(64);
		while (Seek < EndSection)
		{
			lSGBN.bone_name = "";
			RIFFStream->Read(&lBoneName[0], Seek, 64);
			Seek = Seek + 64;
			lSGBN.bone_name = std::string(&lBoneName[0]);
			SGBN->push_back(lSGBN);
		}

		break;
	}

	case (UINT('LODT')):
	{
		while (Seek < EndSection)
		{
			ReadSection(parent + 1);
			LODT->push_back(CurrLOD);
		}
		break;
	}
	case (UINT('LODE')):
	{
		RIFFStream->Read(&LODEData, Seek, sizeof(LODEData));
		Seek = Seek + sizeof(LODEData);
		CurrLOD.LOD = LODEData.LOD;
		CurrLOD.PART = new std::vector<SPART>();
		while (Seek < EndSection)
		{
			ReadSection(parent + 1);
		}

		break;
	}
	case (UINT('PART')):
	{
		SPART PartTemp;
		RIFFStream->Read(&PartTemp, Seek, sizeof(PartTemp));
		Seek = Seek + sizeof(PartTemp);
		CurrLOD.PART->push_back(PartTemp);
		//DrawPart(this, &PartTemp);
		break;
	}
	case (UINT('ANIB')):
	{
		UINT64 off = Temp.Size + Seek;
		//while (Seek < EndSection)
		{
			ReadSection(parent + 1);
		}
		Seek = off;
		break;
	}
	case (UINT('XANL')):
	{
		while (Seek < EndSection)
		{
			ReadSection(parent + 1);
		}
		break;
	}
	case (UINT('XANI')):
	{
		SXANI lXANI;
		RIFFStream->Read(&lXANI, Seek, sizeof(lXANI) - 16 - sizeof(SXAPI));
		Seek = Seek + sizeof(lXANI) - 16 - sizeof(SXAPI);
		lXANI.XANS = new std::vector<SXANS>();
		std::string* lS = new std::string();
		char s = ' ';
		while (int(s) != 0)
		{
			RIFFStream->Read(&s, Seek, sizeof(char));
			Seek = Seek + sizeof(char);
			//lS->append(&s);
			lS->append(&s, 1);
			//lS = lS + s;

		}
		lXANI.typeParam = lS;
		/*for (int jj = 0; jj < AnimationXML->size(); jj++)
		{
			if (std::strcmp(strlwr((char*)ss.c_str()), strlwr((char*)AnimationXML->at(jj).guid.c_str())) == 0)
			{
			}
		}*/
		XANI->push_back(lXANI);
		CurrXANI = &(XANI->at(XANI->size() - 1));

		break;
	}
	case (UINT('XANS')):
	{
		SXANS lXANS;
		RIFFStream->Read(&lXANS, Seek, sizeof(lXANS) - 8);
		Seek = Seek + sizeof(lXANS) - 8;
		lXANS.XANK = new std::vector<SXANK>();
		CurrXANI->XANS->push_back(lXANS);

		CurrXANS = &CurrXANI->XANS->at(CurrXANI->XANS->size() - 1);;

		break;
	}
	case (UINT('XANK')):
	{
		SXANKH lXANKH;
		SXANKT lXANKT;
		SXANKR lXANKR;
		SXANK lXANK = { 0 };
		RIFFStream->Read(&lXANKH, Seek, sizeof(lXANKH));
		Seek = Seek + sizeof(lXANKH);
		lXANK.type = lXANKH.type;
		lXANK.time = lXANKH.time;
		if (lXANKH.type == 4)
		{
			RIFFStream->Read(&lXANKR, Seek, sizeof(lXANKR));
			Seek = Seek + sizeof(lXANKR);
			lXANK.q0 = lXANKR.q0;
			lXANK.q1 = lXANKR.q1;
			lXANK.q2 = lXANKR.q2;
			lXANK.q3 = lXANKR.q3;
		}
		else
		{
			RIFFStream->Read(&lXANKT, Seek, sizeof(lXANKT));
			Seek = Seek + sizeof(lXANKT);
			lXANK.x = lXANKT.x;
			lXANK.y = lXANKT.y;
			lXANK.z = lXANKT.z;
		}
		CurrXANS->XANK->push_back(lXANK);
		break;
	}
	case (UINT('PLAL')):
	{
		while (Seek < EndSection)
		{
			ReadSection(parent + 1);
		}
		break;
	}
	case (UINT('REFL')):
	{
		while (Seek < EndSection)
		{
			ReadSection(parent + 1);
		}
		break;
	}
	case (UINT('REFP')):
	{
		SREFP lREFP;
		int SG;
		int SizePoint;
		RIFFStream->Read(&SG, Seek, sizeof(SG));
		Seek = Seek + sizeof(SG);
		RIFFStream->Read(&SizePoint, Seek, sizeof(SizePoint));
		Seek = Seek + sizeof(SizePoint);
		std::vector<char> lName;
		lName.resize(SizePoint);
		RIFFStream->Read(&lName[0], Seek, SizePoint);
		Seek = Seek + SizePoint;
		std::string SName(&lName[0], SizePoint);
		lREFP.scenegraph_reference = SG;
		lREFP.name = SName;
		REFP->push_back(lREFP);
		break;
	}
	case (UINT('ATTO')):
	{
		while (Seek < EndSection)
		{
			SATTO lATTO;
			int Magic1;
			int Magic2;
			short unk1;
			int unk2;
			int unk3;
			int unk4;
			int unk5;
			short type;
			short length;
			short offset;
			char fxName[80];
			RIFFStream->Read(&Magic1, Seek, sizeof(Magic1));
			Seek = Seek + sizeof(Magic1);
			int StartOff = Seek;
			RIFFStream->Read(&type, Seek, sizeof(type));
			Seek = Seek + sizeof(type);
			RIFFStream->Read(&length, Seek, sizeof(length));
			Seek = Seek + sizeof(length);
			RIFFStream->Read(&offset, Seek, sizeof(offset));
			Seek = Seek + sizeof(offset);
			RIFFStream->Read(&unk1, Seek, sizeof(unk1));
			Seek = Seek + sizeof(unk1);
			RIFFStream->Read(&unk2, Seek, sizeof(unk2));
			Seek = Seek + sizeof(unk2);
			RIFFStream->Read(&unk3, Seek, sizeof(unk3));
			Seek = Seek + sizeof(unk3);
			RIFFStream->Read(&unk4, Seek, sizeof(unk4));
			Seek = Seek + sizeof(unk4);
			RIFFStream->Read(&unk5, Seek, sizeof(unk5));
			Seek = Seek + sizeof(unk5);
			RIFFStream->Read(&fxName, Seek, sizeof(fxName));
			Seek = Seek + sizeof(fxName);
			std::vector<char> lParam;
			lParam.resize(StartOff + offset - Seek);
			RIFFStream->Read(&lParam[0], Seek, StartOff + offset - Seek);
			Seek = Seek + StartOff + offset - Seek;
			std::vector<char> lName;
			lName.resize(length - offset);
			RIFFStream->Read(&lName[0], Seek, length - offset);
			Seek = Seek + length - offset;
			std::string SFX(fxName);
			std::string SParam(&lParam[0]);
			std::string SName(&lName[0]);
			RIFFStream->Read(&Magic2, Seek, sizeof(Magic2));
			Seek = Seek + sizeof(Magic2);
			lATTO.attachPoint = SName;
			lATTO.fxName = SFX;
			lATTO.length = length;
			lATTO.Magic1 = Magic1;
			lATTO.Magic2 = Magic2;
			lATTO.offAttachPoint = offset;
			lATTO.params = SParam;
			lATTO.type = type;
			lATTO.unk1 = unk1;
			lATTO.unk2 = unk2;
			lATTO.unk3 = unk3;
			lATTO.unk4 = unk4;
			lATTO.unk5 = unk5;
			ATTO->push_back(lATTO);
		}
		break;
	}
	case (UINT('TANS')):
	{
		Seek = Temp.Size + Seek;
		break;
	}
	default:
	{
		Seek = Temp.Size + Seek;
		bool bf = false;
		for (int i = 0; i < mdlImport->ModelXML.BadSec->size(); i++)
		{
			if (mdlImport->ModelXML.BadSec->at(i) == UINT2(Temp.Name))
			{
				bf = true;
			}
		}
		if (!bf)
		{
//#ifdef DEBUG
			MessageBoxExA(0, (std::string("Unknown section: ") + std::string(Temp.Name, 4)).c_str(), "Warning", MB_OK, 0);
//#endif // DEBUG
			mdlImport->ModelXML.BadSec->push_back(UINT2(Temp.Name));
		}
		break;
	}
	}
	return 0;
}

RIFF::~RIFF()
{
	if (RIFFStream)
	{
		delete RIFFStream;
		RIFFStream = NULL;
	}
	if (RIFFText)
	{
		delete RIFFText;
		RIFFText = NULL;
	}
}

