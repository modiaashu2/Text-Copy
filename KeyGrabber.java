import java.io.*;

class KeyGrabber
{
    static ClipBoard C;
    static
    {
        C = new ClipBoard();
        // File f;
        // f = new File("Mouse.dll");
        // System.load(f.getAbsolutePath());
        System.loadLibrary("Mouse");
    }

    private native void listen();

    public static void fire_key_event(int i)
    {
        C.get(i);
        System.out.println("key pressed (java code)");
    }

    public static void fire_key_event_2(int i)
    {
        C.add(i);
        System.out.println("key pressed (java code)");
    }

    public static void main(String[] args)
    {
        new KeyGrabber().listen();
    }
}
