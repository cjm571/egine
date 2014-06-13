/*************************
* Author: CJ McAllister  *
*                        *
* Created on: 2014-05-25 *
*************************/

#include "Main.h"

// Tell Catch to provide a main()
#define CATCH_CONFIG_MAIN
// Include Catch unit testing framework header
#include "../Catch/catch.hpp"

double gravTest(Scene testScene)
{
	return testScene.GetGravity();
}

TEST_CASE("No idea what I'm doing...", "[gravTest]" )
{
	Scene testScene = Scene();
	REQUIRE( gravTest(testScene) == 9.8 );
}