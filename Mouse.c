#define WINVER 0x0500
#include <windows.h>
#include "KeyGrabber.h"
#include <stdio.h>
#include <stdlib.h>
#include <jni.h>
#include <unistd.h>

INPUT ip; 
HHOOK hHock = NULL;
KBDLLHOOKSTRUCT kbdstruct;
jclass gcls;
jmethodID gmid, gmid2;
JNIEnv *genv;
jobject *gobj;

LRESULT CALLBACK MyLowLevelHook ( int nCode , WPARAM wParam , LPARAM lParam)
{
    if(nCode >= 0)
    {
        if(wParam == WM_KEYDOWN && GetKeyState(VK_CONTROL))
        {
            kbdstruct = *((KBDLLHOOKSTRUCT *)lParam);
            if(kbdstruct.vkCode == VK_F6)
            {
                (*genv)->CallStaticVoidMethod(genv, gobj, gmid, 1);
                Sleep(10);

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
            if(kbdstruct.vkCode == VK_F5)
            {
                ip.ki.wVk = VK_CONTROL;
                ip.ki.dwFlags = 0; // 0 for key press
                SendInput(1, &ip, sizeof(INPUT));
        
                // Press the "C" key
                ip.ki.wVk = 'C';
                ip.ki.dwFlags = 0; // 0 for key press
                SendInput(1, &ip, sizeof(INPUT));
        
                // Release the "C" key
                ip.ki.wVk = 'C';
                ip.ki.dwFlags = KEYEVENTF_KEYUP;
                SendInput(1, &ip, sizeof(INPUT));
        
                // Release the "Ctrl" key
                ip.ki.wVk = VK_CONTROL;
                ip.ki.dwFlags = KEYEVENTF_KEYUP;
                SendInput(1, &ip, sizeof(INPUT));


                Sleep(10);
                (*genv)->CallStaticVoidMethod(genv, gobj, gmid2, 1);
            }
            if(kbdstruct.vkCode == 34)
            {
                (*genv)->CallStaticVoidMethod(genv, gobj, gmid, 2);
                Sleep(10);

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
            if(kbdstruct.vkCode == 33)
            {
                ip.ki.wVk = VK_CONTROL;
                ip.ki.dwFlags = 0; // 0 for key press
                SendInput(1, &ip, sizeof(INPUT));
        
                // Press the "C" key
                ip.ki.wVk = 'C';
                ip.ki.dwFlags = 0; // 0 for key press
                SendInput(1, &ip, sizeof(INPUT));
        
                // Release the "C" key
                ip.ki.wVk = 'C';
                ip.ki.dwFlags = KEYEVENTF_KEYUP;
                SendInput(1, &ip, sizeof(INPUT));
        
                // Release the "Ctrl" key
                ip.ki.wVk = VK_CONTROL;
                ip.ki.dwFlags = KEYEVENTF_KEYUP;
                SendInput(1, &ip, sizeof(INPUT));
                printf("_a_");

                Sleep(10);
                (*genv)->CallStaticVoidMethod(genv, gobj, gmid2, 2);
            }
            if(kbdstruct.vkCode == 36)
            {
                (*genv)->CallStaticVoidMethod(genv, gobj, gmid, 3);
                Sleep(10);

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
            if(kbdstruct.vkCode == 35)
            {
                ip.ki.wVk = VK_CONTROL;
                ip.ki.dwFlags = 0; // 0 for key press
                SendInput(1, &ip, sizeof(INPUT));
        
                // Press the "C" key
                ip.ki.wVk = 'C';
                ip.ki.dwFlags = 0; // 0 for key press
                SendInput(1, &ip, sizeof(INPUT));
        
                // Release the "C" key
                ip.ki.wVk = 'C';
                ip.ki.dwFlags = KEYEVENTF_KEYUP;
                SendInput(1, &ip, sizeof(INPUT));
        
                // Release the "Ctrl" key
                ip.ki.wVk = VK_CONTROL;
                ip.ki.dwFlags = KEYEVENTF_KEYUP;
                SendInput(1, &ip, sizeof(INPUT));
                printf("_a_");

                Sleep(10);
                (*genv)->CallStaticVoidMethod(genv, gobj, gmid2, 3);
            }
        }
    }
    return CallNextHookEx(hHock , nCode ,wParam , lParam);
}


JNIEXPORT void JNICALL _Java_KeyGrabber_listen(JNIEnv *env, jobject obj)
{
    gobj = obj;
    genv = env;
    printf("Starting to listen to Key F3\n");
    jclass cls = (*env)->FindClass(env, "KeyGrabber");
    gcls = cls;
    if(cls == NULL)
    {
        printf("Cannot find class KeyGrabber\n");
        exit(-1);
    }
    jmethodID mid = (*env)->GetStaticMethodID(env, cls, "fire_key_event", "(I)V");
    gmid = mid;
    if(mid == NULL)
    {
        printf("Cannot find method fire_key_event\n");
        exit(-1);
    }
    jmethodID mid2 = (*env)->GetStaticMethodID(env, cls, "fire_key_event_2", "(I)V");
    gmid2 = mid2;
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
    printf("Leaving C Code\n");
    return;
}
