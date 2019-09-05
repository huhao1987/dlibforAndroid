package au.hao.and.dlibmodule

class Dlib {
    external fun base64(a:String):String

    companion object {

        // Used to load the 'native-lib' library on application startup.
        init {
            System.loadLibrary("native-lib")
        }
    }
}

