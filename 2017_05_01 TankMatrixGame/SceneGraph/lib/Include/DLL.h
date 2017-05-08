#pragma once

// FYI this would be required if you were creating a dll rather than a lib file
#ifdef MYMATHLIB_EXPORTS
#define LIBRARY_API   __declspec(dllexport) 
#else 
#define LIBRARY_API   __declspec(dllimport) 
#endif