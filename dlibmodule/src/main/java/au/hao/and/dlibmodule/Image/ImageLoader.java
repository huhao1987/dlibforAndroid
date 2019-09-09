package au.hao.and.dlibmodule.Image;

public class ImageLoader {
    public Jpegloader Jpegloader(String filename){
            Jpegloader jpegloader=new Jpegloader();
            jpegloader.initimage(filename);
            return jpegloader;
    }
    private void initlib(){
        System.loadLibrary("ImageLoader");
    }

    public static ImageLoader imageLoader =null;

    public static ImageLoader init(){
        if(imageLoader ==null){
            imageLoader =new ImageLoader();
            imageLoader.initlib();
        }
        return imageLoader;
    }}
