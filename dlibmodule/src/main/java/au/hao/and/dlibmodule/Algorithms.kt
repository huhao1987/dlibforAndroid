package au.hao.and.dlibmodule

import java.util.*
import kotlin.experimental.and

class Algorithms {
    external fun binomialrandomvarsaredifferent(k1:String,n1:String,k2:String,n2:String):Double
    external fun correlation(a:Vector<Int>,b:Vector<Int>):Double

    fun getDifference_binomial_random_vars(k1:Int,n1:Int,k2:Int,n2:Int):Double{
        return binomialrandomvarsaredifferent(k1.toString(),n1.toString(),k2.toString(),n2.toString())
    }

    private fun initlib(){
        System.loadLibrary("algorithms")
    }
    companion object{
        var algorithms:Algorithms?=null

        fun init():Algorithms{
            if(algorithms==null)
            {
                algorithms= Algorithms()
                algorithms!!.initlib()
            }
            return algorithms!!
        }
    }
}