// 03-Smoothing.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "03-Smoothing.h"
#include "SmoothingViewer.hh"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// The one and only application object

CWinApp theApp;

using namespace std;

int _tmain(int argc, TCHAR* argv[], TCHAR* envp[])
{
	int nRetCode = 0;

	// initialize MFC and print and error on failure
	if (!AfxWinInit(::GetModuleHandle(NULL), NULL, ::GetCommandLine(), 0))
	{
		// TODO: change error code to suit your needs
		_tprintf(_T("Fatal Error: MFC initialization failed\n"));
		nRetCode = 1;
	}
	else
	{
		// TODO: code your application's behavior here.
		 //glutInit(&argc, argv);

	  SmoothingViewer window("Smoothing", 512, 512);

	  //if (argc>1)
		//window.open_mesh(argv[1]);

	  glutMainLoop();

	  //delete[] window;
	}

	return nRetCode;
}
