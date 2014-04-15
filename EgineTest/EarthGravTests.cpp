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
		static void Rebound(eAxis axis, double v0, double theta0, CartPoint p0)
		{
			// Wrap angle around (0,2pi)
			theta0 = WrapAngle(theta0);
			
			// Reference object
			PhysicsObject refObj = PhysicsObject();
			double halfwidth = refObj.GetAABB().GetWidth()/2;

			// Create rebound object at p0
			PhysicsObject obj = PhysicsObject(p0);

			// Set trajectory
			Trajectory traj0 = Trajectory(testScene.GetGravity(), v0, theta0, obj.GetAABB().GetCenter());
			obj.SetTrajectory(traj0);

			// Add object to scene
			Assert::AreEqual(testScene.AddObject(obj), S_OK);
			
			// Calculate steps required for collision
			double timeToCollision = testScene.CalcOOBTime(axis, obj);
			UINT steps = static_cast<UINT>(ceil(timeToCollision / STEP_EPSILON));

			// Calculate expected post-rebound angle
			double preRBAngle = WrapAngle(obj.GetTrajectory().GetTangentAngle(timeToCollision));
			double expectedAngle;
			if (axis == XAxis)
			{
				expectedAngle = WrapAngle(-1 * (preRBAngle+M_PI));
			}
			else // Y-axis
			{
				expectedAngle = WrapAngle(-1 * preRBAngle);
			}

			// Step until rebound
			for (UINT i=0; i<steps; i++)
			{
				testScene.Step();
			}

			// Assert that actual post-rebound angle is within error bounds of expected
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
		TEST_METHOD(BottomStraightRebound)
		{
			CartPoint startPoint = {100, 75};

			// Initially at-rest
			Rebound(YAxis, 0.0, 0.0, startPoint);
		}

		/***** SCENE-SIDE REBOUND TESTS *****/
		TEST_METHOD(LeftSideParallelRebound)
		{
			CartPoint startPoint = {25, 150};

			// Initially moving towards left Scene side at 5m/s
			Rebound(XAxis, 5.0, M_PI, startPoint);
		}
		
		TEST_METHOD(RightSideParallelRebound)
		{
			CartPoint startPoint = {SCENE_WIDTH-25, 150};

			// Initially moving towards right Scene side at 5m/s
			Rebound(XAxis, 5.0, 0.0, startPoint);
		}

		/***** PARABOLIC ARC TESTS *****/
		TEST_METHOD(Bottom_X2ParabolaRebound)
		{
			CartPoint startPoint = {25, 100};

			// Traces out parabola defined by f(x) = -x^2 starting at point (-1,-1)
			Quadratic _X2 = Quadratic(-1.0, 0.0, 0.0);
			double theta0 = _X2.GetTangentAngle(-1.0);

			// Initially moving along parabola at 1m/s
			Rebound(YAxis, 1.0, theta0, startPoint);
		}
	};
}