

#define IDB_LINE 102
#define IDB_PEN 105
#define IDB_POLYLINE 106
#define IDB_RECT 107
#define IDB_ELLIPSE 108
#define IDB_CLEAR 109
#define IDB_BEZIER 112
#define IDC_WEIGHT 114
#define IDB_OK 115
#define IDB_RED 116
#define IDB_GREEN 117
#define IDB_BLUE 118
#define IDB_BLACK 119


#include <tchar.h>
#include <windows.h>
#include <windowsx.h>
#include <string.h>
#include <iostream>
#include <stdio.h>
#include "header.h"

/*  Declaration of Window procedure  */
LRESULT CALLBACK WindowProcedure(HWND, UINT, WPARAM, LPARAM);
HINSTANCE hInst;

/*  Declare the class name into a global variable  */
TCHAR szClassName[] = ("CodeBlocksWindowsApp");

int WINAPI WinMain(HINSTANCE hThisInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpszArgument,
	int nCmdShow)
{
	HWND hwnd;
	MSG mssgs;
	WNDCLASSEX windowclass;
	hInst = hThisInstance;


	windowclass.hInstance = hThisInstance;
	windowclass.lpszClassName = szClassName;
	windowclass.lpfnWndProc = WindowProcedure;
	windowclass.style = CS_DBLCLKS | CS_HREDRAW | CS_VREDRAW;
	windowclass.cbSize = sizeof(WNDCLASSEX);

	/* Use default icon and mouse-pointer */
	windowclass.hIcon = 0;
	windowclass.hIconSm = 0;
	windowclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	windowclass.lpszMenuName = 0;
	windowclass.cbClsExtra = 0;
	windowclass.cbWndExtra = 0;
	windowclass.hbrBackground = CreateSolidBrush(RGB(242, 242, 242));

	/* Window registration. If it fails return 0 */
	if (!RegisterClassEx(&windowclass))
		return 0;

	/* Window creation*/
	hwnd = CreateWindowEx(
		0,
		szClassName,
		("Lab 3"),
		WS_OVERLAPPEDWINDOW,
		440,
		140,
		620,
		413,
		HWND_DESKTOP,
		NULL,
		hThisInstance,
		NULL
	);

	/* Make the window visible */
	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);

	/* mssg loop - runs until a 0 is in the queue */
	while (GetMessage(&mssgs, NULL, 0, 0))
	{
		TranslateMessage(&mssgs);
		DispatchMessage(&mssgs);
	}

	/* The program return-value = 0 */
	return mssgs.wParam;
}


/*  This function is called by the Windows function Dispatchmssg()  */

