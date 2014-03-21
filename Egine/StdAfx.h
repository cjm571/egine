/*************************
* Author: CJ McAllister  *
*                        *
* Created on: 2014-02-07 *
*************************/
#pragma once

// Modify the following defines if you have to target a platform prior to the ones specified below.
// Refer to MSDN for the latest info on corresponding values for different platforms.
#ifndef WINVER              // Allow use of features specific to Windows 7 or later.
#define WINVER 0x0700       // Change this to the appropriate value to target other versions of Windows.
#endif

#ifndef _WIN32_WINNT        // Allow use of features specific to Windows 7 or later.
#define _WIN32_WINNT 0x0700 // Change this to the appropriate value to target other versions of Windows.
#endif

#ifndef UNICODE
#define UNICODE
#endif

// Exclude rarely-used items from Windows headers.
#define WIN32_LEAN_AND_MEAN

// Allow use of math.h #defines
#define _USE_MATH_DEFINES

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

/***** GLOBAL TYPES *****/
// Represents Cartesian (x,y) coordinates of a physics object
typedef struct
{
	double x;
	double y;
} CartPoint;

// Represents Polar (r,theta) coordinates of a physics object
typedef struct
{
	double r;
	double theta;
} PolarPoint;


/***** GLOBAL HELPER FUNCTIONS *****/
// Converts Cartesian coordinates to Polar
extern PolarPoint CartToPolar(CartPoint cPoint);
// Converts Polar coordinates to Cartesian
extern CartPoint PolarToCart(PolarPoint pPoint);
// Wraps angles between 0 and 2pi
extern double WrapAngle(double angle);

// Enumeration of valid physics object Shapes
enum eShape
{
	PhysCircle = 0,
	PhysTriangle = 1,
	PhysRectangle = 2
};

// Denotes axis of collision
enum eAxis
{
	XAxis = 0,
	YAxis = 1,
	BothAxes = 2,
	AxisErr = -1
};

// Flag indicating desired coordinate system
enum eCoordSys
{
	Physics = 0,
	Drawing = 1
};


/***** SCENE PARAMETERS *****/
// Scene width in meters
// 03/07/14: currently 1m = 1px
extern double SCENE_WIDTH;
// Scene height in meters (03/07/14 currently 1m = 1px)
extern double SCENE_HEIGHT;


/***** SCENE CREATION FLAGS *****/
// Created Scene will have gravity
extern UINT SC_GRAVITY_ON;
// Created Scene will have 0 gravity
extern UINT SC_GRAVITY_OFF;


/***** SCENE CREATION MASKS *****/
// Gravity on/off mask
extern UINT SC_GRAVITY_MASK;

/***** CONSTANTS *****/
// Speed of light in m/s
extern UINT C;
// Acceptable error for collision detection
extern double ERR_COLLISION;