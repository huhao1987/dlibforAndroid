package au.hao.and.dlibmodule.Imageprocessing;

import java.util.ArrayList;

public class CorrelationTracker {
    public native void initcorrelationtracker();
    public native boolean starttrack(ArrayList<String> list);
}
