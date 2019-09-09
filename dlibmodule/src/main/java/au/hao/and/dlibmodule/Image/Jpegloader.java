package au.hao.and.dlibmodule.Image;

public class Jpegloader {
    public native void initimage(String filename);
    public native boolean isgray();
    public native boolean isrgb();
    public native void release();
}
