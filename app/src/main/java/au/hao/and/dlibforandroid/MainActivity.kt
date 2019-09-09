package au.hao.and.dlibforandroid

import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.util.Log
import au.hao.and.dlibmodule.Image.ImageLoader
import au.hao.and.dlibmodule.Image.Jpegloader
import au.hao.and.dlibmodule.statistics.statisticsAbstract
import kotlinx.android.synthetic.main.activity_main.*
import java.util.*

class MainActivity : AppCompatActivity() {

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)

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
            var jpegloader=ImageLoader.init().Jpegloader("/sdcard/a.jpg")
            Log.d("theresultisss:",jpegloader?.isgray().toString())
    }

    /**
     * A native method that is implemented by the 'native-lib' native library,
     * which is packaged with this application.
     */


}
