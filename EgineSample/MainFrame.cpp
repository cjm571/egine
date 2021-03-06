/*************************
* Author: CJ McAllister  *
*                        *
* Created on: 2014-04-14 *
*************************/

#include "MainFrame.h"

ULONGLONG MainFrame::renderCount = 0;

/***** CTORS *****/
MainFrame::MainFrame() :
	m_hwnd(NULL),
	m_pDirect2dFactory(NULL),
	m_pRenderTarget(NULL),
	m_pFillBrush(NULL),
	m_pOutlineBrush(NULL),
	m_pDWriteFactory(NULL),
	m_pTextFormat(NULL),
	m_pFpsBgBrush(NULL),
	m_pFpsTextBrush(NULL),
	m_prevQPC(0),
	m_curQPC(0)
{
}

MainFrame::~MainFrame()
{
    SafeRelease(&m_pDirect2dFactory);
    SafeRelease(&m_pRenderTarget);
    SafeRelease(&m_pFillBrush);
    SafeRelease(&m_pOutlineBrush);
	SafeRelease(&m_pDWriteFactory);
	SafeRelease(&m_pTextFormat);
	SafeRelease(&m_pFpsBgBrush);
	SafeRelease(&m_pFpsTextBrush);
	
	SceneRelease();
}


/***** PUBLIC METHODS *****/
HRESULT MainFrame::Initialize()
{
    HRESULT hr;

    // Initialize device-indpendent resources, such
    // as the Direct2D factory.
    hr = CreateDeviceIndependentResources();

	// Initialize FPS counter members
	if (SUCCEEDED(hr))
	{
		hr |= DWriteCreateFactory(
			DWRITE_FACTORY_TYPE_SHARED,
			__uuidof(IDWriteFactory),
			reinterpret_cast<IUnknown**>(&m_pDWriteFactory)
			);
		hr |= StartCounter();
		hr |= QueryPerformanceCounter((LARGE_INTEGER *)&m_prevQPC) ? S_OK : E_FAIL;
	}

    if (SUCCEEDED(hr))
    {
        // Register the window class.
        WNDCLASSEX wcex = { sizeof(WNDCLASSEX) };
        wcex.style         = CS_HREDRAW | CS_VREDRAW;
        wcex.lpfnWndProc   = MainFrame::WndProc;
        wcex.cbClsExtra    = 0;
        wcex.cbWndExtra    = sizeof(LONG_PTR);
        wcex.hInstance     = HINST_THISCOMPONENT;
        wcex.hbrBackground = NULL;
        wcex.lpszMenuName  = NULL;
        wcex.hCursor       = LoadCursor(NULL, IDI_APPLICATION);
        wcex.lpszClassName = "D2DMainFrame";

        RegisterClassEx(&wcex);


        // Because the CreateWindow function takes its size in pixels,
        // obtain the system DPI and use it to scale the window size.
        FLOAT dpiX, dpiY;

        // The factory returns the current system DPI. This is also the value it will use
        // to create its own windows.
        m_pDirect2dFactory->GetDesktopDpi(&dpiX, &dpiY);

		// Determine window dimensions for desired client-size
		UINT dpiWidth = static_cast<UINT>(ceil(SCENE_WIDTH * dpiX / 96.f));
		UINT dpiHeight = static_cast<UINT>(ceil(SCENE_HEIGHT * dpiY / 96.f));
		RECT windowRect = {0, 0, dpiWidth, dpiHeight};
		AdjustWindowRect(&windowRect, WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX, FALSE);

		// Create the window
		m_hwnd = CreateWindow(
			"D2DMainFrame",
            "Egine Sample DirectX Application",
			WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			windowRect.right - windowRect.left,
			windowRect.bottom - windowRect.top,
			NULL,
			NULL,
			HINST_THISCOMPONENT,
			this
			);
		hr = m_hwnd ? S_OK : E_FAIL;
		if (SUCCEEDED(hr))
		{
			ShowWindow(m_hwnd, SW_SHOWNORMAL);
			UpdateWindow(m_hwnd);
		}
    }

	// Initialize Scene
	if (SUCCEEDED(hr))
	{
		hr |= SceneInit();
	}

    return hr;
}

void MainFrame::RunMessageLoop()
{
    MSG msg;
	
	// Render original scene
	Render();
	
	// Run until main window is closed
	while (IsWindow(m_hwnd))
	{
		// Check for messages w/o blocking
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		// Update scene
		m_scene.Step();

		// Uh.. render the scene
		Render();
	}
}


