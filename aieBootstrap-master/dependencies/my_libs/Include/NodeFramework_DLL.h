#pragma once

// FYI this would be required if you were creating a dll. LIBRARY_API needs to be in front of every class name and separate functions!
// Make sure there is NO POSSIBLE WAY LIBRARY_API will end up as __declspec(dllimport) because otherwise it'll throw up unresolved __declspec(dllimport) errors.

/*The set up before had an #else that then checked if it was _LIB and if not it was __declspec(dllimport). This caused
unresolved externals because the project running it didn't have EXPORTS defined or _LIB and so it made LIBRARY_API __declspec(dllimport),
meaning every single declaration that had it in front was now no longer valid.*/

#ifdef NODEFRAMEWORK_EXPORTS
///DLL
#define NODE_LIBRARY_API   __declspec(dllexport)
#else
#define NODE_LIBRARY_API
#endif
