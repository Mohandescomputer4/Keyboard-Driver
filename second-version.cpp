#include <windows.h>
#include <iostream>

LRESULT CALLBACK KeyboardProc(int nCode, WPARAM wParam, LPARAM lParam) {
    if (nCode == HC_ACTION) {
        PKBDLLHOOKSTRUCT p = reinterpret_cast<PKBDLLHOOKSTRUCT>(lParam);
        DWORD scanCode = p->scanCode;
        UINT vkCode = MapVirtualKey(scanCode, MAPVK_VSC_TO_VK_EX);

        // Check if key is being pressed
        if (wParam == WM_KEYDOWN || wParam == WM_SYSKEYDOWN) {
            std::cout << "Key Pressed: Scan Code: " << scanCode << ", Virtual Key Code: " << vkCode << std::endl;
        }
        // Check if key is being released
        else if (wParam == WM_KEYUP || wParam == WM_SYSKEYUP) {
            std::cout << "Key Released: Scan Code: " << scanCode << ", Virtual Key Code: " << vkCode << std::endl;
        }
    }
    return CallNextHookEx(NULL, nCode, wParam, lParam);
}

int main() {
    // Set a low-level keyboard hook
    HHOOK keyboardHook = SetWindowsHookEx(WH_KEYBOARD_LL, KeyboardProc, NULL, 0);

    // Run a message loop
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0) != 0) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    UnhookWindowsHookEx(keyboardHook);

    return 0;
}
