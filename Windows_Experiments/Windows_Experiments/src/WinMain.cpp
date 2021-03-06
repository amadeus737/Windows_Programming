#include <Windows.h>

// Forward declare windows procedure (defined below WinMain)
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

// Windows Entry Point function
// hInstance is something called a "handle to an instance" or "handle to a module." The operating system uses this value to identify the executable(EXE) when it is loaded in memory.The instance handle is needed for certain Windows functions?for example, to load icons or bitmaps.
// hPrevInstance has no meaning.It was used in 16 - bit Windows, but is now always zero.
// pCmdLine contains the command - line arguments as a Unicode string.
// nCmdShow is a flag that says whether the main application window will be minimized, maximized, or shown normally.
int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmLine, int nCmdShow)
{
	// Create windows class
	const LPCWSTR pClassName = L"chap3D";
	WNDCLASSEX wc = { 0 }; // start by zeroing it out
	wc.cbSize = sizeof(wc);			 // The size, in bytes, of this structure
	wc.style = CS_OWNDC;			 // CS_OWNDC means allocate a unique device context for each window in the class -- avoids needing to retrieve a device context each time window is painted
	wc.lpfnWndProc = WndProc;  // A pointer to the window procedure function
	wc.cbClsExtra = 0;				 // The number of extra bytes to allocate following the window-class structure
	wc.cbWndExtra = 0;				 // The number of extra bytes to allocate following the window instance
	wc.hInstance = hInstance;		 // A handle to the instance that contains the window procedure for the class
	wc.hIcon = nullptr;			     // Handle to class icon
	wc.hCursor = nullptr;			 // Handle to class cursor
	wc.hbrBackground = nullptr;		 // Set brush background to nullptr to avoid windows painting over D3D
	wc.lpszMenuName = nullptr;		 // Pointer to class menu
	wc.lpszClassName = pClassName;	 // Window clas name
	wc.hIconSm = nullptr;			 // Handle to small icon

	// Register windows class
	RegisterClassEx(&wc);

	// Create windows instance	
	HWND hWnd = CreateWindowEx(0, pClassName, L"Window Title", WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU, 200, 200, 640, 480, nullptr, nullptr, hInstance, nullptr);

	// Show the window
	ShowWindow(hWnd, SW_SHOW);

	// Message pump
	MSG msg;
	BOOL gResult;
	while ((gResult = GetMessage(&msg, nullptr, 0, 0)) > 0)
	{
		TranslateMessage(&msg);

		// Pass message back to windows 32 side
		DispatchMessage(&msg);
	}

	if (gResult == -1)
		return -1;
	else
		return msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
		case WM_CLOSE:
			PostQuitMessage(0);
			break;
	}

	return DefWindowProc(hWnd, msg, wParam, lParam);
}