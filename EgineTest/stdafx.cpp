// stdafx.cpp : source file that includes just the standard includes
// EgineTest.pch will be the pre-compiled header
// stdafx.obj will contain the pre-compiled type information

#include "stdafx.h"

/*** CONSTANTS ***/
const double ALLOWABLE_ERROR = 0.001;
const CartPoint EPICENTER = {100.0, 100.0};
const PolarPoint EPICENTER_POLAR = CartToPolar(EPICENTER);
const double EPICENTER_OFFSET = 10.0;
const double OBJECT_VELOCITY = 0.1;

/*** TEST SCENE OBJECT ***/
Scene testScene = NULL;