package au.hao.and.dlibforandroid

import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import au.hao.and.dlibmodule.Algorithms
import au.hao.and.dlibmodule.Dlib
import kotlinx.android.synthetic.main.activity_main.*
import java.util.*
import kotlin.collections.ArrayList

class MainActivity : AppCompatActivity() {

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)

        // sample
        var algorithms=Algorithms.init()
        var a=ArrayList<Int>()
        a.add(1)
        a.add(2)
        var b=ArrayList<Int>()
        b.add(1)
        b.add(2)
        b.add(3)
        sample_text.text=algorithms.correlation(a,b).toString()
    }

    /**
     * A native method that is implemented by the 'native-lib' native library,
     * which is packaged with this application.
     */


}
