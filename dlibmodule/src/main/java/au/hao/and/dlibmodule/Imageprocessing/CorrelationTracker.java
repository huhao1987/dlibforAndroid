package au.hao.and.dlibmodule.Imageprocessing;

import android.graphics.Bitmap;

import java.util.ArrayList;

import au.hao.and.dlibmodule.Objects.Drectangle;
import au.hao.and.dlibmodule.Objects.Rectangle;

public class CorrelationTracker {
//    The track must init by this function firstly.
    public native void initcorrelationtracker();
//    the track must set up starttrack firstly and then update.
    public native boolean starttrack(Bitmap bitmap);
    public native double update(Bitmap bitmap);

    public native ArrayList<Drectangle> trackwithPics(ArrayList<String> list);

}
