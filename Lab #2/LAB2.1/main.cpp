#include <windows.h>
#include "resource1.h"
// Windows procedure, 
LRESULT CALLBACK WindowProcedure(HWND, UINT, WPARAM, LPARAM);
// Help procedure, 
BOOL CALLBACK HelpProc(HWND, UINT, WPARAM, LPARAM);
// Function for changing background color
void DrawColour(HWND hwnd);
void createWindows(HWND);

BOOL CALLBACK DialogFunct(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);

TCHAR szAppName[] = ("WindowsApp");

HWND hListBox, hAddButton, hClearButton,
hNewItem;
HMENU hPopUpMenu;
static HWND  hWndWidthScroll, hWndHeightScroll;
static int widthScroll = 45;
static int heightScroll = 45;

int mainWindowWidth = 600;
int mainWindowHeight = 400;



int WINAPI WinMain(HINSTANCE hThisInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpszArgument,
	int nCmdShow)
{
	HWND hwnd;                  // Window handle
	MSG messages;               // Messages struct
	WNDCLASSEX wc;              // windowclass datastructure

								// Window structure 
	wc.hInstance = hThisInstance;
	wc.lpszClassName = szAppName;
	wc.lpfnWndProc = WindowProcedure;      // function is called by windows 
	wc.style = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;
	wc.cbSize = sizeof(WNDCLASSEX);

	// Icon and mouse pointer
	wc.hIcon = LoadIcon(hThisInstance, MAKEINTRESOURCE(IDI_ICON1));
	wc.hIconSm = LoadIcon(hThisInstance, MAKEINTRESOURCE(IDI_ICON1));
	wc.hCursor = LoadCursor(hThisInstance, MAKEINTRESOURCE(IDC_CURSOR1));
	wc.lpszMenuName = MAKEINTRESOURCE(IDC_MENU);
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	// Use Windows's colour as the background of the window - default 
	wc.hbrBackground = CreateSolidBrush(RGB(218, 247, 166));

	// Register the window class, if it fails - quit the program 
	if (!RegisterClassEx(&wc))
		return 0;

	hwnd = CreateWindowEx(
		0,
		szAppName, // window class name
		TEXT("Lab 2"), // window caption
		WS_OVERLAPPEDWINDOW, // window style
		CW_USEDEFAULT, // initial x position
		CW_USEDEFAULT, // initial y position
		mainWindowWidth, // initial x size
		mainWindowHeight, // initial y size
		NULL, // parent window handle
		NULL, // window menu handle
		hThisInstance, // program instance handle
		NULL
	); // creation parameters           

	RegisterHotKey(hwnd, HK_CTRL_C, MOD_CONTROL, 0x43);
	RegisterHotKey(hwnd, HK_CRTL_SPACE, MOD_CONTROL, VK_SPACE);
	// Make the window visible on the screen
	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);

	while (GetMessage(&messages, NULL, 0, 0))
	{
		// Translate messages
		TranslateMessage(&messages);
		// Send message to the WindowProcedure 
		DispatchMessage(&messages);
	}

	// The program return-value is 0 - The value that PostQuitMessage() gave 
	return messages.wParam;
}