LRESULT CALLBACK WindowProcedure(HWND hwnd, UINT mssg, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;


	PAINTSTRUCT ps;
	RECT rect = { 140, 0, 600, 300 };
	HPEN hpen;
	/* Declaration of an HPEN object, used as a "pen" element */
	static HWND line, pen, rectangle, ellipse,
		clear, bezier, weight, okButton,
		colorButton;
	HWND tools[] = { pen, line, rectangle, ellipse,
		clear, bezier, };
	static BOOL isDrawing = FALSE;
	static int xFirst, yFirst, xLast, yLast;
	static int mouse_x, mouse_y;
	char textStore[50];
	POINT bez[4] = { { 290, 100 },{ 299, 102 },{ 310, 67 },{ 200, 40 } };           /* The bezier coordinates */
	static bool bezierBool = false;
	static int weightStatic = 4;
	HINSTANCE hInstance = (HINSTANCE)GetWindowLong(hwnd, GWLP_HINSTANCE);


	mouse_x = LOWORD(lParam);
	mouse_y = HIWORD(lParam);
	COLORREF color = RGB(0, 0, 0);
	HBRUSH hbrush;
	switch (mssg)                  /* handle the mssgs */
	{
	case WM_COMMAND:
	{
		switch (LOWORD(wParam))
		{
		case IDB_PEN: {
			setUnchecked(tools, pen);
			break;
		}
		case IDB_LINE: {
			setUnchecked(tools, line);
			break;
		}
		case IDB_ELLIPSE: {
			setUnchecked(tools, ellipse);
			break;
		}
		case IDB_RECT: {
			setUnchecked(tools, rectangle);
			break;
		}
		case IDB_BEZIER: {
			setUnchecked(tools, bezier);
			bezierBool = true;
			InvalidateRect(hwnd, NULL, TRUE);
			UpdateWindow(hwnd);
			break;
		}
		case IDB_CLEAR: {
			setUnchecked(tools, clear);
			InvalidateRect(hwnd, &rect, FALSE);
			InvalidateRect(hwnd, &rect, TRUE);
			Button_SetCheck(clear, BST_UNCHECKED);
			break;
		}

		case IDB_OK: {
			GetWindowText(weight, textStore, 50);
			weightStatic = atoi(textStore);
			printf("%d", weightStatic);
			break; }
		}
		break;
	}

	case WM_CREATE:
	{
		/* Initialiazation of hwnd objects used in the window */
		pen = CreateWindowEx(NULL, "BUTTON", "PEN",
			WS_VISIBLE | WS_CHILD | BS_AUTOCHECKBOX | BS_PUSHLIKE,
			0, 0, 140, 43,
			hwnd, (HMENU)IDB_PEN, GetModuleHandle(NULL), NULL);
		line = CreateWindowEx(NULL, "BUTTON", "LINE",
			WS_VISIBLE | WS_CHILD | BS_AUTOCHECKBOX | BS_PUSHLIKE,
			0, 43, 140, 43,
			hwnd, (HMENU)IDB_LINE, GetModuleHandle(NULL), NULL);
		rectangle = CreateWindowEx(NULL, "BUTTON", "RECTANGLE",
			WS_VISIBLE | WS_CHILD | BS_AUTOCHECKBOX | BS_PUSHLIKE,
			0, 86, 140, 43,
			hwnd, (HMENU)IDB_RECT, GetModuleHandle(NULL), NULL);
		ellipse = CreateWindowEx(NULL, "BUTTON", "ELLIPSE",
			WS_VISIBLE | WS_CHILD | BS_AUTOCHECKBOX | BS_PUSHLIKE,
			0, 129, 140, 43,
			hwnd, (HMENU)IDB_ELLIPSE, GetModuleHandle(NULL), NULL);
		clear = CreateWindowEx(NULL, "BUTTON", "CLEAR",
			WS_VISIBLE | WS_CHILD | BS_AUTOCHECKBOX | BS_PUSHLIKE,
			0, 215, 140, 43,
			hwnd, (HMENU)IDB_CLEAR, GetModuleHandle(NULL), NULL);
		bezier = CreateWindowEx(NULL, "BUTTON", "BEZIER",
			WS_VISIBLE | WS_CHILD | BS_AUTOCHECKBOX | BS_PUSHLIKE,
			0, 172, 140, 43,
			hwnd, (HMENU)IDB_BEZIER, GetModuleHandle(NULL), NULL);

		weight = CreateWindowEx(WS_EX_CLIENTEDGE, "EDIT", "SIZE",
			WS_VISIBLE | WS_CHILD | ES_NUMBER,
			5, 275, 35, 20,
			hwnd, (HMENU)IDC_WEIGHT, GetModuleHandle(NULL), NULL);
		okButton = CreateWindowEx(NULL, "BUTTON", "OK",
			WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
			40, 275, 30, 20,
			hwnd, (HMENU)IDB_OK, GetModuleHandle(NULL), NULL);
		CreateWindowEx(NULL, "BUTTON", "Red",
			WS_VISIBLE | WS_CHILD | BS_AUTORADIOBUTTON | WS_GROUP,
			180, 330, 60, 18,
			hwnd, (HMENU)IDB_RED, GetModuleHandle(NULL), NULL);
		CreateWindowEx(NULL, "BUTTON", "Green",
			WS_VISIBLE | WS_CHILD | BS_AUTORADIOBUTTON,
			240, 330, 60, 18,
			hwnd, (HMENU)IDB_GREEN, GetModuleHandle(NULL), NULL);
		CreateWindowEx(NULL, "BUTTON", "Blue",
			WS_VISIBLE | WS_CHILD | BS_AUTORADIOBUTTON,
			300, 330, 60, 18,
			hwnd, (HMENU)IDB_BLUE, GetModuleHandle(NULL), NULL);
		CreateWindowEx(NULL, "BUTTON", "Black",
			WS_VISIBLE | WS_CHILD | BS_AUTORADIOBUTTON | BST_CHECKED,
			360, 330, 60, 18,
			hwnd, (HMENU)IDB_BLACK, GetModuleHandle(NULL), NULL);
		CreateWindowEx(NULL, "BUTTON", "FILL",
			WS_VISIBLE | WS_CHILD | BS_AUTOCHECKBOX,
			440, 330, 60, 18,
			hwnd, (HMENU)IDB_FILL, GetModuleHandle(NULL), NULL);
		Button_SetCheck(GetDlgItem(hwnd, IDB_BLACK), BST_CHECKED);

		break;
	}

	case WM_LBUTTONDOWN:
	{
		if (mouse_x > 140 && mouse_x < 600 && mouse_y > 0 && mouse_y < 300)
		{
			if (Button_GetCheck(GetDlgItem(hwnd, IDB_RED)) == BST_CHECKED)
			{
				color = RGB(255, 0, 0);
			}
			else if (Button_GetCheck(GetDlgItem(hwnd, IDB_GREEN)) == BST_CHECKED)
			{
				color = RGB(0, 255, 0);
			}
			else if (Button_GetCheck(GetDlgItem(hwnd, IDB_BLUE)) == BST_CHECKED)
			{
				color = RGB(0, 0, 255);
			}
			else if (Button_GetCheck(GetDlgItem(hwnd, IDB_BLACK)) == BST_CHECKED)
			{
				color = RGB(0, 0, 0);
			}
			hpen = CreatePen(PS_SOLID, weightStatic, color);
			hdc = GetDC(hwnd);
			SelectObject(hdc, hpen);
			xFirst = LOWORD(lParam);
			yFirst = HIWORD(lParam);
			xLast = LOWORD(lParam);
			yLast = HIWORD(lParam);
			if (Button_GetCheck(line) == BST_CHECKED) {
				SetROP2(hdc, R2_WHITE);
				MoveToEx(hdc, xFirst, yFirst, NULL);
				LineTo(hdc, xLast, yLast);
				isDrawing = TRUE;
			}
			if (Button_GetCheck(pen) == BST_CHECKED) {
				xFirst = LOWORD(lParam);
				yFirst = HIWORD(lParam);
				isDrawing = TRUE;
			}
			if (Button_GetCheck(rectangle) == BST_CHECKED) {
				hbrush = getBrush(hwnd, color);
				FillRectangle(rectangle, hwnd, hbrush, hdc, xFirst, yFirst, xLast, yLast);
				isDrawing = TRUE;
				DeleteObject(hbrush);
			}
			if (Button_GetCheck(ellipse) == BST_CHECKED) {
				hbrush = getBrush(hwnd, color);
				FillEllipse(rectangle, hwnd, hbrush, hdc, xFirst, yFirst, xLast, yLast);
				isDrawing = TRUE;
				DeleteObject(hbrush);
			}

			DeleteObject(hpen);
			ReleaseDC(hwnd, hdc);
		}
		break;
	}

	case WM_MOUSEMOVE:
	{
		if (mouse_x > 140 && mouse_x < 600 && mouse_y > 0 && mouse_y < 300) {
			hdc = GetDC(hwnd);
			if (isDrawing == TRUE) {
				if (Button_GetCheck(GetDlgItem(hwnd, IDB_RED)) == BST_CHECKED)
				{
					color = RGB(255, 0, 0);
				}
				else if (Button_GetCheck(GetDlgItem(hwnd, IDB_GREEN)) == BST_CHECKED)
				{
					color = RGB(0, 255, 0);
				}
				else if (Button_GetCheck(GetDlgItem(hwnd, IDB_BLUE)) == BST_CHECKED)
				{
					color = RGB(0, 0, 255);
				}
				else if (Button_GetCheck(GetDlgItem(hwnd, IDB_BLACK)) == BST_CHECKED)
				{
					color = RGB(0, 0, 0);
				}
				hpen = CreatePen(PS_SOLID, weightStatic, color);
				SelectObject(hdc, hpen);
				SetROP2(hdc, R2_NOTXORPEN);
				if (Button_GetCheck(line) == BST_CHECKED) {
					MoveToEx(hdc, xFirst, yFirst, NULL);
					LineTo(hdc, xLast, yLast);
					xLast = LOWORD(lParam);
					yLast = HIWORD(lParam);
					MoveToEx(hdc, xFirst, yFirst, NULL);
					LineTo(hdc, xLast, yLast);
				}
				if (Button_GetCheck(pen) == BST_CHECKED) {
					MoveToEx(hdc, xLast, yLast, NULL);
					xLast = LOWORD(lParam);
					yLast = HIWORD(lParam);
					LineTo(hdc, xLast, yLast);
				}
				if (Button_GetCheck(rectangle) == BST_CHECKED) {
					hbrush = getBrush(hwnd, color);
					UnfillRectangle(rectangle, hwnd, hbrush, hdc, xFirst, yFirst, xLast, yLast);
					xLast = LOWORD(lParam);
					yLast = HIWORD(lParam);
					Rectangle(hdc, xFirst, yFirst, xLast, yLast);
					DeleteObject(hbrush);
				}
				if (Button_GetCheck(ellipse) == BST_CHECKED) {
					hbrush = getBrush(hwnd, color);
					UnfillEllipse(ellipse, hwnd, hbrush, hdc, xFirst, yFirst, xLast, yLast);
					xLast = LOWORD(lParam);
					yLast = HIWORD(lParam);
					Ellipse(hdc, xFirst, yFirst, xLast, yLast);
					DeleteObject(hbrush);
				}


			}
			DeleteObject(hpen);
			ReleaseDC(hwnd, hdc);
		}
		break;
	}

	case WM_LBUTTONUP: {
		if (mouse_x > 140 && mouse_x < 600 && mouse_y > 0 && mouse_y < 300) {
			hdc = GetDC(hwnd);
			xLast = LOWORD(lParam);
			yLast = HIWORD(lParam);
			release(hdc, xFirst, yFirst, yLast, xLast, hwnd);
			if (Button_GetCheck(line) == BST_CHECKED) {
				isDrawing = FALSE;
			}
			if (Button_GetCheck(pen) == BST_CHECKED) {
				isDrawing = FALSE;
			}
			if (Button_GetCheck(rectangle) == BST_CHECKED) {
				isDrawing = FALSE;
			}
			if (Button_GetCheck(ellipse) == BST_CHECKED) {
				isDrawing = FALSE;
			}
			break;
		}
	}

	case WM_PAINT: {
		hdc = BeginPaint(hwnd, &ps);
		FillRect(hdc, &rect, CreateSolidBrush(RGB(255, 255, 255)));

		SetBkMode(hdc, TRANSPARENT);
		if (bezierBool) {
			HPEN localhpen = CreatePen(PS_SOLID, weightStatic, color);
			SelectObject(hdc, localhpen);
			SetFocus(hwnd);
			PolyBezier(hdc, bez, 4);
			bezierBool = false;
			DeleteObject(localhpen);
		}
		EndPaint(hwnd, &ps);
		break;
	}
	case WM_GETMINMAXINFO: {
		LPMINMAXINFO winSize = (LPMINMAXINFO)lParam;
		resize(winSize);
		break;
	}
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hwnd, mssg, wParam, lParam);
	}
	return TRUE;
}
