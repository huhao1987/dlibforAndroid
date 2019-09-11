package au.hao.and.dlibmodule.ImageProcessing;

import java.util.ArrayList;

import au.hao.and.dlibmodule.Beans.Rectangle;

public class ObjectDetection {
    public native ArrayList<Rectangle> getfrontalfacedetector(String filename);
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
}
