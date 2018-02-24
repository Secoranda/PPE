#include <windows.h>
#include <stdlib.h>
#include <tchar.h>
#define IDC_BUTTON_1 102
#define IDC_BUTTON_2 103
#define IDC_TEXTAREA1 104
#define IDC_TEXTAREA2 105
#define IDC_LABEL 106

LRESULT CALLBACK WindowProcedure(HWND, UINT, WPARAM, LPARAM);
char szClassName[] = "Lab1";

int WINAPI WinMain(HINSTANCE hThisInstance, HINSTANCE hPrevInstance, LPSTR lpszArgument, int nCmdShow) {
	HWND hwnd;               /* This is the handle for our window */
	MSG messages;            /* Here messages to the application are saved */
	WNDCLASSEX wincl;        /* Data structure for the windowclass */

							 /* The Window structure */
	wincl.hInstance = hThisInstance;
	wincl.lpszClassName = szClassName;
	wincl.lpfnWndProc = WindowProcedure;      /* This function is called by windows */
	wincl.style = CS_HREDRAW | CS_VREDRAW;              /* Catch double-clicks */
	wincl.cbSize = sizeof(WNDCLASSEX);

	/* Use default icon and mouse-pointer */
	wincl.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wincl.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	wincl.hCursor = LoadCursor(NULL, IDC_ARROW);
	wincl.lpszMenuName = NULL;                 /* No menu */
	wincl.cbClsExtra = 0;                      /* No extra bytes after the window class */
	wincl.cbWndExtra = 0;                      /* structure or the window instance */
											   /* Use Windows's default colour as the background of the window */
	wincl.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);

	if (!RegisterClassEx(&wincl))
		return 0;
	hwnd = CreateWindowEx(
		0,                   /* Extended possibilites for variation */
		szClassName,         /* Classname */
		"Shopping List",  /* Title Text */
		WS_OVERLAPPEDWINDOW, /* default window */
		CW_USEDEFAULT,       /* Windows decides the position */

		CW_USEDEFAULT,       /* where the window ends up on the screen */
		550,                 /* The programs width */
		350,                 /* and height in pixels */
		HWND_DESKTOP,        /* The window is a child-window to desktop */
		NULL,                /* No menu */
		hThisInstance,       /* Program Instance handler */
		NULL                 /* No Window Creation data */
	);
	ShowWindow(hwnd, nCmdShow);


	while (GetMessage(&messages, NULL, 0, 0)) {
		TranslateMessage(&messages);
		DispatchMessage(&messages);
	}
	return messages.wParam;
}

