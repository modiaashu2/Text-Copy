#define WINVER 0x0500
#include <windows.h>
INPUT ip; 
HHOOK hHock = NULL;
KBDLLHOOKSTRUCT kbdstruct;


LRESULT CALLBACK MyLowLevelHook ( int nCode , WPARAM wParam , LPARAM lParam)
{
    if(nCode >= 0)
    {
        if(wParam == WM_KEYDOWN && GetAsyncKeyState(VK_CONTROL))
        {
            kbdstruct = *((KBDLLHOOKSTRUCT *)lParam);
            if(kbdstruct.vkCode == VK_F3)
            {
                ip.ki.wVk = VK_CONTROL;
                ip.ki.dwFlags = 0; // 0 for key press
                SendInput(1, &ip, sizeof(INPUT));
        
                // Press the "V" key
                ip.ki.wVk = 'V';
                ip.ki.dwFlags = 0; // 0 for key press
                SendInput(1, &ip, sizeof(INPUT));
        
                // Release the "V" key
                ip.ki.wVk = 'V';
                ip.ki.dwFlags = KEYEVENTF_KEYUP;
                SendInput(1, &ip, sizeof(INPUT));
        
                // Release the "Ctrl" key
                ip.ki.wVk = VK_CONTROL;
                ip.ki.dwFlags = KEYEVENTF_KEYUP;
                SendInput(1, &ip, sizeof(INPUT));
                printf("_a_");
            }
        }
    }
    return CallNextHookEx(hHock , nCode ,wParam , lParam);
}

int main()
{
    // Create a generic keyboard event structure
    
    ip.type = INPUT_KEYBOARD;
    ip.ki.wScan = 0;
    ip.ki.time = 0;
    ip.ki.dwExtraInfo = 0;
    MSG msg;
	hHock = SetWindowsHookEx(WH_KEYBOARD_LL, MyLowLevelHook , NULL,NULL);

    while(!GetMessage(&msg, NULL, NULL, NULL)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
	
    UnhookWindowsHookEx(hHock);
    return 0;
}