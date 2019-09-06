package au.hao.and.dlibforandroid

import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import au.hao.and.dlibmodule.Algorithms
import au.hao.and.dlibmodule.Dlib
import kotlinx.android.synthetic.main.activity_main.*

class MainActivity : AppCompatActivity() {

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)

        // sample
        var algorithms=Algorithms.init()
        sample_text.text=algorithms.getDifference_binomial_random_vars(1,2,3,4).toString()
    }

    /**
     * A native method that is implemented by the 'native-lib' native library,
     * which is packaged with this application.
     */


}
