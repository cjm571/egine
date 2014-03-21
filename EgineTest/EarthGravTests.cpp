/*************************
* Author: CJ McAllister  *
*                        *
* Created on: 2014-03-21 *
*************************/

#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace EgineTest
{
	// Earth-gravity Tests
	TEST_CLASS(EarthGravity)
	{
	private:
		// Scene-edge Rebound helper function
		// NOTE: 
		// Bottom rebounds must be placed below Y = 100m
		// Side rebounds must be placed within 50m of vertical side
		static void SERebound(double v0, double theta0, CartPoint p0)
		{
			bool bottomRebound = true;
			// Sanity check starting point, set rebound type
			Assert::IsTrue((((p0.x  <= 50) || (p0.x >= SCENE_WIDTH-50)) && (p0.y >= 100)) ||
						   (p0.y < 100 ) && ((p0.x > 50) || (p0.x < SCENE_WIDTH-50)));
			bottomRebound = (p0.y < 100 ) && ((p0.x > 50) || (p0.x < SCENE_WIDTH-50));

			// Wrap angle around (0,2pi)
			theta0 = WrapAngle(theta0);
			
			// Reference object
			PhysicsObject refObj = PhysicsObject();
			double halfwidth = refObj.GetAABB().GetWidth()/2;

			// Create rebound object at epicenter
			PhysicsObject obj = PhysicsObject(EPICENTER);

			// Set trajectory
			Trajectory traj0 = Trajectory(v0, theta0);
			obj.SetTrajectory(traj0);

			// Calculate steps required until collision
			double dist = -1.0;
			if (bottomRebound)
			{
				dist = obj.GetAABB().GetLowerBound(Physics);
			}
			else // Side rebound
			{
				dist = min(obj.GetAABB().GetLeftBound(), SCENE_WIDTH - obj.GetAABB().GetRightBound());
			}
			double g = testScene.GetGravity();
			// TODO: Quadratic formula helper function
			

		}

	public:
		/***** TEST INIT/CLEANUP *****/
		TEST_METHOD_INITIALIZE(EarthGravInit)
		{
			testScene = Scene(SC_GRAVITY_EARTH);
		}
		
		TEST_METHOD_CLEANUP(EarthGravCleanup)
		{
			testScene = NULL;
		}
		

		/***** SCENE-BOTTOM REBOUND TESTS *****/
		TEST_METHOD(SBParallelRebound)
		{
			Assert::Fail();
		}

		/***** SCENE-SIDE REBOUND TESTS *****/
		TEST_METHOD(SSParallelRebound)
		{
			Assert::Fail();
		}

		/***** PARABOLIC ARC TESTS *****/
		TEST_METHOD(Parabola_X2)
		{
			Assert::Fail();
		}
	};
}