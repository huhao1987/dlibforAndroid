package au.hao.and.dlibforandroid

import android.content.Context
import android.graphics.BitmapFactory
import android.graphics.Matrix
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
import android.opengl.ETC1.getHeight
import android.opengl.ETC1.getWidth
import android.content.Context.WINDOW_SERVICE
import android.graphics.Bitmap
import androidx.core.content.ContextCompat.getSystemService
import android.view.WindowManager
import androidx.core.app.ComponentActivity
import androidx.core.app.ComponentActivity.ExtraData
import android.icu.lang.UCharacter.GraphemeClusterBreak.T
import com.otaliastudios.cameraview.CameraListener
import com.otaliastudios.cameraview.PictureResult
import com.otaliastudios.cameraview.frame.Frame
import com.otaliastudios.cameraview.frame.FrameProcessor
import java.nio.ByteBuffer


class MainActivity : AppCompatActivity() {
    private var currdata:ByteArray?=null
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)
        val wm = getSystemService(Context.WINDOW_SERVICE) as WindowManager
        val width = wm.defaultDisplay.width
        val height = wm.defaultDisplay.height
        AndPermission.with(this)
            .runtime()
            .permission(Permission.READ_EXTERNAL_STORAGE)
            .onGranted { permissions ->
                loading.visibility = View.VISIBLE
                cameraview.setSnapshotMaxWidth(width)
                cameraview.setSnapshotMaxHeight(height)
                cameraview.setLifecycleOwner(this)
                cameraview.addFrameProcessor(object:FrameProcessor{
                    override fun process(frame: Frame) {
                        currdata=frame.data
                    }
                })
                takephoto.setOnClickListener {
                    var bitmap=Bitmap.createBitmap(width,height,Bitmap.Config.ARGB_8888)
                    var buffer=ByteBuffer.wrap(currdata)
                    buffer.position()
                    bitmap.copyPixelsFromBuffer(buffer)
                    displayview.setImageBitmap(bitmap)
                }
//                cameraview.addCameraListener(object: CameraListener() {
//                    override fun onPictureTaken(result: PictureResult) {
//                        super.onPictureTaken(result)
//                    }
//                })
                object : Thread() {
                    override fun run() {
                        var objectdtection = ObjectDetection.init()
                        var filePath =
                            Environment.getExternalStorageDirectory().absolutePath + "/a.jpg";
                        var options = BitmapFactory.Options()
                        options.inPreferredConfig=Bitmap.Config.ARGB_8888
//                        options.inSampleSize=10
                        var bitmap = BitmapFactory.decodeFile(filePath, options)
                        var bw=bitmap.width
                        var bh=bitmap.height
                        var matrix=Matrix()

                        var a=width.toFloat()/bw
                        var b=height.toFloat()/bh
                        scale=Math.min((width.toFloat()/bw),height.toFloat()/bh)
                        Log.d("theviewisss::","$width $height $a $b $scale")


                        matrix.postRotate(-90f)
                        matrix.postScale(scale!!,scale!!)
                        var newbitmap=Bitmap.createBitmap(bitmap,0,0,bw,bh,matrix,true)
                        runOnUiThread {
                            displayview.setImageBitmap(newbitmap)
                        }
//                       var arr= objectdtection.getfrontalfacewithbitmap(newbitmap)
                        var datpath =
                            Environment.getExternalStorageDirectory().absolutePath + "/shape_predictor_68_face_landmarks.dat"
                        var list = objectdtection.facelandmarkdetectionwithBitmap(newbitmap, datpath)
                        runOnUiThread {
                            faceview.bringToFront()
                            faceview.addFaceInfo(list)
                            loading.visibility = View.GONE
                        }
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

//                        var arrayList=ArrayList<String>()
//                        arrayList.add(f1)
//                        arrayList.add(f2)
//                        arrayList.add(f3)
//                        arrayList.add(f4)
//                        for (l in list) {
//                            Log.d("DlibforAndroid", l.toString())
//                        }
//                        runOnUiThread {
//                            faceview.bringToFront()
//                            faceview.addFaceInfo(arr)
//                                loading.visibility = View.GONE
//                        }
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

    override fun onPause() {
        super.onPause()
    }
    companion object{
        var scale:Float?=null
    }
}
