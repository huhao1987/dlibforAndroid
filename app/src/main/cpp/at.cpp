#include <jni.h>
#include <string>

extern "C" JNIEXPORT jstring JNICALL
Java_au_hao_and_dlibforandroid_MainActivity_stringFroget(
        JNIEnv *env,
        jobject /* this */) {
    std::string hello = "Hello from at";
    return env->NewStringUTF(hello.c_str());
}
