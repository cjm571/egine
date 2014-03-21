/*************************
* Author: CJ McAllister  *
*                        *
* Created on: 2014-03-11 *
*************************/

#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace EgineTest
{
	// 0-gravity Tests
	TEST_CLASS(ZeroGravity)
	{
	private:
		// Helper function for 'axis'-axis collisions at 'angle' collision angle (radians)
		// X-Axis angles are bound to (-pi/2,pi/2)
		// Y-Axis angles are bound to (0, pi)
		static void Collision(eAxis axis, double angle)
		{
			// Wrap angle around (0, 2pi)
			angle = WrapAngle(angle);

			// Assert valid collision angle
			if (axis == XAxis)
			{
				Assert::IsTrue(((angle > 3*M_PI/2) && (angle <= 2*M_PI)) ||
							   ((angle >= 0.0) && (angle < M_PI/2)));
			}
			if (axis == YAxis)
			{
				Assert::IsTrue((angle > 0) && (angle < M_PI));
			}

			// Create reference object
			PhysicsObject refObj = PhysicsObject();
			double halfwidth = refObj.GetAABB().GetWidth()/2;
			
			// Offset object A from epicenter along reflection of collision angle
			double reflAngle = angle + M_PI;
			double xOffset = (EPICENTER_OFFSET+halfwidth) * cos(reflAngle);
			double yOffset = (EPICENTER_OFFSET+halfwidth) * sin(reflAngle);
			CartPoint centerA = {EPICENTER.x + xOffset, EPICENTER.y + yOffset};
			PhysicsObject objA = PhysicsObject(centerA);

			// Offset object B from epicenter along collision axis
			CartPoint centerB;
			switch (axis)
			{
			case XAxis:
				centerB.x = EPICENTER.x + EPICENTER_OFFSET+halfwidth;
				centerB.y = EPICENTER.y;
				break;
			case YAxis:
				centerB.x = EPICENTER.x;
				centerB.y = EPICENTER.y + EPICENTER_OFFSET+halfwidth;
				break;
			case BothAxes:
				// TODO: revisit, hardcoded and probably wrong, needs reflected position calculated
				centerB.x = EPICENTER.x + (EPICENTER_OFFSET+halfwidth)/2;
				centerB.y = EPICENTER.y + (EPICENTER_OFFSET+halfwidth)/2;
				break;
			default: // AxisErr
				Assert::Fail();
				break;
			}
			PhysicsObject objB = PhysicsObject(centerB);
			
			// Set trajectories
			Trajectory trajA = Trajectory(DEFAULT_VELOCITY, angle);
			Trajectory trajB;
			switch (axis)
			{
			case XAxis:
				trajB = Trajectory(DEFAULT_VELOCITY, M_PI);
				break;
			case YAxis:
				trajB = Trajectory(DEFAULT_VELOCITY, 3*M_PI/2);
				break;
			case BothAxes:
				trajB = Trajectory(DEFAULT_VELOCITY, reflAngle);
				break;
			default: // AxisErr
				Assert::Fail();
				break;
			}
			objA.SetTrajectory(trajA);
			objB.SetTrajectory(trajB);

			// Add objects to Scene
			Assert::AreEqual(testScene.AddObject(&objA), S_OK);
			Assert::AreEqual(testScene.AddObject(&objB), S_OK);

			// Calculate steps required for collision
			double boundsDist = -1.0;
			double velObjA = -1.0;
			switch (axis)
			{
			case XAxis:
				boundsDist = abs((objA.GetAABB().GetRightBound()) -
								 (objB.GetAABB().GetLeftBound()));
				velObjA = abs(DEFAULT_VELOCITY * cos(objA.GetTrajectory().GetDirection()));
				break;
			case YAxis:
				boundsDist = abs((objA.GetAABB().GetUpperBound(Physics)) -
								 (objB.GetAABB().GetLowerBound(Physics)));
				velObjA = abs(DEFAULT_VELOCITY * sin(objA.GetTrajectory().GetDirection()));
				break;
			case BothAxes:
				// TODO: properly calculate corner distance, velocity
				boundsDist = 0.0;
				break;
			default: // AxisErr
				Assert::Fail();
				break;
			}
			// TODO: handle both-axes collisions
			UINT stepsTillCollision = static_cast<UINT>(ceil(boundsDist / (velObjA + DEFAULT_VELOCITY)));

			// Step scene until collision occurs
			for (UINT stepsTaken=0; stepsTaken<stepsTillCollision; stepsTaken++)
			{
				testScene.Step();
			}

			// Assert that trajectories have reversed
			double reversedA = -1.0;
			double reversedB = -1.0;
			switch (axis)
			{
			case XAxis:
				reversedA = WrapAngle((angle*-1) + M_PI);
				reversedB = 0;
				break;
			case YAxis:
				reversedA = WrapAngle(angle*-1);
				reversedB = M_PI/2;
				break;
			case BothAxes:
				reversedA = reflAngle;
				// TODO: confirm correctness of reversedB
				reversedB = angle;
			default: // AxisErr
				Assert::Fail();
				break;
			}
			Assert::AreEqual(reversedA, objA.GetTrajectory().GetDirection());
			Assert::AreEqual(reversedB, objB.GetTrajectory().GetDirection());
		}

	public:
		/***** TEST INIT/CLEANUP *****/
		TEST_METHOD_INITIALIZE(ZeroGravInit)
		{
			testScene = Scene(SC_GRAVITY_OFF);
		}
		
		TEST_METHOD_CLEANUP(ZeroGravCleanup)
		{
			testScene = NULL;
		}
		

		/***** X-AXIS COLLISION TESTS *****/
		TEST_METHOD(X60DegCollision)
		{
			Collision(XAxis, M_PI/6);
		}
		
		TEST_METHOD(X45DegCollision)
		{
			Collision(XAxis, M_PI/4);
		}
		
		TEST_METHOD(X30DegCollision)
		{
			Collision(XAxis, M_PI/3);
		}

		TEST_METHOD(X0DegCollision)
		{			
			Collision(XAxis, 0);
		}

		TEST_METHOD(X330DegCollision)
		{
			Collision(XAxis, 11*M_PI/6);
		}
		
		TEST_METHOD(X315DegCollision)
		{
			Collision(XAxis, 7*M_PI/4);
		}
		
		TEST_METHOD(X300DegCollision)
		{
			Collision(XAxis, 5*M_PI/3);
		}
		
		/***** Y-AXIS COLLISION TESTS *****/
		TEST_METHOD(Y30DegCollision)
		{
			Collision(YAxis, M_PI/6);
		}
		
		TEST_METHOD(Y45DegCollision)
		{
			Collision(YAxis, M_PI/4);
		}
		
		TEST_METHOD(Y60DegCollision)
		{
			Collision(YAxis, M_PI/3);
		}

		TEST_METHOD(Y90DegCollision)
		{
			Collision(YAxis, M_PI/2);
		}

		TEST_METHOD(Y120DegCollision)
		{
			Collision(YAxis, 2*M_PI/3);
		}
		
		TEST_METHOD(Y135DegCollision)
		{
			Collision(YAxis, 3*M_PI/4);
		}
		
		TEST_METHOD(Y150DegCollision)
		{
			Collision(YAxis, 5*M_PI/6);
		}
	};
}