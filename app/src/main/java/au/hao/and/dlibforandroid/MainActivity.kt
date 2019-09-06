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
        var a=Vector<Int>()
        a.addElement(1)
        a.addElement(2)
        sample_text.text=algorithms.correlation(a,a).toString()
    }

    /**
     * A native method that is implemented by the 'native-lib' native library,
     * which is packaged with this application.
     */


}
