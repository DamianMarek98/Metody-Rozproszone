#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

const char Name[] = "Window";

#define NUMBER "Number of files:"
#define TEXT "  text: "
#define BITMAP ",  bitmap: "

#define SIZE_OF_COUNTER 10

PASCAL


WndProc(HWND hwnd, WORD message, WORD wParam, LONG lParam)
{

	static HWND hwndNxtVwr;
	static int globalTextClipboardCounter;
	static int globalBitmapClipboardCounter;

	HDC hdc;
	PAINTSTRUCT ps;
	RECT rect;

	switch (message)
	{
	case WM_CREATE:
		hwndNxtVwr = SetClipboardViewer(hwnd);

		globalTextClipboardCounter = 0;
		globalBitmapClipboardCounter = 0;

		return 0;
	case WM_DRAWCLIPBOARD:
		if (hwndNxtVwr != NULL)
		{
			SendMessage(hwndNxtVwr, message, wParam, lParam);
		}

		
		if (IsClipboardFormatAvailable(CF_BITMAP)) //when bitmap copied counter ++
		{
			globalBitmapClipboardCounter++;
		}

		InvalidateRect(hwnd, NULL, TRUE);
		return 0;
	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);
		GetClientRect(hwnd, &rect);

		Rectangle(hdc, -1, -1, 360, 260); //-1 to hide frame

		char buffer[SIZE_OF_COUNTER];
		char text[200] = "";

		strcat_s(text, 180, NUMBER);
		strcat_s(text, 180, TEXT);
		_itoa_s(globalTextClipboardCounter, buffer, SIZE_OF_COUNTER, SIZE_OF_COUNTER);
		strcat_s(text, 180, buffer);
		strcat_s(text, 180, BITMAP);
		_itoa_s(globalBitmapClipboardCounter, buffer, SIZE_OF_COUNTER, SIZE_OF_COUNTER);
		strcat_s(text, 180, buffer);
		
		DrawText(hdc,text,-1,&rect,DT_CENTER | DT_VCENTER);

		if (IsClipboardFormatAvailable(CF_TEXT))
		{
			globalTextClipboardCounter++;

			OpenClipboard(hwnd);

			char* hCbMem = GetClipboardData(CF_TEXT);
			char* hProgMem = GlobalAlloc(GHND, GlobalSize(hCbMem));
			char* lpCbMem = GlobalLock(hCbMem);
			char* lpProgMem = GlobalLock(hProgMem);

			lstrcpy(lpProgMem, lpCbMem);

			GlobalUnlock(hCbMem);
			GlobalUnlock(hProgMem);

			CloseClipboard();

			lpProgMem[strlen(hCbMem)] = '\0';

			DrawText(hdc,lpProgMem,-1,&rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER
			);
		}
		else
		{
			DrawText(hdc,"No text in clipboard.",-1,&rect,DT_SINGLELINE | DT_CENTER | DT_VCENTER);
		}

		EndPaint(hwnd, &ps);
		return 0;
	case WM_CHANGECBCHAIN:
		if (wParam == hwndNxtVwr)
		{
			hwndNxtVwr = LOWORD(lParam);
		}
		else
		{
			if (hwndNxtVwr != NULL)
			{
				SendMessage(hwndNxtVwr, message, wParam, lParam);
			}
		}

		return 0;
	case WM_DESTROY:
		ChangeClipboardChain(hwnd, hwndNxtVwr);
		PostQuitMessage(0);
		return 0;
	default:
		return DefWindowProc(hwnd, message, wParam, lParam);
	}

	return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,LPSTR lpCmdLine, int nCmdShow)
{
	WNDCLASSEX wc;
	HWND hwnd;
	MSG msg;

	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = 0;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 2);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = Name;
	wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

	if (!RegisterClassEx(&wc))
	{
		MessageBox(NULL, "Failed to create a window!", "Error!",
			MB_ICONEXCLAMATION | MB_OK);
		return 0;
	}

	hwnd = CreateWindowEx(
		WS_EX_CLIENTEDGE,
		Name,
		"Przetwarzanie rozproszone lab5",
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		360,
		260,
		NULL,
		NULL,
		hInstance,
		NULL
	);

	if (hwnd == NULL)
	{
		MessageBox(NULL, "Window Creation Failed!", "Error!",
			MB_ICONEXCLAMATION | MB_OK);
		return 0;
	}

	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);

	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}