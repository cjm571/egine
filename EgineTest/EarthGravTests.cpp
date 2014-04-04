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
			Trajectory traj0 = Trajectory(testScene.GetGravity(), v0, theta0, obj.GetAABB().GetCenter(Physics));
			obj.SetTrajectory(traj0);

			// Add object to scene
			Assert::AreEqual(testScene.AddObject(&obj), S_OK);

			// Calculate distance until collision
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

			// Calculate steps required for collision
			std::pair<double,double> roots;
			double timeToCollision = -1.0;
			if (bottomRebound)
			{
				// Solve for positive x-intercept to get collision time 
				roots = obj.GetTrajectory().GetXIntercept(obj.GetAABB().GetLowerBound(Physics));
				timeToCollision = roots.second;
			}
			else // Side rebound
			{
				// Use nearest y-intercept for collision time
				// TODO: Fix this, it sucks. maybe pull side rebounds into separate function
				roots = obj.GetTrajectory().GetXRoots();
			}
			UINT steps = static_cast<UINT>(ceil(timeToCollision / STEP_EPSILON));

			// Step until rebound
			for (UINT i=0; i<steps; i++)
			{
				testScene.Step();
			}

			// Calculate expected post-rebound angle
			double preRBTime = timeToCollision - STEP_EPSILON;
			double preRBAngle = obj.GetTrajectory().GetTangentAngle(preRBTime);
			double expectedAngle = WrapAngle(preRBAngle * -1);

			// Assert that actual post-rebound angle within error bounds of expected
			double actualAngle = obj.GetTrajectory().GetTheta();
			double error = abs(expectedAngle - actualAngle);
			Assert::IsTrue(error <= ANGLE_ERROR);
			
			// Calculate expected post-rebound velocity
			double postRBTime = timeToCollision + STEP_EPSILON;
			double yVel = dist / (postRBTime - 0.5*g*pow(postRBTime,2));
			double expectedVel = yVel + (v0 * cos(theta0));
			double actualVel = obj.GetTrajectory().GetVelocity();
			error = abs(expectedVel - actualVel);
			Assert::IsTrue(error <= VELOCITY_ERROR);
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