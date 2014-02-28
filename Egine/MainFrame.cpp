/*************************
* Author: CJ McAllister  *
*                        *
* Created on: 2014-02-07 *
*************************/

#include "MainFrame.h"

// Initialize frame width and height
UINT MainFrame::width = 640;
UINT MainFrame::height = 480;


/********** CTORS **********/
MainFrame::MainFrame() : 
    m_hwnd(NULL),
    m_pDirect2dFactory(NULL),
    m_pRenderTarget(NULL),
	m_pFillBrush(NULL)
{
}

MainFrame::~MainFrame()
{
	SafeRelease(&m_pDirect2dFactory);
    SafeRelease(&m_pRenderTarget);
	SafeRelease(&m_pFillBrush);
}


/********** ENTRY PhysPoint AND INITIALIZATION **********/
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

	if (SUCCEEDED(CoInitializeEx(NULL, COINIT_SPEED_OVER_MEMORY)))
	{
		{
			MainFrame app;

			if (SUCCEEDED(app.Initialize()))
			{
				app.RunGameLoop();
			}
		}
		CoUninitialize();
	}

	return 0;
}

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

HRESULT MainFrame::Initialize()
{
	HRESULT hr;

	// Initialize device-indpendent resources, such
    // as the Direct2D factory.
	hr = CreateDeviceIndependentResources();

	if (SUCCEEDED(hr))
	{
		// Register the window class
		WNDCLASSEX wcex		= { sizeof(WNDCLASSEX) };
		wcex.style			= CS_HREDRAW | CS_VREDRAW;
		wcex.lpfnWndProc	= MainFrame::WndProc;
		wcex.cbClsExtra		= 0;
		wcex.cbWndExtra		= sizeof(LONG_PTR);
		wcex.hInstance		= HINST_THISCOMPONENT;
		wcex.hbrBackground	= NULL;
		wcex.lpszMenuName	= NULL;
		wcex.hCursor		= LoadCursor(NULL, IDI_APPLICATION);
		wcex.lpszClassName	= L"D2DMainFrame";

		RegisterClassEx(&wcex);

		// Because the CreateWindow function takes its size in pixels,
        // obtain the system DPI and use it to scale the window size.
        FLOAT dpiX, dpiY;

		// The factory returns the current system DPI. This is also the value it will use
        // to create its own windows.
        m_pDirect2dFactory->GetDesktopDpi(&dpiX, &dpiY);

		// Determine window dimensions for desired client-size
		UINT dpiWidth = static_cast<UINT>(ceil(MainFrame::width * dpiX / 96.f));
		UINT dpiHeight = static_cast<UINT>(ceil(MainFrame::height * dpiY / 96.f));
		RECT windowRect = {0, 0, dpiWidth, dpiHeight};
		AdjustWindowRect(&windowRect, WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX, FALSE);

		// Create the window
		m_hwnd = CreateWindow(
			L"D2DMainFrame",
			L"Direct2D Physics Sandbox",
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

	return hr;
}

void MainFrame::RunGameLoop()
{
/***** TEST CODE, DROP THIS SHIT *****/
#ifdef _DEBUG
		m_scene = Scene();

		// Default object
		PhysicsObject objDefault = PhysicsObject();

		// Tall, Red, Rectangle
		PhysPoint center = PhysPoint();
		center.x = 100;
		center.y = 100;
		AABB aabb = AABB(center, 10, 30);
		D2D1::ColorF::Enum red = D2D1::ColorF::Red;
		PhysicsObject objTall = PhysicsObject(aabb, red, PhysRectangle);

		// Long, Yellow, Rectangle
		PhysPoint centerB = PhysPoint();
		centerB.x = 400;
		centerB.y = 250;
		aabb = AABB(centerB, 100, 40);
		D2D1::ColorF::Enum yellow = D2D1::ColorF::Yellow;
		PhysicsObject objLong = PhysicsObject(aabb, yellow, PhysRectangle);
		Trajectory traj = Trajectory(1.0, (M_PI/4));
		objLong.ChangeTrajectory(traj);

		m_scene.AddObject(&objDefault);
		m_scene.AddObject(&objTall);
		m_scene.AddObject(&objLong);
#endif		
/***** TEST CODE, DROP THIS SHIT *****/
	MSG msg;

	// Render initial state
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

		// Update game state
		m_scene.Step();

		// Render.. duh?
		Render();

		
	}
}


/********** D2D RESOURCES **********/
HRESULT MainFrame::CreateDeviceIndependentResources()
{
	HRESULT hr = S_OK;

	// Create a Direct2D factory
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
	
		// Create a Direct2D render target
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
}


/********** RENDER HELPER FUNCTIONS **********/
HRESULT MainFrame::RenderScene()
{
	HRESULT hr = S_OK;

	std::vector<PhysicsObject*> physicsObjects = m_scene.GetObjects();

	// Draw objects based on shape/size/etc.
	std::vector<PhysicsObject*>::iterator poItr;
	for (poItr = physicsObjects.begin(); poItr != physicsObjects.end(); ++poItr)
	{
		PhysicsObject* curObject = (*poItr);
		
		// Set brush colors
		D2D1::ColorF::Enum color = curObject->GetColor();
		hr = m_pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(color), &m_pFillBrush);
		hr |= m_pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Black), &m_pOutlineBrush);

		// Exit loop on brush-create failure
		if (FAILED(hr))
		{
			break;
		}

		// Get AABB data to determine dimensions of object
		AABB aabb = curObject->GetAABB();
		PhysPoint center = aabb.GetCenter(AABB::Drawing);
		PhysPoint tl = aabb.GetTopLeft(AABB::Drawing);
		PhysPoint br = aabb.GetBottomRight(AABB::Drawing);
		double width = aabb.GetWidth();
		double height = aabb.GetHeight();

		// Draw the damn thing
		switch (curObject->GetShape())
		{
		case PhysCircle:
			{
			D2D1_POINT_2F d2dCenter;
			d2dCenter.x = (float)center.x;
			d2dCenter.y = (float)center.y;
			D2D1_ELLIPSE circle = D2D1::Ellipse(d2dCenter, (float)(width/2), (float)(height/2));
			m_pRenderTarget->FillEllipse(&circle, m_pFillBrush);
			m_pRenderTarget->DrawEllipse(&circle, m_pOutlineBrush);
			continue;
			}
		case PhysTriangle:
			{
			continue;
			}
		case PhysRectangle:
			{
			D2D1_RECT_F rect = D2D1::RectF((float)tl.x, (float)tl.y, (float)br.x, (float)br.y);
			m_pRenderTarget->FillRectangle(&rect, m_pFillBrush);
			m_pRenderTarget->DrawRectangle(&rect, m_pOutlineBrush);
			continue;
			}
		default:
			{
			// Invalid shape
			LPCSTR errMsg = "Invalid shape for UID " + curObject->GetUID();
			MessageBoxA(NULL, errMsg, NULL, MB_OK);
			break;
			}
		}
	}

	return hr;
}


/********** EVENT HANDLERS **********/
HRESULT MainFrame::Render()
{
	HRESULT hr = S_OK;

	hr = CreateDeviceResources();

	if (SUCCEEDED(hr))
	{
		// Clear background
		m_pRenderTarget->BeginDraw();
		m_pRenderTarget->SetTransform(D2D1::Matrix3x2F::Identity());
		m_pRenderTarget->Clear(D2D1::ColorF(D2D1::ColorF::Aqua));
		
		// Render objects in physics scene
		hr = RenderScene();

		hr = m_pRenderTarget->EndDraw();
	}

	if (hr == D2DERR_RECREATE_TARGET)
    {
        hr = S_OK;
        DiscardDeviceResources();
    }

	return hr;
}