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
		// Collision test
		TEST_METHOD(CollisionTest)
		{
			Scene testScene = Scene(SC_GRAVITY_OFF);
			// Default object
			PhysicsObject objDefault = PhysicsObject();
			Trajectory defTraj = Trajectory(0.1, 0.0);
			objDefault.ChangeTrajectory(defTraj);

			// Tall, Red, Rectangle
			PhysPoint center = PhysPoint();
			center.x = 100;
			center.y = 100;
			AABB aabb = AABB(center, 10, 30);
			D2D1::ColorF::Enum red = D2D1::ColorF::Red;
			PhysicsObject objTall = PhysicsObject(aabb, red, PhysRectangle);
			Trajectory tallTraj = Trajectory(0.5, (3*M_PI/4));
			objTall.ChangeTrajectory(tallTraj);

			// Long, Yellow, Rectangle
			PhysPoint centerB = PhysPoint();
			centerB.x = 400;
			centerB.y = 250;
			aabb = AABB(centerB, 100, 40);
			D2D1::ColorF::Enum yellow = D2D1::ColorF::Yellow;
			PhysicsObject objLong = PhysicsObject(aabb, yellow, PhysRectangle);
			Trajectory traj = Trajectory(1.0, (M_PI/4));
			objLong.ChangeTrajectory(traj);

			testScene.AddObject(&objDefault);
			testScene.AddObject(&objTall);
			testScene.AddObject(&objLong);
			
			Assert::IsNotNull(&testScene);
			Assert::IsNotNull(&objDefault);
			Assert::IsNotNull(&objTall);
			Assert::IsNotNull(&objLong);
		}
	};
}