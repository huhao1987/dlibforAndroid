package au.hao.and.dlibforandroid

import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import au.hao.and.dlibmodule.Algorithms
import au.hao.and.dlibmodule.Dlib
import kotlinx.android.synthetic.main.activity_main.*
import java.util.*

class MainActivity : AppCompatActivity() {

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)

        // sample
        var algorithms=Algorithms.init()
        var a=ArrayList<Int>()
        a.add(1477)
        a.add(2445)
        var b=ArrayList<Int>()
        b.add(1454)
        b.add(21111)
        b.add(3)
        b.add(4567)
        sample_text.text=algorithms.correlation(a,b).toString()
    }

    /**
     * A native method that is implemented by the 'native-lib' native library,
     * which is packaged with this application.
     */


}
