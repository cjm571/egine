/*************************
* Author: CJ McAllister  *
*                        *
* Created on: 2014-02-13 *
*************************/

#include "MainFrame.h"
#include "Scene.h"

/********** CTORS **********/
Scene::Scene(int _width, int _height)
{
	width = _width;
	height = _height;
}

Scene::~Scene()
{
	while(!physicsObjects.empty())
	{
		delete physicsObjects.back();
		physicsObjects.pop_back();
	}

	physicsObjects.clear();
	delete &physicsObjects;
}


/********** PUBLIC METHODS **********/
HRESULT Scene::AddObject(PhysicsObject* newObject)
{
	HRESULT hr = S_OK;

	// Sanity check new physics object properties, add to list on pass
	Point aabbMin = newObject->getAABB().getMin();
	Point aabbMax = newObject->getAABB().getMax();

	// Out-of-bounds check
	if (aabbMin.x < 0 || aabbMin.y < 0 ||
		aabbMax.x > MainFrame::width || aabbMax.y > MainFrame::height)
	{
		hr = E_FAIL;
	}

	if (SUCCEEDED(hr))
	{
		//TODO: Left off here
	}


	// AABB overlap check

	physicsObjects.push_back(newObject);
}
