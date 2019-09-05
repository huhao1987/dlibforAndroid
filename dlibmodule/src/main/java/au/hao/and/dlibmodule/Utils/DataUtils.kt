package au.hao.and.dlibmodule.Utils

import kotlin.experimental.and

class DataUtils {
    companion object{
        fun getUint8(s: Short): Short {
            return (s and 0x00ff).toShort()
        }
        fun getUint16(i: Int): Int {
            return i and 0x0000ffff
        }
        fun getUint32(l: Long): Long {
            return l and -0x1
        }
    }
}