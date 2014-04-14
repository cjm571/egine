/*************************
* Author: CJ McAllister  *
*                        *
* Created on: 2014-04-14 *
*************************/
#pragma once

// File Description:
// Contains typedefs/function declarations/etc that are useful for multi-platform development


/***** TYPEDEFS *****/
typedef unsigned int UINT;
typedef unsigned long ULONG;
typedef UINT PHRESULT;

// PhysicsObject colors
enum Color : UINT
{
	Black	= 0x000000,
	White	= 0xFFFFFF,
	Red		= 0xFF0000,
	Orange	= 0xFF6600,
	Yellow	= 0xFFFF00,
	Green	= 0x00FF00,
	Blue	= 0x0000FF,
	Indigo	= 0x2E0854,
	Violet	= 0x8F5E99
};

/***** FUNCTION DECLARATIONS *****/
bool SUCCEEDED(PHRESULT hr);

/***** CONSTANTS *****/
// Success
extern const PHRESULT S_OK;
// General failure
extern const PHRESULT E_FAIL;
