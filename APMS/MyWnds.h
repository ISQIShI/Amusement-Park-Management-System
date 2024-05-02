#pragma once
#include"general.h"

LRESULT CALLBACK MainWndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

class MyWnds {
public:
	static void MainWnd(HINSTANCE hInstance);
};