/***** HELPER FUNCTIONS *****/
HRESULT MainFrame::Render()
{
    HRESULT hr = S_OK;

    hr = CreateDeviceResources();

    if (SUCCEEDED(hr))
    {
        m_pRenderTarget->BeginDraw();

        m_pRenderTarget->SetTransform(D2D1::Matrix3x2F::Identity());

        m_pRenderTarget->Clear(D2D1::ColorF(D2D1::ColorF::Cyan));

		// Get render area dimensions
        D2D1_SIZE_F rtSize = m_pRenderTarget->GetSize();
        int width = static_cast<int>(rtSize.width);
        int height = static_cast<int>(rtSize.height);

		// Get objects in Scene and render according to their properties
		std::vector<PhysicsObject*> objs = m_scene.GetObjects();
		std::vector<PhysicsObject*>::iterator objItr;
		for (objItr=objs.begin(); objItr!=objs.end(); ++objItr)
		{
			// Initialize fill & outline brushes
			hr = m_pRenderTarget->CreateSolidColorBrush(D2D1::ColorF((*objItr)->GetColor()), &m_pFillBrush);
			hr |= m_pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(Black), &m_pOutlineBrush);

			// Define rectangle for object
			D2D1_RECT_F rect = D2D1::RectF(
				(FLOAT)(*objItr)->GetAABB().GetLeftBound(),
				(FLOAT)(*objItr)->GetAABB().GetUpperBound(Drawing),
				(FLOAT)(*objItr)->GetAABB().GetRightBound(),
				(FLOAT)(*objItr)->GetAABB().GetLowerBound(Drawing)
				);

			// Fill rectangle with object color
			m_pRenderTarget->FillRectangle(&rect, m_pFillBrush);

			// Outline rectangle in black
			m_pRenderTarget->DrawRectangle(&rect, m_pOutlineBrush);
		}

		// Draw FPS counter
		ShowFps();

		// End draw
		m_pRenderTarget->EndDraw();
    }

    if (hr == D2DERR_RECREATE_TARGET)
    {
        hr = S_OK;
        DiscardDeviceResources();
    }

	renderCount++;
    return hr;
}

HRESULT MainFrame::ShowFps()
{
	HRESULT hr = S_OK;

	// Get current QPC FIRST
	hr |= QueryPerformanceCounter((LARGE_INTEGER *)&m_curQPC) ? S_OK : E_FAIL;

	const UINT RESOLUTION = 5;
	double sTimeDiff; // in seconds
	double fps;
	std::ostringstream strs;
	std::string strFps;
	LPWSTR wStrFps = new wchar_t[RESOLUTION+1];

	__int64 countDiff = m_curQPC - m_prevQPC;
	sTimeDiff = (countDiff * 1.0) / PCFreq;

	fps = 1.0 / sTimeDiff;
	strs << fps;
	strFps = strs.str().substr(0, RESOLUTION); // only care about a few decimal places, ignore the rest
	MultiByteToWideChar(CP_UTF8, NULL, strFps.c_str(), RESOLUTION, wStrFps, RESOLUTION+1);

	// Draw black rectangle background
	D2D1_RECT_F fpsRect = D2D1::RectF(
		0.0f,
		0.0f,
		30.0f,
		16.0f
		);
	if SUCCEEDED(hr)
	{
		hr = m_pRenderTarget->CreateSolidColorBrush(
			D2D1::ColorF(D2D1::ColorF::Black, 1.0f),
			&m_pFpsBgBrush
			);
	}
	if SUCCEEDED(hr)
	{
		m_pRenderTarget->FillRectangle(
			fpsRect,
			m_pFpsBgBrush
			);
	}

	// FINALLY draw the goddamned FPS
	if SUCCEEDED(hr)
	{
		hr = m_pDWriteFactory->CreateTextFormat(
			L"Courier",
			NULL,
			DWRITE_FONT_WEIGHT_REGULAR,
			DWRITE_FONT_STYLE_NORMAL,
			DWRITE_FONT_STRETCH_NORMAL,
			12.0f,
			L"en-us",
			&m_pTextFormat
			);
	}
	if SUCCEEDED(hr)
	{
		hr = m_pRenderTarget->CreateSolidColorBrush(
			D2D1::ColorF(D2D1::ColorF::Yellow, 1.0f),
			&m_pFpsTextBrush
			);
	}
	if SUCCEEDED(hr)
	{
		m_pRenderTarget->DrawTextA(
			wStrFps,
			RESOLUTION,
			m_pTextFormat,
			fpsRect,
			m_pFpsTextBrush
			);
	}

	delete[] wStrFps;

	// Reset prevTick
	hr |= QueryPerformanceCounter((LARGE_INTEGER *)&m_prevQPC) ? S_OK : E_FAIL;
	return hr;
}

