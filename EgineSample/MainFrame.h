/*************************
* Author: CJ McAllister  *
*                        *
* Created on: 2014-04-14 *
*************************/
#pragma once

// Engine header
#include "..\Egine\Scene.h"

#include "StdAfx.h"

class MainFrame
{
// Ctors
public:
    MainFrame();
    ~MainFrame();

// Public Methods
public:
    // Register the window class and call methods for instantiating drawing resources
    HRESULT Initialize();

    // Process and dispatch messages
    void RunMessageLoop();

// Helper Functions
private:
    // Draw content.
    HRESULT Render();

	// Initialize physics scene
	HRESULT SceneInit();

// Direct2D Helper Functions
private:
    // Initialize device-independent resources.
    HRESULT CreateDeviceIndependentResources();

    // Initialize device-dependent resources.
    HRESULT CreateDeviceResources();

    // Release device-dependent resource.
    void DiscardDeviceResources();

// Windows Stuff
private:
    // Resize the render target.
    void OnResize(
        UINT width,
        UINT height
        );

    // The windows procedure.
    static LRESULT CALLBACK WndProc(
        HWND hWnd,
        UINT message,
        WPARAM wParam,
        LPARAM lParam
        );

private:
    HWND m_hwnd;
	Scene m_scene;
    ID2D1Factory* m_pDirect2dFactory;
    ID2D1HwndRenderTarget* m_pRenderTarget;
    ID2D1SolidColorBrush* m_pLightSlateGrayBrush;
    ID2D1SolidColorBrush* m_pCornflowerBlueBrush;
};