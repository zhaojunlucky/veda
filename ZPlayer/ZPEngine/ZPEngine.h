// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the ZPENGINE_EXPORTS
// symbol defined on the command line. This symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// ZPENGINE_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.
#ifdef ZPENGINE_EXPORTS
#define ZPENGINE_API __declspec(dllexport)
#else
#define ZPENGINE_API __declspec(dllimport)
#endif

// This class is exported from the ZPEngine.dll
class ZPENGINE_API CZPEngine {
public:
	CZPEngine(void);
	// TODO: add your methods here.
};

extern ZPENGINE_API int nZPEngine;

ZPENGINE_API int fnZPEngine(void);
