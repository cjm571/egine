/*************************
* Author: CJ McAllister  *
*                        *
* Created on: 2014-02-07 *
*************************/

// Windows header files
#include <Windows.h>

// C Runtime header files
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <wchar.h>
#include <math.h>

#include <d2d1.h>
#include <d2d1helper.h>
#include <dwrite.h>
#include <wincodec.h>

template <class Interface>
inline void SafeRelease( Interface **ppInterfaceToRelease )
{
	if (*ppInterfaceToRelease != NULL)
	{
		(*ppInterfaceToRelease)->Release();
		(*ppInterfaceToRelease) = NULL;
	}
}

#ifndef Assert
	#if defined(DEBUG) || defined(_DEBUG)
		#define Assert(b) do{if (!(b)) {OutputDebugStringA("Assert: " #b "\n");}} while(0)
	#else
		#define Assert(b)
	#endif
#endif

#ifndef HINST_THISCOMPONENT
	EXTERN_C IMAGE_DOS_HEADER __ImageBase;
	#define HINST_THISCOMPONENT ((HINSTANCE)&__ImageBase)
#endif
