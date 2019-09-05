#include <jni.h>
#include <string>

#include <iostream>
#include <dlib/matrix.h>
#include <sstream>

using namespace dlib;
using namespace std;

unsigned  long long Java_au_hao_and_dlibmodule_algorithms_getUint64_t( JNIEnv *env,jstring num){
    char *str=env->GetStringUTFChars(num,NULL);
    return strtoull(str.c_str());
}
extern "C" JNIEXPORT double JNICALL
Java_au_hao_and_dlibmodule_algorithms_isbinomial_randomSame(
        JNIEnv *env,
        jobject /* this */) {
    std::string hello = matrix_ex();
    return env->NewStringUTF(hello.c_str());
}


