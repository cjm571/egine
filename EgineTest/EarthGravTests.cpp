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
			Trajectory traj0 = Trajectory(testScene.GetGravity(), v0, theta0, obj.GetAABB().GetCenter());
			obj.SetTrajectory(traj0);

			// Add object to scene
			Assert::AreEqual(testScene.AddObject(&obj), S_OK);

			// Calculate distance until collision
			double dist = -1.0;
			if (bottomRebound)
			{
				dist = obj.GetAABB().GetLowerBound();
			}
			else // Side rebound
			{
				dist = min(obj.GetAABB().GetLeftBound(), SCENE_WIDTH - obj.GetAABB().GetRightBound());
			}
			double g = testScene.GetGravity();

			// Calculate steps required for collision
			std::pair<double,double> roots;
			double timeToCollision = -1.0;
			if (bottomRebound)
			{
				/*
				// Solve for positive x-intercept to get collision time
				roots = obj.GetTrajectory().CalcXIntercepts(obj.GetAABB().GetLowerBound());
				timeToCollision = roots.second;
				*/

				timeToCollision = testScene.CalcOOBTime(YAxis, obj);
			}
			else // Side rebound
			{
				// Use nearest y-intercept for collision time
				// TODO: Fix this, it sucks. maybe pull side rebounds into separate function
				roots = obj.GetTrajectory().GetXRoots();
			}
			UINT steps = static_cast<UINT>(ceil(timeToCollision / STEP_EPSILON));

			// Calculate expected post-rebound angle
			double preRBAngle = obj.GetTrajectory().GetTangentAngle(timeToCollision);
			double expectedAngle = WrapAngle(preRBAngle * -1);

			// Step until rebound
			for (UINT i=0; i<steps; i++)
			{
				testScene.Step();
			}

			// Assert that actual post-rebound angle within error bounds of expected
			double curTime = testScene.GetElapsedTime();
			double actualAngle = obj.GetTrajectory().GetTheta(curTime);
			double error = abs(expectedAngle - actualAngle);
			Assert::IsTrue(error <= ANGLE_ERROR);
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
			CartPoint cPoint = {100, 75};
			SERebound(0.0, 0.0, cPoint);
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