package au.hao.and.dlibforandroid;
import android.content.Context;
import android.graphics.Canvas;
import android.graphics.Color;
import android.graphics.Paint;
import android.graphics.Rect;
import android.util.AttributeSet;
import android.util.Log;
import android.view.View;
import androidx.annotation.Nullable;

import java.util.ArrayList;
import java.util.concurrent.CopyOnWriteArrayList;

import au.hao.and.dlibmodule.Objects.Rectangle;

public class faceDisplayView extends View {
    private static final String TAG = "FaceRectView";
    private ArrayList<Rectangle> faceRectList = new ArrayList<>();

    public faceDisplayView(Context context) {
        this(context, null);
    }

    public faceDisplayView(Context context, @Nullable AttributeSet attrs) {
        super(context, attrs);
    }

    @Override
    protected void onDraw(Canvas canvas) {
        super.onDraw(canvas);

        if (faceRectList != null && faceRectList.size() > 0) {
            for (int i = 0; i < faceRectList.size(); i++) {
                Log.d("theviewisss",faceRectList.toString());
                Paint paint=new Paint();
                paint.setStyle(Paint.Style.STROKE);
                paint.setColor(Color.GREEN);
                if(MainActivity.Companion.getScale()!=null)
                canvas.scale(MainActivity.Companion.getScale()+1,MainActivity.Companion.getScale()+1);
                Rect rect=new Rect((int)faceRectList.get(i).getLeft(),(int)faceRectList.get(i).getTop(),(int)faceRectList.get(i).getRight(),(int)faceRectList.get(i).getBottom());
                canvas.drawRect(rect,paint);
            }
        }
    }

    public void clearFaceInfo() {
        faceRectList.clear();
        postInvalidate();
    }



    public void addFaceInfo(ArrayList<Rectangle> faceInfoList) {
        faceRectList.addAll(faceInfoList);
        postInvalidate();
    }

}