HRESULT MainFrame::SceneInit()
{
	HRESULT hr = S_OK;

	// Create Earth-gravity scene
	m_scene = Scene(GravityFlag::Earth | LogModeFlag::StdOut);

	// Create 2 default objects
	CartPoint pointA = {100,250};
	PhysicsObject* objA = new PhysicsObject(pointA);
	CartPoint pointB = {250,150};
	PhysicsObject* objB = new PhysicsObject(pointB);

	// Define their trajectories
	Trajectory trajA = Trajectory(m_scene.GetGravity(), 0.0, 0.0, pointA, TIME_SIM_START);
	Trajectory trajB = Trajectory(m_scene.GetGravity(), 20.0, 5*M_PI/3, pointB, TIME_SIM_START);
	hr |= objA->SetTrajectory(trajA);
	hr |= objB->SetTrajectory(trajB);

	// Make them pretty
	objA->SetColor(Red);
	objB->SetColor(Violet);

	// Add objects to the scene
	hr |= m_scene.AddObject(objA);
	hr |= m_scene.AddObject(objB);

	return hr;
}

void  MainFrame::SceneRelease()
{
	std::vector<PhysicsObject*> objs = m_scene.GetObjects();
	std::vector<PhysicsObject*>::iterator objItr;

	for (objItr=objs.begin(); objItr!=objs.end(); ++objItr)
	{
		delete &(*objItr);
	}
}

/***** D2D FUNCTIONS *****/
HRESULT MainFrame::CreateDeviceIndependentResources()
{
    HRESULT hr = S_OK;

    // Create a Direct2D factory.
    hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &m_pDirect2dFactory);

    return hr;
}

HRESULT MainFrame::CreateDeviceResources()
{
    HRESULT hr = S_OK;

    if (!m_pRenderTarget)
    {
        RECT rc;
        GetClientRect(m_hwnd, &rc);

        D2D1_SIZE_U size = D2D1::SizeU(
            rc.right - rc.left,
            rc.bottom - rc.top
            );

        // Create a Direct2D render target.
        hr = m_pDirect2dFactory->CreateHwndRenderTarget(
            D2D1::RenderTargetProperties(),
            D2D1::HwndRenderTargetProperties(m_hwnd, size),
            &m_pRenderTarget
            );
    }

    return hr;
}

void MainFrame::DiscardDeviceResources()
{
    SafeRelease(&m_pRenderTarget);
    SafeRelease(&m_pFillBrush);
    SafeRelease(&m_pOutlineBrush);
}


/***** WINDOWS STUFF *****/
LRESULT CALLBACK MainFrame::WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    LRESULT result = 0;

    if (message == WM_CREATE)
    {
        LPCREATESTRUCT pcs = (LPCREATESTRUCT)lParam;
        MainFrame *pMainFrame = (MainFrame *)pcs->lpCreateParams;

        ::SetWindowLongPtrW(
            hwnd,
            GWLP_USERDATA,
            PtrToUlong(pMainFrame)
            );

        result = 1;
    }
    else
    {
        MainFrame *pMainFrame = reinterpret_cast<MainFrame *>(static_cast<LONG_PTR>(
            ::GetWindowLongPtrW(
                hwnd,
                GWLP_USERDATA
                )));

        bool wasHandled = false;

        if (pMainFrame)
        {
            switch (message)
            {
            case WM_SIZE:
                {
                    UINT width = LOWORD(lParam);
                    UINT height = HIWORD(lParam);
                    pMainFrame->OnResize(width, height);
                }
                result = 0;
                wasHandled = true;
                break;

            case WM_DISPLAYCHANGE:
                {
                    InvalidateRect(hwnd, NULL, FALSE);
                }
                result = 0;
                wasHandled = true;
                break;

            case WM_PAINT:
                {
                    pMainFrame->Render();
                    ValidateRect(hwnd, NULL);
                }
                result = 0;
                wasHandled = true;
                break;

            case WM_DESTROY:
                {
                    PostQuitMessage(0);
                }
                result = 1;
                wasHandled = true;
                break;
            }
        }

        if (!wasHandled)
        {
            result = DefWindowProc(hwnd, message, wParam, lParam);
        }
    }

    return result;
}

void MainFrame::OnResize(UINT width, UINT height)
{
    if (m_pRenderTarget)
    {
        // Note: This method can fail, but it's okay to ignore the
        // error here, because the error will be returned again
        // the next time EndDraw is called.
        m_pRenderTarget->Resize(D2D1::SizeU(width, height));
    }
}

// Provides the application entry point.
int WINAPI WinMain(
    HINSTANCE /* hInstance */,
    HINSTANCE /* hPrevInstance */,
    LPSTR /* lpCmdLine */,
    int /* nCmdShow */
    )
{
    // Use HeapSetInformation to specify that the process should
    // terminate if the heap manager detects an error in any heap used
    // by the process.
    // The return value is ignored, because we want to continue running in the
    // unlikely event that HeapSetInformation fails.
    HeapSetInformation(NULL, HeapEnableTerminationOnCorruption, NULL, 0);

    if (SUCCEEDED(CoInitialize(NULL)))
    {
        {
            MainFrame app;

            if (SUCCEEDED(app.Initialize()))
            {
                app.RunMessageLoop();
            }
        }
        CoUninitialize();
    }

    return 0;
}
