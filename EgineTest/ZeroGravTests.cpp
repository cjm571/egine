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
		

		/***** COLLISION TESTS *****/
		TEST_METHOD(XParallelCollision)
		{
			// Create 2 default objects, parallel on X axis
			PhysPoint centerA = {50, 100};
			PhysicsObject objA = PhysicsObject(centerA);
			PhysPoint centerB = {100, 100};
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
			double separation = abs(objA.GetAABB().GetRightBound() - objB.GetAABB().GetLeftBound());
			
			// Allowable error: 0.001m
			double error = abs(separation - 2.0);
			Assert::IsTrue(error <= ALLOWABLE_ERROR);
		}

		TEST_METHOD(YParallelCollision)
		{
			// Create 2 default objects, parallel on Y axis
			PhysPoint centerA = {100, 50};
			PhysicsObject objA = PhysicsObject(centerA);
			PhysPoint centerB = {100, 100};
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
			for (int stepsTaken=0; stepsTaken<149; stepsTaken++)
			{
				testScene.Step();
			}

			// DEBUG!!!!!!!
			testScene.Step();
			// DEBUG!!!!!!!

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
			
			// Allowable error: 0.001m
			double error = abs(separation - 2.0);
			Assert::IsTrue(error <= ALLOWABLE_ERROR);
		}
	};
}