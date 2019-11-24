//**************************************************************************/
// Copyright (c) 1998-2007 Autodesk, Inc.
// All rights reserved.
// 
// These coded instructions, statements, and computer programs contain
// unpublished proprietary information written by Autodesk, Inc., and are
// protected by Federal copyright law. They may not be disclosed to third
// parties or copied or duplicated in any form, in whole or in part, without
// the prior written consent of Autodesk, Inc.
//**************************************************************************/
// DESCRIPTION: Appwizard generated plugin
// AUTHOR: 
//***************************************************************************/

#include "MDLConverterv2.h"
#include <memory>
using namespace std;


#define MDLConverterv2_CLASS_ID	Class_ID(0x9a4c648d, 0x54080edb)


class MDLConverterv2 : public SceneImport
{
public:
	//Constructor/Destructor
	MDLConverterv2();
	virtual ~MDLConverterv2();

	virtual int				ExtCount();					// Number of extensions supported
	virtual const TCHAR *	Ext(int n);					// Extension 0n (i.e. "3DS")
	virtual const TCHAR *	LongDesc();					// Long ASCII description (i.e. "Autodesk 3D Studio File")
	virtual const TCHAR *	ShortDesc();				// Short ASCII description (i.e. "3D Studio")
	virtual const TCHAR *	AuthorName();				// ASCII Author name
	virtual const TCHAR *	CopyrightMessage();			// ASCII Copyright message
	virtual const TCHAR *	OtherMessage1();			// Other message 01
	virtual const TCHAR *	OtherMessage2();			// Other message 02
	virtual unsigned int	Version();					// Version number * 100 (i.e. v3.01 = 301)
	virtual void			ShowAbout(HWND hWnd);		// Show DLL's "About..." box
	virtual int				DoImport(const TCHAR *name,ImpInterface *i,Interface *gi, BOOL suppressPrompts=FALSE);	// Import file

};



class MDLConverterv2ClassDesc : public ClassDesc2 
{
public:
	virtual int IsPublic() 							{ return TRUE; }
	virtual void* Create(BOOL /*loading = FALSE*/) 		{ return new MDLConverterv2(); }
	virtual const TCHAR *	ClassName() 			{ return GetString(IDS_CLASS_NAME); }
	virtual SClass_ID SuperClassID() 				{ return SCENE_IMPORT_CLASS_ID; }
	virtual Class_ID ClassID() 						{ return MDLConverterv2_CLASS_ID; }
	virtual const TCHAR* Category() 				{ return GetString(IDS_CATEGORY); }

	virtual const TCHAR* InternalName() 			{ return _T("MDLConverterv2"); }	// returns fixed parsable name (scripter-visible name)
	virtual HINSTANCE HInstance() 					{ return hInstance; }					// returns owning module handle
	

};


ClassDesc2* GetMDLConverterv2Desc() { 
	static MDLConverterv2ClassDesc MDLConverterv2Desc;
	return &MDLConverterv2Desc; 
}




INT_PTR CALLBACK MDLConverterv2OptionsDlgProc(HWND hWnd,UINT message,WPARAM ,LPARAM lParam) {
	static MDLConverterv2* imp = nullptr;

	switch(message) {
		case WM_INITDIALOG:
			imp = (MDLConverterv2 *)lParam;
			CenterWindow(hWnd,GetParent(hWnd));
			return TRUE;

		case WM_CLOSE:
			EndDialog(hWnd, 0);
			return 1;
	}
	return 0;
}


//--- MDLConverterv2 -------------------------------------------------------
MDLConverterv2::MDLConverterv2()
{

}

MDLConverterv2::~MDLConverterv2() 
{

}

int MDLConverterv2::ExtCount()
{
	#pragma message(TODO("Returns the number of file name extensions supported by the plug-in."))
	return 1;
}

const TCHAR *MDLConverterv2::Ext(int /*n*/)
{		
	#pragma message(TODO("Return the 'i-th' file name extension (i.e. \"3DS\")."))
	return _T("MDL");
}

const TCHAR *MDLConverterv2::LongDesc()
{
	#pragma message(TODO("Return long ASCII description (i.e. \"Targa 2.0 Image File\")"))
	return _T("Flight Simulator X MDL File");
}
	
const TCHAR *MDLConverterv2::ShortDesc() 
{			
	#pragma message(TODO("Return short ASCII description (i.e. \"Targa\")"))
	return _T("RIFF Model");
}

const TCHAR *MDLConverterv2::AuthorName()
{			
	#pragma message(TODO("Return ASCII Author name"))
	return _T("Igor M.");
}

const TCHAR *MDLConverterv2::CopyrightMessage() 
{	
	#pragma message(TODO("Return ASCII Copyright message"))
	return _T("");
}

const TCHAR *MDLConverterv2::OtherMessage1() 
{		
	//TODO: Return Other message 01 if any
	return _T("");
}

const TCHAR *MDLConverterv2::OtherMessage2() 
{		
	//TODO: Return other message 02 in any
	return _T("");
}

unsigned int MDLConverterv2::Version()
{				
	#pragma message(TODO("Return Version number * 100 (i.e. v3.01 = 301)"))
	return 025;
}

void MDLConverterv2::ShowAbout(HWND /*hWnd*/)
{			
	// Optional
}

int MDLConverterv2::DoImport(const TCHAR * filename, ImpInterface * i, Interface * gi, BOOL suppressPrompts)
{
#pragma message(TODO("Implement the actual file import here and"))	
	
	char RIFFSign[4];
	char RIFFVer[4];
	ReadStream* RIFFStream = new ReadStream(filename);
	RIFFStream->Read(&RIFFSign, 0, 4);
	RIFFStream->Read(&RIFFVer, 8, 4);
	RIFFStream;

	if (RIFF::UINT2(RIFFSign) == UINT('RIFF'))
	{
		if (RIFF::UINT2(RIFFVer) == UINT('MDLX') ||
			RIFF::UINT2(RIFFVer) == UINT('PV20'))
		{
			MDLImport* MDL = new MDLImport(filename, i, gi, suppressPrompts);
			delete MDL;
			MDL = NULL;
		}
		else
		{
			std::string s = std::string(RIFFVer,4);
			MessageBoxEx(0, std::wstring(L"Not supported RIFF version \'" + std::wstring(s.begin(), s.end()) + L"\'").c_str(), L"RIFF Not supported", MB_OK, 0);
			return -1;
		}
	}
	else
	{
		MessageBoxEx(0, L"Not supported MDL File", L"Error", MB_OK, 0);
		return -1;
	}
	
	return 1;
	
}
	
