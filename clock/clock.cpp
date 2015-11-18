// clock.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "clock.h"

#define MAX_LOADSTRING 100
RECT windowRect = { 300, 100, 300, 100 };

// Global Variables:
HINSTANCE hInst;								// current instance
TCHAR szTitle[MAX_LOADSTRING];					// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];			// the main window class name

// Forward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPTSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

 	// TODO: Place code here.
	MSG msg;
	HACCEL hAccelTable;

	// Initialize global strings
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_CLOCK, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_CLOCK));

	// Main message loop:
	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int) msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_CLOCK));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= NULL;
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   HWND hWnd;

   hInst = hInstance; // Store instance handle in our global variable

   hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      windowRect.left, windowRect.top, windowRect.right, windowRect.bottom, NULL, NULL, hInstance, NULL);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND	- process the application menu
//  WM_PAINT	- Paint the main window
//  WM_DESTROY	- post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	HFONT hf;
	SetTimer(hwnd, 0, 0, NULL);
	HDC hdc = NULL; //Kh?i t?o giá tr? cho HDC là NULL(chýa có g?)
	/*B?n chú ? chúng ta s? d?ng bi?n static, bi?n static là bi?n mà khi hàm k?t thúc nó c?ng không b? xoá, t?c là khi WndProc ðý?c g?i bao nhiêu l?n nó c?ng không ph?i kh?i t?o l?i giá tr? cho bi?n này*/
	static int length = 0; //ð? dài c?a d?ng ch? s? vi?t ra màn h?nh
	PAINTSTRUCT paintStruct;
	// lay thoi gian thanh chuoi
	int x, y; //T?a ð? s? in d?ng ch? ra
	/*

	char x1[10], x2[10], x3[10];
	itoa(h, x1,sizeof(x1));
	itoa(m, x2, sizeof(x2));
	itoa(s, x3, sizeof(x3));
	char sstr[100] = "  ";
	//char sstr[100] ;//D?ng ch? chúng ta s? in ra
	strcat(sstr, x1);
	strcat(sstr, " : ");
	strcat(sstr, x2);
	strcat(sstr, " : ");
	strcat(sstr, x3);
	*/
	hf = CreateFont(28,                        // nHeight
		0,                         // nWidth
		0,                         // nEscapement
		0,                         // nOrientation
		FW_NORMAL,                 // nWeight
		FALSE,                     // bItalic
		FALSE,                     // bUnderline
		0,                         // cStrikeOut
		ANSI_CHARSET,              // nCharSet
		OUT_DEFAULT_PRECIS,        // nOutPrecision
		CLIP_DEFAULT_PRECIS,       // nClipPrecision
		DEFAULT_QUALITY,           // nQuality
		DEFAULT_PITCH | FF_SWISS,  // nPitchAndFamily
		_T("Arial"));
	switch (iMsg) {

	case WM_CREATE: //Trong lúc t?o c?a s?....
		hdc = GetWindowDC(hwnd); //L?y handle device context 
//		length = strlen(sstr); //L?y ð? dài c?a d?ng ch? s? in
		ReleaseDC(hwnd, hdc); //Gi?i phóng b? nh? cho handle device context
		break;

	case WM_SIZE:        
		GetWindowRect(hwnd, &windowRect);/*Hàm này s? ði?n thông tin v? kích thý?c c?a c?a s? vào bi?n windowRect,b?n chú ? các hàm có k? t? "&" */
		break;

	case WM_TIMER:
	{
					 SYSTEMTIME time;
					 GetLocalTime(&time);
					 int h = time.wHour;
					 int m = time.wMinute;
					 int s = time.wSecond;
					 TCHAR t[100];
					 wsprintf(t, L"%d : %d : %d ", h, m, s);

					 hdc = GetDC(hwnd); //B?t ð?u v? 
					 SelectObject(hdc, hf);
					 TextOut(hdc, 60, 20, (LPCWSTR)t, 13); //Bây gi? chúng ta có th? ðýa d?ng ch? này ra màn h?nh.
					 DeleteObject(hf);
					 ReleaseDC(hwnd, hdc); //K?t thúc công vi?c v?i hdc t?i ðây, gi?i phóng b? nh?....
					 break;
	}
	case WM_PAINT:
		break;
	case WM_CLOSE:
		KillTimer(hwnd, NULL);
		DestroyWindow(hwnd);
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	return DefWindowProc(hwnd, iMsg, wParam, lParam);

}

//LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
//{
//
//	int wmId, wmEvent;
//	PAINTSTRUCT ps;
//	HDC hdc;
//
//	switch (message)
//	{
//	case WM_COMMAND:
//		wmId    = LOWORD(wParam);
//		wmEvent = HIWORD(wParam);
//		// Parse the menu selections:
//		switch (wmId)
//		{
//		case IDM_ABOUT:
//			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
//			break;
//		case IDM_EXIT:
//			DestroyWindow(hWnd);
//			break;
//		default:
//			return DefWindowProc(hWnd, message, wParam, lParam);
//		}
//		break;
//	case WM_PAINT:
//		hdc = BeginPaint(hWnd, &ps);
//		// TODO: Add any drawing code here...
//		EndPaint(hWnd, &ps);
//		break;
//	case WM_DESTROY:
//		PostQuitMessage(0);
//		break;
//	default:
//		return DefWindowProc(hWnd, message, wParam, lParam);
//	}
//	return 0;
//}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}
