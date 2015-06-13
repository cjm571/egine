/*************************
* Author: CJ McAllister  *
*                        *
* Created on: 2014-04-14 *
*************************/
#pragma once

#include <sstream>

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

// Public Statics
public:
	static ULONGLONG renderCount;

// Helper Functions
private:
    // Draw content.
    HRESULT Render();

	// Displays FPS counter
	HRESULT ShowFps();

	// Initialize physics scene
	HRESULT SceneInit();

	// Releases assets allocated by SceneInit()
	void SceneRelease();

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
	// D2D interface pointers
    HWND m_hwnd;
	Scene m_scene;
    ID2D1Factory* m_pDirect2dFactory;
    ID2D1HwndRenderTarget* m_pRenderTarget;
    ID2D1SolidColorBrush* m_pFillBrush;
    ID2D1SolidColorBrush* m_pOutlineBrush;

	// FPS data
	IDWriteFactory* m_pDWriteFactory;
	IDWriteTextFormat* m_pTextFormat;
	ID2D1SolidColorBrush* m_pFpsBgBrush;
	ID2D1SolidColorBrush* m_pFpsTextBrush;
	__int64 m_prevQPC;
	__int64 m_curQPC;
};