LRESULT CALLBACK WindowProcedure(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;
	RECT rect;
	static HWND button1, button2, text1, text2, label11;
	static int cxCoord, cyCoord;
	LRESULT textSize;
	char box2[200];
	int iScreenW;
	int iScreenH;
	switch (message) {

		case WM_CREATE: {
			button1 = CreateWindowEx(NULL, TEXT("BUTTON"), TEXT("Remove"),
				WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
				0, 0, 0, 0,
				hwnd, (HMENU)IDC_BUTTON_1, GetModuleHandle(NULL), NULL); /* Default buttom*/
			button2 = CreateWindowEx(NULL, TEXT("BUTTON"), TEXT("Button2"),
				WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON | BS_OWNERDRAW,
				0, 0, 0, 0,
				hwnd, (HMENU)IDC_BUTTON_2, GetModuleHandle(NULL), NULL); /* Changed buttom*/
			text1 = CreateWindowEx(WS_EX_CLIENTEDGE, TEXT("EDIT"), TEXT(" "),
				WS_VISIBLE | WS_CHILD | ES_MULTILINE | ES_AUTOVSCROLL | WS_VSCROLL|  ES_LEFT,
				0, 0, 0, 0,
				hwnd, (HMENU)IDC_TEXTAREA1, GetModuleHandle(NULL), NULL);  /* Input textbox*/
			text2 = CreateWindowEx(WS_EX_CLIENTEDGE, TEXT("EDIT"), TEXT(" "),
				WS_VISIBLE | WS_CHILD | ES_MULTILINE | ES_AUTOVSCROLL | WS_VSCROLL | ES_LEFT,
				0, 0, 0, 0,
				hwnd, (HMENU)IDC_TEXTAREA2, GetModuleHandle(NULL), NULL);/* Input textbox*/
	
			label11 = CreateWindowEx(WS_EX_TRANSPARENT, TEXT("static"), "ADD items to buy", WS_VISIBLE| WS_CHILD ,
				0, 0, 0, 0, hwnd, (HMENU)IDC_LABEL, NULL, NULL);
			/* Label for text that moves to center when maximize the screen*/
			break; }
	
		case WM_SIZE:  /* All elements will be on the same place while max. or min. the screen */
			cxCoord = LOWORD(lParam); 
			cyCoord = HIWORD(lParam); 
			MoveWindow(button1, cxCoord - 150, cyCoord / 2 - 50, 110, 40, TRUE);
			MoveWindow(button2, cxCoord - 150, cyCoord / 2, 110, 40, TRUE);
			MoveWindow(text1, 15, 60, cxCoord - 250, cyCoord / 3, TRUE);
			MoveWindow(text2, 15, cyCoord / 2 + 30, cxCoord - 250, cyCoord / 3, TRUE);
			if (wParam == SIZE_MAXIMIZED) {
				/* If screen max. text will move to the center of the screen*/
				MoveWindow(label11, cxCoord/2, cyCoord / 2 , 160, 20, TRUE);
			} /* else keeps the given position */
			else { MoveWindow(label11, cxCoord - 150, cyCoord / 2 - 90, 160, 20, TRUE); }
			break;
			/* Will draw text */
		case WM_PAINT:
			cxCoord = LOWORD(lParam); 
			cyCoord = HIWORD(lParam); 
			HFONT hFont; /* parameter for new style */

			hdc = BeginPaint(hwnd, &ps);

			GetClientRect(hwnd, &rect);
			/*Title with new style */
			hFont = CreateFont(30, 20, 0, 0, FW_BOLD, FALSE, TRUE, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS,
				CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, VARIABLE_PITCH, TEXT("Times New Roman"));
			SelectObject(hdc, hFont);
			/* rect gives position for function draw text to draw a text */
			rect.top = 15;
			SetBkColor(hdc, RGB(96, 125, 139));
			SetTextColor(hdc, RGB(218, 247, 166));
			DrawText(hdc, TEXT("Shopping List "), -1, &rect, DT_SINGLELINE | DT_CENTER | DT_TOP);
			DeleteObject(hFont);
			EndPaint(hwnd, &ps);
			return 0;
			break;
		case WM_DRAWITEM:
			/* Draws the buttom with new style */
			if ((UINT)wParam == IDC_BUTTON_2) {
				LPDRAWITEMSTRUCT lpdis = (DRAWITEMSTRUCT*)lParam;
				SIZE size;
				char button2[10];
				strcpy(button2, "Add ");
				GetTextExtentPoint32(lpdis->hDC, button2, strlen(button2), &size);  /* gets parameters about created buttom for futher changes */
				SetTextColor(lpdis->hDC, RGB(96, 125, 139));  /* text color */
				SetBkColor(lpdis->hDC, RGB(218, 247, 166)); /* background color */
				/*draws text using the currently selected font, background color, and text color.*/
				ExtTextOut(
					lpdis->hDC,
					((lpdis->rcItem.right - lpdis->rcItem.left) - size.cx) / 2,/* The x - coordinate, in logical coordinates, of the reference point used to position the string.*/
					((lpdis->rcItem.bottom - lpdis->rcItem.top) - size.cy) / 2,/* The y-coordinate, in logical coordinates, of the reference point used to position the string.*/
					ETO_OPAQUE | ETO_CLIPPED, /*The current background color should be used to fill the rectangle and the text will be clipped to the rectangle.*/
					&lpdis->rcItem,/* the dimensions, in logical coordinates, of a rectangle*/
					button2,
					strlen(button2),
					NULL);

				DrawEdge(/*draws one or more edges of rectangle*/
					lpdis->hDC,
					&lpdis->rcItem,
					(lpdis->itemState & ODS_SELECTED ? EDGE_SUNKEN : EDGE_RAISED),
					/*EDGE_SUNKEN-Combination of BDR_SUNKENOUTER and BDR_SUNKENINNER=Sunken inner edge+Sunken outer edge.*/
					/* EDGE_RAISED-Combination of BDR_RAISEDOUTER and BDR_RAISEDINNER.=Raised inner edge.+Raised outer edge*/
					BF_RECT);/*Entire border rectangle.*/
				return TRUE;
			}
			break;
		case WM_COMMAND:/*Interaction between input texts and buttons*/
			switch (LOWORD(wParam))
			{
				case IDC_BUTTON_1:
				{ /*will delete texts from both input boxs, instead of box2 possible to write 1, and will delete by one char*/
					SendMessage(text2, WM_CHAR, (WPARAM)VK_BACK, (LPARAM)box2);
					SendMessage(text1, WM_CHAR, (WPARAM)VK_BACK, (LPARAM)box2);
					break;
				}
				case IDC_BUTTON_2:
				{

					textSize = SendMessage(text1, WM_GETTEXT, 100, (LPARAM)box2);
					box2[textSize] = _T('\0');/*from null posiion*/
					SendMessage(text2, EM_REPLACESEL, 0, (LPARAM)box2);/*copies from input 1 to input 2*/
					SendMessage(text2, EM_REPLACESEL, 0, (LPARAM)" \r\n");/*from new line each time will add smth new*/
					break;
				}
			}
			break;
			/* Limited size */
		case WM_GETMINMAXINFO:
		{
			LPMINMAXINFO winSize = (LPMINMAXINFO)lParam;
			winSize->ptMinTrackSize.x = 550;
			winSize->ptMinTrackSize.y = 350;
			winSize->ptMaxTrackSize.x = 750;
			winSize->ptMaxTrackSize.y = 550;
			break;
		}
		/*input box new style*/
		case WM_CTLCOLOREDIT: {
			HFONT hFont;
			if (IDC_TEXTAREA2 == GetDlgCtrlID((HWND)lParam))
			{
				HDC hdcStatic = (HDC)wParam;
				hFont = CreateFont(15, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS,
					CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, VARIABLE_PITCH, TEXT("Times New Roman"));
				SetTextColor(hdcStatic, RGB(218, 247, 166));
				SelectObject(hdcStatic, hFont);
				SetBkColor(hdcStatic, RGB(96, 125, 139));
				return (INT_PTR)CreateSolidBrush(RGB(218, 247, 166));
			}
			break; }
		/*label new style*/
		case WM_CTLCOLORSTATIC:{
			if (IDC_LABEL == GetDlgCtrlID((HWND)lParam))
			{
				HDC hdcStatic = (HDC)wParam;
				SetTextColor(hdcStatic, RGB(0, 0, 0));
				SetBkMode(hdcStatic, RGB(230, 230, 230));
				return (INT_PTR)GetStockObject(NULL_BRUSH);
			}
			
			break;

		}	
		case WM_SYSCOMMAND: 
			switch (wParam) {
				case SC_MINIMIZE:
					ShowWindow(hwnd, SW_MINIMIZE);
					return MessageBox(NULL, TEXT("Unable to minimize!"), TEXT("Minimize"), MB_OK | MB_ICONWARNING);
					break;
				case SC_MAXIMIZE:
						ShowWindow(hwnd, SW_MAXIMIZE);
					return MessageBox(NULL, TEXT("Unable to maximize!"), TEXT("Maximize"), MB_OK | MB_ICONASTERISK);
					break;
				case SC_CLOSE: {
					iScreenW = GetSystemMetrics(SM_CXSCREEN);
					iScreenH = GetSystemMetrics(SM_CYSCREEN);
					GetWindowRect(hwnd, &rect);
					/*gets new position for window and move it to that place*/
					SetWindowPos(
						hwnd, 0,
						(iScreenW - rect.right) / 10 * (rand() % 11),
						(iScreenH - rect.bottom) / 10 * (rand() % 11),
						0, 0,
						SWP_NOZORDER | SWP_NOSIZE);
					if (MessageBox(hwnd, "Do you want to close the program?", "Alert", MB_YESNO | MB_ICONQUESTION) == IDYES)
					{
						exit(1);
					}
					break;
				}
				default:
					return DefWindowProc(hwnd, message, wParam, lParam);
			}
			break;
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
		default:
			return DefWindowProc(hwnd, message, wParam, lParam);
			break;
	}
	return 0;
}
