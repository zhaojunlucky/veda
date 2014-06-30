// ZPEngine.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "ZPEngine.h"


// This is an example of an exported variable
ZPENGINE_API int nZPEngine=0;

// This is an example of an exported function.
ZPENGINE_API int fnZPEngine(void)
{
	return 42;
}

// This is the constructor of a class that has been exported.
// see ZPEngine.h for the class definition
CZPEngine::CZPEngine()
{
	return;
}
