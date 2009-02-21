// Copyright (c) 2008 Dean McNamee <dean@gmail.com>
// 
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to
// deal in the Software without restriction, including without limitation the
// rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
// sell copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
// 
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
// IN THE SOFTWARE.

// Dopest codes on the block.  Turn your desktop to folder list view.
//
// Build using the MSVC compiler:
//   cl listview.c user32.lib
//
// You'll probably want to add this to startup, for example the registry key:
//   HKLM/Software/Microsoft/Windows/CurrentVersion/Run
//
// - deanm / jan 2008

#define _WIN32_WINNT 0x501
#include <windows.h>
#include <commctrl.h>

#include <stdio.h>

HWND FindChild(HWND parent, LPCTSTR cls, LPCTSTR win) {
  if (parent == NULL) return NULL;
  return FindWindowEx(parent, NULL, cls, win);
}

int APIENTRY WinMain(HINSTANCE inst, HINSTANCE prev, LPSTR cl, int show) {
  // Find the desktop folder view.
  HWND folder = FindChild(
    FindChild(GetShellWindow(), "SHELLDLL_DefView", ""),
    "SysListView32", "FolderView");

  // Setup the style (removing noscroll), otherwise list style doesn't
  // seem to work correctly (docs say noscroll is incompatible with list).
  SetWindowLong(folder, GWL_STYLE,
    GetWindowLong(folder, GWL_STYLE) & ~LVS_NOSCROLL);

  // Switch to list view.
  SendMessage(folder, LVM_SETVIEW, LV_VIEW_LIST, 0);

  // Set the column width.  You can adjust the 200 for a different width.
  ListView_SetColumnWidth(folder, 0, 200);

  // Refresh.
  UpdateWindow(folder);
  
  return 0;
}
