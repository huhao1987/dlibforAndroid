package au.hao.and.dlibforandroid

import android.graphics.BitmapFactory
import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.os.Environment
import android.util.Log
import android.view.View
import au.hao.and.dlibmodule.Image.ImageLoader
import au.hao.and.dlibmodule.Image.Jpegloader
import au.hao.and.dlibmodule.Imageprocessing.ObjectDetection
import au.hao.and.dlibmodule.statistics.statisticsAbstract
import com.yanzhenjie.permission.AndPermission
import com.yanzhenjie.permission.runtime.Permission
import kotlinx.android.synthetic.main.activity_main.*
import java.util.*

class MainActivity : AppCompatActivity() {

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)
        AndPermission.with(this)
            .runtime()
            .permission(Permission.READ_EXTERNAL_STORAGE)
            .onGranted { permissions ->
                loading.visibility = View.VISIBLE
                object : Thread() {
                    override fun run() {
                        var objectdtection = ObjectDetection.init()
                        var filePath =
                            Environment.getExternalStorageDirectory().absolutePath + "/a.jpg";
                        var options = BitmapFactory.Options()
                        options.inPurgeable = true
                        options.inSampleSize = 2
                        var bitmap = BitmapFactory.decodeFile(filePath, options)
                        runOnUiThread {
                            displayview.setImageBitmap(bitmap)
                        }
//                       var arr= objectdtection.getfrontalfacewithbitmap(bitmap)
//                        var text=""
//                        for(a in arr){
//                            text+=a.toString()+"/n"
//                        }
//                       var f1=Environment.getExternalStorageDirectory().absolutePath + "/a.jpg"
//                        var f2=Environment.getExternalStorageDirectory().absolutePath + "/b.jpg"
//                        var f3=Environment.getExternalStorageDirectory().absolutePath + "/c.jpg"
//                        var f4=Environment.getExternalStorageDirectory().absolutePath + "/d.jpg"
//
//                        objectdtection.initCorrelationTracker()
//                        var arrayList=ArrayList<String>()
//                        arrayList.add(f1)
//                        arrayList.add(f2)
//                        arrayList.add(f3)
//                        arrayList.add(f4)
//
//                        var result=objectdtection.startTrack(arrayList)
//                        var text=""
//                        if(result!=null)
//                        {
//                            for(a in result){
//                                text+=a.toString()+"/n"
//                            }
//                        }
//                        var f1=Environment.getExternalStorageDirectory().absolutePath + "/a.jpg"
//                        var f2=Environment.getExternalStorageDirectory().absolutePath + "/b.jpg"
//                        var f3=Environment.getExternalStorageDirectory().absolutePath + "/c.jpg"
//                        var f4=Environment.getExternalStorageDirectory().absolutePath + "/d.jpg"
                        var datpath =
                            Environment.getExternalStorageDirectory().absolutePath + "/shape_predictor_68_face_landmarks.dat"

//                        var arrayList=ArrayList<String>()
//                        arrayList.add(f1)
//                        arrayList.add(f2)
//                        arrayList.add(f3)
//                        arrayList.add(f4)
                        var list = objectdtection.facelandmarkdetectionwithBitmap(bitmap, datpath)
//                        for (l in list) {
//                            Log.d("DlibforAndroid", l.toString())
//                        }
                        runOnUiThread {
                            faceview.bringToFront()
                            faceview.addFaceInfo(list)
                                loading.visibility = View.GONE
                        }
//                        var options=BitmapFactory.Options()
//                        options.inPurgeable=true
//                        options.inSampleSize=2
//                        var bitmap1= BitmapFactory.decodeFile(f1,options);
//                        var bitmap2= BitmapFactory.decodeFile(f2,options);
//                        var bitmap3= BitmapFactory.decodeFile(f3,options);
//
//                        objectdtection.initCorrelationTracker(true)
//
//                       var istarttrack=objectdtection.startTrack(bitmap1)
//                        if(istarttrack)
//                        {
//                            var r1=objectdtection.updatetrack(bitmap2)
//                            var r2=objectdtection.updatetrack(bitmap3)
//                            runOnUiThread {
//                                loading.visibility = View.GONE
//                                showtext.text = "$r1\n$r2"
//                            }
//                        }
//                        else runOnUiThread {
//                            loading.visibility = View.GONE
//                        }


                    }
                }.start()

//                jpegloader?.let {
//                    // sample
////        var statisticsAbstract= au.hao.and.dlibmodule.statistics.statisticsAbstract.init()
////        var a=ArrayList<Int>()
////        a.add(1477)
////        a.add(2445)
////        var b=ArrayList<Int>()
////        b.add(1454)
////        b.add(21111)
////        b.add(3)
////        b.add(4567)
////        sample_text.text=statisticsAbstract.getevent_correlation(2,3,1,10).toString()
//                    Log.d("theresultisss:", "gray:" + jpegloader?.isgray().toString())
//                    Log.d("theresultisss:", "rgb:" + jpegloader?.isrgb().toString())
//                }
            }.start()

    }

    /**
     * A native method that is implemented by the 'native-lib' native library,
     * which is packaged with this application.
     */


}
