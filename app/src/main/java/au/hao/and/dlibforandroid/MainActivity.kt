package au.hao.and.dlibforandroid

import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.os.Environment
import android.util.Log
import au.hao.and.dlibmodule.Image.ImageLoader
import au.hao.and.dlibmodule.Image.Jpegloader
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
                var jpegloader = ImageLoader.init()
                    .Jpegloader(Environment.getExternalStorageDirectory().absolutePath + "/a.jpg")
                jpegloader?.let {
                    // sample
//        var statisticsAbstract= au.hao.and.dlibmodule.statistics.statisticsAbstract.init()
//        var a=ArrayList<Int>()
//        a.add(1477)
//        a.add(2445)
//        var b=ArrayList<Int>()
//        b.add(1454)
//        b.add(21111)
//        b.add(3)
//        b.add(4567)
//        sample_text.text=statisticsAbstract.getevent_correlation(2,3,1,10).toString()
                    Log.d("theresultisss:", "gray:" + jpegloader?.isgray().toString())
                    Log.d("theresultisss:", "rgb:" + jpegloader?.isrgb().toString())
                }
            }.start()

    }

    /**
     * A native method that is implemented by the 'native-lib' native library,
     * which is packaged with this application.
     */


}