LRESULT CALLBACK WindowProcedure(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static HMENU hMenu;
	PAINTSTRUCT ps;
	HDC hdc;
	HFONT hFont;
	
	UINT iTextLength;
	char* szText;
	static POINT pt;
	int curPosition;
	HINSTANCE hInstance = nullptr;

	switch (message)                  // handle the messages
	{
	case WM_CREATE:
		hInstance = (HINSTANCE)((LPCREATESTRUCT)lParam)->hInstance;
		hMenu = LoadMenu(hInstance, szAppName);
		hMenu = GetSubMenu(hMenu, 0);
		createWindows(hwnd);
		break;

	case WM_PAINT:
		RECT rect;
		hdc = BeginPaint(hwnd, &ps);
		GetClientRect(hwnd, &rect);
		hFont = CreateFont(25, 20, 0, 0, FW_BOLD, FALSE, TRUE, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS,
			CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, VARIABLE_PITCH, TEXT("Times New Roman"));
		SelectObject(hdc, hFont);
		SetBkColor(hdc, RGB(96, 125, 139));
		SetTextColor(hdc, RGB(218, 247, 166));
		DrawText(hdc, TEXT("Crew's MEMBERS"), -1, &rect, DT_SINGLELINE | DT_CENTER | DT_TOP);
		EndPaint(hwnd, &ps);

	case WM_COMMAND:
		switch (LOWORD(wParam)) {
			case ID_ADD_BUTTON:
				iTextLength = (UINT)SendMessage(hNewItem, WM_GETTEXTLENGTH, 0, 0);
				if (iTextLength != 0) {
					szText = (char*)malloc(iTextLength + 1);
					SendMessage(hNewItem, WM_GETTEXT, iTextLength + 1, (LPARAM)szText);
					SendMessage(hListBox, LB_ADDSTRING, 0, (LPARAM)szText);
					SendMessage(hNewItem, WM_SETTEXT, 0, (LPARAM)"");
					free(szText);
				}
				break;
			case ID_CLEAR_BUTTON:
				SendMessage(hListBox, LB_RESETCONTENT, 0, 0);
				break;
			case ID_FILE_ABOUT:
				MessageBox(hwnd, TEXT("Add Members of a team in a simple List"), MB_OK, MB_ICONASTERISK);
				break;
			case ID_KEYBOARDOPTIONS_MINIMIZETHESCREEN:
				SendMessage(hListBox, LB_SETITEMDATA, 0, (LPARAM)TEXT(" "));
				SetWindowPos(hwnd, HWND_TOP, 200, 200, 200, 300, SWP_NOOWNERZORDER);
				break;
			case ID_KEYBOARDOPTIONS_CHANGEBACKGROUNDCOLOUR:
				DrawColour(hwnd);
				break;
			case ID_CONTEXTMENU_DELETE:
				curPosition
					= SendMessage(hListBox, LB_GETCURSEL, 0, 0);
				SendMessage(hListBox, LB_DELETESTRING, curPosition
					, 0);
				break;
			case ID_CONTEXTMENU_RENAME:
				if (DialogBox(hInstance, MAKEINTRESOURCE(IDR_ABOUTBOX), hwnd, (DLGPROC)DialogFunct)) {
					InvalidateRect(hwnd, NULL, TRUE);
				}
				break;
			}
	case WM_CONTEXTMENU:
		if ((HWND)wParam == hListBox) {
			hPopUpMenu = LoadMenu(NULL, MAKEINTRESOURCE(IDR_POP_MENU));
			hPopUpMenu = GetSubMenu(hPopUpMenu, 0);
			ClientToScreen(hwnd, (LPPOINT)&pt);
			pt.x = LOWORD(lParam);
			pt.y = HIWORD(lParam);
			TrackPopupMenu(hPopUpMenu, TPM_RIGHTBUTTON, pt.x, pt.y, 0, hwnd, NULL);
			DestroyMenu(hPopUpMenu);
		}
	case WM_HSCROLL: {
		GetWindowRect(hwnd, &rect);
		int iSysWidth = GetSystemMetrics(SM_CXSCREEN);
		int iSysHeight = GetSystemMetrics(SM_CYSCREEN);
		int iWinWidth = rect.right - rect.left;
		int iWinHeight = rect.bottom - rect.top;

		switch (GetWindowLong((HWND)lParam, GWL_ID)) {
			case ID_SCROLLW: {
				switch (LOWORD(wParam)) {
					case SB_LINELEFT:
						widthScroll -= 1;
						break;
					case SB_LINERIGHT:
						widthScroll += 1;
						break;
					case SB_THUMBTRACK:
						widthScroll = HIWORD(wParam);
						break;
					default:
						break;
				}
				SetScrollPos(hWndWidthScroll, SB_CTL, widthScroll, FALSE);
				MoveWindow(hwnd, rect.left, rect.top, (widthScroll * iSysWidth / 100), iWinHeight, TRUE);
			}
			break;
			case ID_SCROLLH: {
					switch (LOWORD(wParam)) {
					case SB_LINELEFT:
						heightScroll--;
						break;
					case SB_LINERIGHT:
						heightScroll++;
						break;
					case SB_THUMBTRACK:
						heightScroll = HIWORD(wParam);
						break;
					default:
						break;
				}
				SetScrollPos(hWndHeightScroll, SB_CTL, heightScroll, TRUE);
				MoveWindow(hwnd, rect.left, rect.top, iWinWidth, (heightScroll * iSysHeight / 100), TRUE);
			}
		break;
		}
	}
	break;
	
	case WM_HOTKEY:
		switch (wParam) {
		case HK_CTRL_C:
			DrawColour(hwnd);
			break;
		case HK_CRTL_SPACE:
			SendMessage(hListBox, LB_SETITEMDATA, 0, (LPARAM)TEXT(" "));
			SetWindowPos(hwnd, HWND_TOP, 200, 200, 200, 300, SWP_NOOWNERZORDER);
			break;
		}
		break;
	case WM_SETCURSOR:
		hInstance = GetModuleHandle(NULL);
		if (LOWORD(lParam) == HTCLIENT) {
			SetCursor(LoadCursor(hInstance, MAKEINTRESOURCE(IDC_CURSOR1)));
			return TRUE;
		}
		break;
	case WM_SETFOCUS: {
		SetFocus(hwnd);
	}
	break;

	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hwnd, message, wParam, lParam);
}



