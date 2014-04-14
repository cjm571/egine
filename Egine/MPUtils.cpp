/*************************
* Author: CJ McAllister  *
*                        *
* Created on: 2014-04-14 *
*************************/

#include "MPUtils.h"

/***** FUNCTIONS *****/
bool SUCCEEDED(PHRESULT hr)
{
	return (hr == S_OK);
}

/***** CONSTANTS *****/
const PHRESULT S_OK		= 0x00000000;
const PHRESULT E_FAIL	= 0x80004005;