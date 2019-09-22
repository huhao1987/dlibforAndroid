package au.hao.and.dlibmodule.Imageprocessing;

import android.graphics.Bitmap;

import java.util.ArrayList;

import au.hao.and.dlibmodule.Objects.Drectangle;
import au.hao.and.dlibmodule.Objects.Point;
import au.hao.and.dlibmodule.Objects.Rectangle;

public class ObjectDetection {
    CorrelationTracker tracker=null;
    public native ArrayList<Rectangle> getfrontalfacedetector(String filename);
    public native ArrayList<Rectangle> getfrontalfacewithbitmap(Bitmap bitmap);
    public native ArrayList<ArrayList<Rectangle>> facelandmarkdetection(ArrayList<String> files,String datfile);
    public native ArrayList<Point> facelandmarkdetectionwithBitmap(Bitmap bitmap, String datfile);

    private void initlib(){
        System.loadLibrary("objectdetection");
    }

    public static ObjectDetection objectdetection =null;

    public static ObjectDetection init(){
        if(objectdetection ==null){
            objectdetection =new ObjectDetection();
            objectdetection.initlib();
        }
        return objectdetection;
    }
    public void initCorrelationTracker(boolean converttogray){
        tracker=new CorrelationTracker();
        tracker.initcorrelationtracker(converttogray);
    }
    public ArrayList<Drectangle> trackwithPics(ArrayList<String> list){
        return tracker.trackwithPics(list);
    }

    public boolean startTrack(Bitmap bitmap){
        return tracker.starttrack(bitmap);
    }
    public double updatetrack(Bitmap bitmap){
       return tracker.update(bitmap);
    }
}
