/*************************
* Author: CJ McAllister  *
*                        *
* Created on: 2014-05-25 *
*************************/

#include "Main.h"

using namespace std;
int main()
{
	TestStub testStub = TestStub();
	Scene testScene = Scene();
	
	cout << "Hello egine" << endl;
	
	double grav = testScene.GetGravity();
	
	cout << "Gravity: " << grav << endl;
	
	return 0;
}

