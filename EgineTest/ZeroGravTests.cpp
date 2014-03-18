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
		// Helper function for X-axis collisions at 'angle' collision angle (radians)
		static void XCollision(double angle)
		{
			// Create 2 default objects
			PhysicsObject objA = PhysicsObject();
			PhysicsObject objB = PhysicsObject();
			// Offset object A from epicenter along X-axis
			double halfwidth = objA.GetAABB().GetWidth()/2;
			CartPoint centerA = {EPICENTER.x + EPICENTER_OFFSET+halfwidth, EPICENTER.y};
			objA.GetAABB().SetCenter(centerA);

			// Offset object B from epicenter along 0rad-reflection of collision angle
			double reflAngle = angle + M_PI;
			double xOffset = (EPICENTER_OFFSET+halfwidth) * cos(reflAngle);
			double yOffset = (EPICENTER_OFFSET+halfwidth) * sin(reflAngle);
			CartPoint centerB = {EPICENTER.x + xOffset, EPICENTER.y + yOffset};
			objB.GetAABB().SetCenter(centerB);

			// Set trajectories
			Trajectory trajA = Trajectory(OBJECT_VELOCITY, M_PI);
			Trajectory trajB = Trajectory(OBJECT_VELOCITY, angle);
			objA.SetTrajectory(trajA);
			objB.SetTrajectory(trajB);

			// Add objects to Scene
			testScene.AddObject(&objA);
			testScene.AddObject(&objB);

			// TODO: Pick up here, calculate steps until collision
			// Step scene until collision occurs
			for (int stepsTaken=0; stepsTaken<150; stepsTaken++)
			{
				testScene.Step();
			}

			// Assert that trajectories have reversed
			double reversedA = M_PI;
			double reversedB = 0;
			Assert::AreEqual(objA.GetTrajectory().GetDirection(), reversedA);
			Assert::AreEqual(objB.GetTrajectory().GetDirection(), reversedB); 

			// Step 10 more times, check object centerpoints
			for (int stepsTaken=0; stepsTaken<9; stepsTaken++)
			{
				testScene.Step();
			}

			// Object bounds should be 2m apart
			double separation = abs(objA.GetAABB().GetRightBound() -
									objB.GetAABB().GetLeftBound());
			
			// Check if object separation is within error bounds
			double error = abs(separation - 2.0);
			Assert::IsTrue(error <= ALLOWABLE_ERROR);
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
			Assert::IsTrue(false);
		}
		
		TEST_METHOD(X45DegCollision)
		{
			Assert::IsTrue(false);
		}
		
		TEST_METHOD(X30DegCollision)
		{
			Assert::IsTrue(false);
		}

		TEST_METHOD(X0DegCollision)
		{
			// Create 2 default objects, parallel on X axis
			CartPoint centerA = {50, 100};
			PhysicsObject objA = PhysicsObject(centerA);
			CartPoint centerB = {100, 100};
			PhysicsObject objB = PhysicsObject(centerB);

			// Set 0.1m/s trajectories toward each other
			Trajectory trajA = Trajectory(0.1, 0.0);
			Trajectory trajB = Trajectory(0.1, M_PI);
			objA.SetTrajectory(trajA);
			objB.SetTrajectory(trajB);

			// Add objects to Scene
			testScene.AddObject(&objA);
			testScene.AddObject(&objB);

			// Step scene until collision occurs
			// At 0.1m/s, objects should collide in 150 steps
			for (int stepsTaken=0; stepsTaken<150; stepsTaken++)
			{
				testScene.Step();
			}

			// Assert that trajectories have reversed
			double reversedA = M_PI;
			double reversedB = 0;
			Assert::AreEqual(objA.GetTrajectory().GetDirection(), reversedA);
			Assert::AreEqual(objB.GetTrajectory().GetDirection(), reversedB); 

			// Step 10 more times, check object centerpoints
			for (int stepsTaken=0; stepsTaken<9; stepsTaken++)
			{
				testScene.Step();
			}

			// Object bounds should be 2m apart
			double separation = abs(objA.GetAABB().GetRightBound() -
									objB.GetAABB().GetLeftBound());
			
			// Check if object separation is within error bounds
			double error = abs(separation - 2.0);
			Assert::IsTrue(error <= ALLOWABLE_ERROR);
		}

		TEST_METHOD(X330DegCollision)
		{
			Assert::IsTrue(false);
		}
		
		TEST_METHOD(X315DegCollision)
		{
			Assert::IsTrue(false);
		}
		
		TEST_METHOD(X300DegCollision)
		{
			Assert::IsTrue(false);
		}
		
		/***** Y-AXIS COLLISION TESTS *****/
		TEST_METHOD(Y90DegCollision)
		{
			// Create 2 default objects, parallel on Y axis
			CartPoint centerA = {100, 50};
			PhysicsObject objA = PhysicsObject(centerA);
			CartPoint centerB = {100, 100};
			PhysicsObject objB = PhysicsObject(centerB);

			// Set 0.1m/s trajectories toward each other
			Trajectory trajA = Trajectory(0.1, M_PI/2);
			Trajectory trajB = Trajectory(0.1, 3*M_PI/2);
			objA.SetTrajectory(trajA);
			objB.SetTrajectory(trajB);

			// Add objects to Scene
			testScene.AddObject(&objA);
			testScene.AddObject(&objB);

			// Step scene until collision occurs
			// At 0.1m/s, objects should collide in 150 steps
			for (int stepsTaken=0; stepsTaken<150; stepsTaken++)
			{
				testScene.Step();
			}

			// Assert that trajectories have reversed
			double reversedA = 3*M_PI/2;
			double reversedB = M_PI/2;
			Assert::AreEqual(objA.GetTrajectory().GetDirection(), reversedA);
			Assert::AreEqual(objB.GetTrajectory().GetDirection(), reversedB); 

			// Step 10 more times, check object centerpoints
			for (int stepsTaken=0; stepsTaken<9; stepsTaken++)
			{
				testScene.Step();
			}

			// Object bounds should be 2m apart
			double separation = abs(objA.GetAABB().GetUpperBound(AABB::Physics) -
									objB.GetAABB().GetLowerBound(AABB::Physics));
			
			// Check if object separation is within error bounds
			double error = abs(separation - 2.0);
			Assert::IsTrue(error <= ALLOWABLE_ERROR);
		}
		
		TEST_METHOD(Y120DegCollision)
		{
			Assert::IsTrue(false);
		}
		
		TEST_METHOD(Y135DegCollision)
		{
			Assert::IsTrue(false);
		}
		
		TEST_METHOD(Y150DegCollision)
		{
			Assert::IsTrue(false);
		}

		TEST_METHOD(Y210DegCollision)
		{
			Assert::IsTrue(false);
		}
		
		TEST_METHOD(Y225DegCollision)
		{
			Assert::IsTrue(false);
		}
		
		TEST_METHOD(Y240DegCollision)
		{
			Assert::IsTrue(false);
		}
	};
}