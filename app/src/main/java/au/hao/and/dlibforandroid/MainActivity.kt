package au.hao.and.dlibforandroid

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
                loading.visibility= View.VISIBLE
                object:Thread(){
                    override fun run() {
                        var objectdtection = ObjectDetection.init()
//                       var arr= objectdtection.getfrontalfacedetector(Environment.getExternalStorageDirectory().absolutePath + "/a.jpg")
//                        var text=""
//                        for(a in arr){
//                            text+=a.toString()+"/n"
//                        }
                       var f1=Environment.getExternalStorageDirectory().absolutePath + "/a.jpg"
                        var f2=Environment.getExternalStorageDirectory().absolutePath + "/b.jpg"
                        var f3=Environment.getExternalStorageDirectory().absolutePath + "/c.jpg"
                        var f4=Environment.getExternalStorageDirectory().absolutePath + "/d.jpg"

                        objectdtection.initCorrelationTracker()
                        var arrayList=ArrayList<String>()
                        arrayList.add(f1)
                        arrayList.add(f2)
                        arrayList.add(f3)
                        arrayList.add(f4)

                        var isget=objectdtection.startTrack(arrayList)
                        if(isget)
                        runOnUiThread {
                            loading.visibility = View.GONE
//                            showtext.text = text
                        }
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
