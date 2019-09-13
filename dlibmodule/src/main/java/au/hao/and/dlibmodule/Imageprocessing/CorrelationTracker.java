package au.hao.and.dlibmodule.Imageprocessing;

import java.util.ArrayList;

import au.hao.and.dlibmodule.Objects.Drectangle;
import au.hao.and.dlibmodule.Objects.Rectangle;

public class CorrelationTracker {
    public native void initcorrelationtracker();
    public native ArrayList<Drectangle> starttrack(ArrayList<String> list);
}