void createWindows(HWND hwnd) {
	HINSTANCE hInstance = GetModuleHandle(NULL);
	hListBox = CreateWindowExW(WS_EX_CLIENTEDGE,
		L"LISTBOX", NULL,
		WS_CHILD | WS_VISIBLE | LBS_NOTIFY | WS_VSCROLL | LBS_HASSTRINGS,
		150, 60, 200, 200,
		hwnd, (HMENU)IDC_LIST_BOX, hInstance, NULL);

	hNewItem = CreateWindowEx(
		WS_EX_CLIENTEDGE,
		TEXT("Edit"),
		TEXT(""),
		WS_CHILD | WS_VISIBLE | WS_BORDER,
		150, 30, 200, 20, hwnd,
		(HMENU)ID_NEW_ITEM,
		GetModuleHandle(NULL),
		NULL);
	SetFocus(hNewItem);

	hAddButton = CreateWindowEx(
		NULL,
		TEXT("Button"),
		TEXT("Add"),
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		400, 50, 78, 20, hwnd,
		(HMENU)ID_ADD_BUTTON,
		GetModuleHandle(NULL),
		NULL);

	hClearButton = CreateWindowEx(
		NULL,
		TEXT("Button"),
		TEXT("Clear"),
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		400, 80, 78, 20, hwnd,
		(HMENU)ID_CLEAR_BUTTON,
		GetModuleHandle(NULL),
		NULL);

	hWndWidthScroll = CreateWindowEx((DWORD)NULL,
		TEXT("scrollbar"),
		NULL,
		WS_CHILD | WS_VISIBLE | SBS_HORZ,
		100, 270, 300, 20,
		hwnd,
		(HMENU)ID_SCROLLW,
		hInstance,
		NULL);
	SetScrollRange(hWndWidthScroll, SB_CTL, 0, 100, TRUE);
	SetScrollPos(hWndWidthScroll, SB_CTL, 45, TRUE);

	hWndHeightScroll = CreateWindowEx((DWORD)NULL,
		TEXT("scrollbar"),
		NULL,
		WS_CHILD | WS_VISIBLE | SBS_HORZ,
		100, 300, 300, 20,
		hwnd,
		(HMENU)ID_SCROLLH,
		hInstance,
		NULL);
	SetScrollRange(hWndHeightScroll, SB_CTL, 0, 100, TRUE);
	SetScrollPos(hWndHeightScroll, SB_CTL, 45, TRUE);
}

void DrawColour(HWND hwnd) {

	PAINTSTRUCT ps;
	RECT r;
	static int a, b, c, textColor = 0;
	static bool backgFlag;

	GetClientRect(hwnd, &r);

	if (r.bottom == 0)
		return;

	HDC hdc = BeginPaint(hwnd, &ps);
	a = rand() % 255;
	b = rand() % 255;
	c = rand() % 255;
	backgFlag = true;
	if (backgFlag == true)
	{
		SetClassLong(hwnd, GCL_HBRBACKGROUND, (LONG)CreateSolidBrush(RGB(a, b, c)));
	}
	InvalidateRect(hwnd, NULL, TRUE);
	EndPaint(hwnd, &ps);
}

BOOL CALLBACK DialogFunct(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam) {
	static HWND hEditControl;
	int curPosition, iTextLength;
	TCHAR *szText;

	switch (message) {
	case WM_INITDIALOG:
		hEditControl = GetDlgItem(hDlg, ID_EDIT);
		SetFocus(hEditControl);
		return FALSE;
	case WM_COMMAND:
		switch (LOWORD(wParam)) {
			case ID_DIALOG_RENAME:
				iTextLength = (UINT)SendMessage(hEditControl, WM_GETTEXTLENGTH, 0, 0);
				szText = (char*)malloc(iTextLength + 1);
				SendMessage(hEditControl, WM_GETTEXT, (WPARAM)(iTextLength + 1), (LPARAM)szText);
				curPosition
					= (int)SendMessage(hListBox, LB_GETCURSEL, 0, 0);
				SendMessage(hListBox, LB_DELETESTRING, 0, 0);
				SendMessage(hListBox, LB_INSERTSTRING, curPosition
					, (LPARAM)szText);
				SendMessage(hEditControl, WM_SETTEXT, 0, (LPARAM)"");
				free(szText);
				EndDialog(hDlg, TRUE);
				return TRUE;
		}
	}
	return FALSE; ;
}
