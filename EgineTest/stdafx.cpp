// stdafx.cpp : source file that includes just the standard includes
// EgineTest.pch will be the pre-compiled header
// stdafx.obj will contain the pre-compiled type information

#include "stdafx.h"

/*** CONSTANTS ***/
const double ALLOWABLE_ERROR = 0.1;
const CartPoint EPICENTER = {100.0, 100.0};
const PolarPoint EPICENTER_POLAR = CartToPolar(EPICENTER);
const double EPICENTER_OFFSET = 25.0;
const double DEFAULT_VELOCITY = 0.1;
const double SEPARATION_DISTANCE = 25.0;

/*** TEST SCENE OBJECT ***/
Scene testScene = NULL;