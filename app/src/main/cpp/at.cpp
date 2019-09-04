#include <jni.h>
#include <string>

#include <native-lib.cpp>



extern "C" JNIEXPORT jstring JNICALL
Java_au_hao_and_dlibforandroid_MainActivity_stringFroget(
        JNIEnv *env,
        jobject /* this */) {
    std::string hello = matrix_ex();
    return env->NewStringUTF(hello.c_str());
}
