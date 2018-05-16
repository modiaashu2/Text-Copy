import java.awt.datatransfer.Clipboard;
import java.awt.datatransfer.ClipboardOwner;
import java.awt.datatransfer.Transferable;
import java.awt.datatransfer.StringSelection;
import java.awt.datatransfer.DataFlavor;
import java.awt.datatransfer.UnsupportedFlavorException;
import java.awt.Toolkit;
import java.io.*;


public class ClipBoard implements ClipboardOwner
{
    String C[];
    ClipBoard()
    {
        C = new String[4];
    }

    public void lostOwnership(Clipboard clipboard, Transferable contents) 
    {
        System.out.println("Clipboard contents replaced");
    }

    public void add(int i)
    {
        if(i < 0 && i > 3)
        return;
        Clipboard Cl;
        Cl = Toolkit.getDefaultToolkit().getSystemClipboard();
        Transferable contents = Cl.getContents(null);
        boolean hasTransferableText = (contents != null) && contents.isDataFlavorSupported(DataFlavor.stringFlavor);
        if (hasTransferableText) 
        {
            try 
            {
                C[i] = (String)contents.getTransferData(DataFlavor.stringFlavor);
                System.out.println("hi" + C[i] + "hi");
            }
            catch (Exception ex)
            {
                System.out.println(ex);
                ex.printStackTrace();
            }
        }
        System.out.println("C1 at " + i + " " + C[i]);
    }
    public void get(int i)
    {
        Clipboard Cl = Toolkit.getDefaultToolkit().getSystemClipboard();
        StringSelection stringSelection = new StringSelection(C[i]);
        try{
        System.out.println(stringSelection.getTransferData(DataFlavor.stringFlavor));}
        catch(Exception e){}
        //Transferable ct = new Transferable();
       // ct.setContents(stringSelection);
        Toolkit.getDefaultToolkit().getSystemClipboard().setContents(stringSelection, this);
    }
}