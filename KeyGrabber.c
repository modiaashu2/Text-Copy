#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/keysymdef.h>
#include "KeyGrabber.h"
#include <stdio.h>
#include <stdlib.h>

#define XK_F3                            0xffc0
#define KEYCODE XK_v
#define XK_KP_1                          0xffb1
#define XK_KP_2                          0xffb2


/*XKeyEvent createKeyEvent(Display *display, Window &win, Window &winRoot, bool press, int keycode, int modifiers)
{
    XKeyEvent event;
    event.display = display;
    event.window = win;
    event.root = winRoot;
    event.subwindow = None;
    event.time = CurrentTime;
    event.x = 1;
    event.y = 1;
    event.x_root = 1;
    event.y_root = 1;
    event.same_screen = True;
    event.keycode = XKeysymToKeycode(display, keycode);
    event.state = ControlMask;
    if(press)
    {
        event.type = KeyPress;
    }
    else
    {
        event.type = KeyRelease;
    }
    return event;
}
*/

JNIEXPORT void JNICALL Java_KeyGrabber_listen(JNIEnv *env, jobject obj)
{
    printf("Starting to listen to Key F3\n");
    jclass cls = (*env)->FindClass(env, "KeyGrabber");
    if(cls == NULL)
    {
        printf("Cannot find class KeyGrabber\n");
        exit(-1);
    }
    jmethodID mid = (*env)->GetStaticMethodID(env, cls, "fire_key_event", "()V");
    if(mid == NULL)
    {
        printf("Cannot find method fire_key_event\n");
        exit(-1);
    }
    Window root;
    XEvent ev;
    Display *dpy = XOpenDisplay(0);
    if(!dpy)
    {
        return;
    }
    root = DefaultRootWindow(dpy);
    char *key_string = "F3";
    KeyCode key = XKeysymToKeycode(dpy, XK_F3);
//    key = 0x0036;
//    key = 16;
    printf("%x\n", key);
    Window winFocus;
    int revert;
    XKeyEvent event;
    XGrabKey(dpy, key, AnyModifier, root, False, GrabModeAsync, GrabModeAsync);
    //XSelectInput()
// if(GetKeyState(VK_SHIFT) != 0)
        //
    XGetInputFocus(dpy, &winFocus, &revert);
    for(;;)
    {
        //dpy = XOpenDisplay(0);
        root = XDefaultRootWindow(dpy);
        XGrabKey(dpy, key, AnyModifier, root, False, GrabModeAsync, GrabModeAsync);
        // if(GetKeyState(VK_SHIFT) != 0)
        // printf("Shift\n");
        XNextEvent(dpy, &ev);
        if(ev.type == FocusOut)
        {
            printf("hi");
            if(winFocus != root)
            XSelectInput(dpy, winFocus, 0);
            XGetInputFocus(dpy, &winFocus, &revert);
            if(winFocus == PointerRoot)
            winFocus = root;
            XSelectInput(dpy, winFocus, KeyReleaseMask | FocusChangeMask | KeyPressMask);
        }
        //if(ev.xkey.state & (Mod1Mask) == Mod1Mask)
        //{
            if(ev.type = KeyPress && ev.xkey.keycode == key)
            {
                XKeyEvent event;
                event.display = dpy;
                event.window = winFocus;
                event.root = root;
                event.subwindow = None;
                event.time = CurrentTime;
                event.x = 1;
                event.y = 1;
                event.x_root = 1;
                event.y_root = 1;
                event.same_screen = True;
                event.keycode = XKeysymToKeycode(dpy, KEYCODE);
                event.state = ControlMask;
                event.type = KeyPress;
                XSendEvent(event.display, event.window, True, KeyPressMask, (XEvent *) &event);
                event.type = KeyRelease;
                XSendEvent(event.display, event.window, True, KeyPressMask, (XEvent *) &event);
        //        event = createKeyEvent(dpy, winFocus, root, True, KEYCODE, 0);
        //        XSendEvent(event.display, event.window, True, KeyPressMask, (XEvent *) &event);
        //        event = createKeyEvent(dpy, winFocus, root, False, KEYCODE, 0);
        //        XSendEvent(event.display, event.window, True, KeyPressMask, (XEvent *) &event);
                (*env)->CallStaticVoidMethod(env, cls, mid);
            }
        //}
    }
    printf("Leaving C Code\n");
    return;
}
