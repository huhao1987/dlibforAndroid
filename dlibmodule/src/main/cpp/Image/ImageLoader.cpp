#include <jni.h>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <sstream>
#include <vector>
#define DLIB_JPEG_SUPPORT
#include <dlib/image_io.h>

#include <android/log.h>

#include "../MathUtils.cpp"

using namespace dlib;
using namespace std;

#define  LOG_TAG    "DlibforAndroid"

#define  LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)
#define  LOGE(...)  __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)


jpeg_loader *jpegloader=NULL;
#define JPEGNAME(NAME)\
    Java_au_hao_and_dlibmodule_Image_Jpegloader_##NAME

    extern "C"
    JNIEXPORT void JNICALL
    JPEGNAME(initimage)(
            JNIEnv *env,
            jobject thiz,
            jstring filename) {
        std::string str = jstring2str(env,filename);
        jpegloader = new jpeg_loader(str.c_str());
    }
extern "C"
JNIEXPORT jboolean JNICALL
JPEGNAME(isgray)(
        JNIEnv *env,
        jobject thiz) {
        if(jpegloader==NULL)
        return JNI_FALSE;
        else{
            return jpegloader->is_gray();
        }
}
extern "C"
JNIEXPORT jboolean JNICALL
JPEGNAME(isrgb)(
        JNIEnv *env,
        jobject thiz) {
    if(jpegloader==NULL)
        return false;
    else{
        return jpegloader->is_rgb();
    }
}

