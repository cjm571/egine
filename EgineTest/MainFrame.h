/*************************
* Author: CJ McAllister  *
*                        *
* Created on: 2014-02-07 *
*************************/
#pragma once

#include "StdAfx.h"

class MainFrame
{
// Ctors
public:
	MainFrame();
	~MainFrame();

	// Register the window class and call methods for instantiating drawing resources
    HRESULT Initialize();

	// Runs the main game loop
	void RunGameLoop();
	
// Helper Functions
private:
	// Renders physics scene defined by m_scene
	HRESULT RenderScene();

	// Renders all components of the game
	HRESULT Render();

// D2D Resource Functions
private:
    // Initialize device-independent resources.
    HRESULT CreateDeviceIndependentResources();

    // Initialize device-dependent resources.
    HRESULT CreateDeviceResources();
	
    // Release device-dependent resource.
    void DiscardDeviceResources();

// Windows Callback Functions
private:
	// The windows procedure.
    static LRESULT CALLBACK WndProc(
        HWND hWnd,
        UINT message,
        WPARAM wParam,
        LPARAM lParam
        );
				
// Properties
private:
	HWND m_hwnd;
	ID2D1Factory* m_pDirect2dFactory;
	ID2D1HwndRenderTarget* m_pRenderTarget;
	ID2D1SolidColorBrush* m_pFillBrush;
	ID2D1SolidColorBrush* m_pOutlineBrush;
	Scene m_scene;
};
