/*************************
* Author: CJ McAllister  *
*                        *
* Created on: 2014-04-14 *
*************************/

#include "MainFrame.h"

/***** CTORS *****/
MainFrame::MainFrame() :
    m_hwnd(NULL),
    m_pDirect2dFactory(NULL),
    m_pRenderTarget(NULL),
    m_pFillBrush(NULL),
    m_pOutlineBrush(NULL)
{
}

MainFrame::~MainFrame()
{
    SafeRelease(&m_pDirect2dFactory);
    SafeRelease(&m_pRenderTarget);
    SafeRelease(&m_pFillBrush);
    SafeRelease(&m_pOutlineBrush);

}


/***** PUBLIC METHODS *****/
HRESULT MainFrame::Initialize()
{
    HRESULT hr;

    // Initialize device-indpendent resources, such
    // as the Direct2D factory.
    hr = CreateDeviceIndependentResources();

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

        // Create the window.
        m_hwnd = CreateWindow(
            "D2DMainFrame",
            "Egine Sample DirectX Application",
            WS_OVERLAPPEDWINDOW,
            CW_USEDEFAULT,
            CW_USEDEFAULT,
            static_cast<UINT>(ceil(640.f * dpiX / 96.f)),
            static_cast<UINT>(ceil(480.f * dpiY / 96.f)),
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
		std::vector<PhysicsObject> objs = m_scene.GetObjects();
		std::vector<PhysicsObject>::iterator objItr;
		for (objItr=objs.begin(); objItr!=objs.end(); ++objItr)
		{
			// Initialize fill & outline brushes
			hr = m_pRenderTarget->CreateSolidColorBrush(D2D1::ColorF((*objItr).GetColor()), &m_pFillBrush);
			hr |= m_pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(Black), &m_pOutlineBrush);

			// Define rectangle for object
			D2D1_RECT_F rect = D2D1::RectF(
				(FLOAT)(*objItr).GetAABB().GetLeftBound(),
				(FLOAT)(*objItr).GetAABB().GetUpperBound(Drawing),
				(FLOAT)(*objItr).GetAABB().GetRightBound(),
				(FLOAT)(*objItr).GetAABB().GetLowerBound(Drawing)
				);

			// Fill rectangle with object color
			m_pRenderTarget->FillRectangle(&rect, m_pFillBrush);

			// Outline rectangle in black
			m_pRenderTarget->DrawRectangle(&rect, m_pOutlineBrush);
		}

		// End draw
		m_pRenderTarget->EndDraw();
    }

    if (hr == D2DERR_RECREATE_TARGET)
    {
        hr = S_OK;
        DiscardDeviceResources();
    }

    return hr;
}

HRESULT MainFrame::SceneInit()
{
	HRESULT hr = S_OK;

	// Create zero-gravity scene
	m_scene = Scene(SC_GRAVITY_OFF);

	// Create 2 default objects
	CartPoint pointA = {100,100};
	PhysicsObject objA = PhysicsObject(pointA);
	CartPoint pointB = {250,150};
	PhysicsObject objB = PhysicsObject(pointB);

	// Define their trajectories
	Trajectory trajA = Trajectory(m_scene.GetGravity(), 10.0, M_PI/6, pointA);
	Trajectory trajB = Trajectory(m_scene.GetGravity(), 20.0, 5*M_PI/3, pointB);
	hr |= objA.SetTrajectory(trajA);
	hr |= objB.SetTrajectory(trajB);

	// Make them pretty
	objA.SetColor(Red);
	objB.SetColor(Violet);

	// Add objects to the scene
	hr |= m_scene.AddObject(objA);
	hr |= m_scene.AddObject(objB);

	return hr;
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
