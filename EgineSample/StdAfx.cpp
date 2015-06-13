/*************************
* Author: CJ McAllister  *
*                        *
* Created on: 2014-04-14 *
*************************/

#include "StdAfx.h"
__int64 PCFreq = 0;
__int64 CounterStart = 0;

HRESULT StartCounter()
{
	HRESULT hr = S_OK;

	hr |= QueryPerformanceFrequency((LARGE_INTEGER *)&PCFreq) ? S_OK : E_FAIL;
	hr |= QueryPerformanceCounter((LARGE_INTEGER *)&CounterStart) ? S_OK : E_FAIL;
	
	return hr;
}
