package au.hao.and.dlibmodule.Imageprocessing;

import android.graphics.Bitmap;

import java.util.ArrayList;

import au.hao.and.dlibmodule.Objects.Drectangle;
import au.hao.and.dlibmodule.Objects.Rectangle;

public class ObjectDetection {
    CorrelationTracker tracker=null;
    public native ArrayList<Rectangle> getfrontalfacedetector(String filename);
    public native ArrayList<Rectangle> getfrontalfacewithbitmap(Bitmap bitmap);
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
    public void initCorrelationTracker(){
        tracker=new CorrelationTracker();
        tracker.initcorrelationtracker();
    }
    public ArrayList<Drectangle> startTrack(ArrayList<String> list){
        return tracker.starttrack(list);
    }
}
