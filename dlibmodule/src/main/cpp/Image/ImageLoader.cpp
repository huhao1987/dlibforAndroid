#include <jni.h>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <sstream>
#include <vector>

#define DLIB_JPEG_SUPPORT

#include <dlib/image_io.h>

#include <dlib/image_processing/frontal_face_detector.h>

#include <android/log.h>

#include "../MathUtils.cpp"

using namespace dlib;
using namespace std;

#define  LOG_TAG    "DlibforAndroid"

#define  LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)
#define  LOGE(...)  __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)


jpeg_loader *jpegloader = NULL;
#define JPEGNAME(NAME)\
    Java_au_hao_and_dlibmodule_Image_Jpegloader_##NAME

extern "C"
JNIEXPORT void JNICALL
JPEGNAME(initimage)(
        JNIEnv *env,
        jobject thiz,
        jstring filename) {
    std::string str = jstring2str(env, filename);
    jpegloader = new jpeg_loader(str.c_str());
}

extern "C"
JNIEXPORT jboolean JNICALL
JPEGNAME(isgray)(
        JNIEnv *env,
        jobject thiz) {
    if (jpegloader == NULL) {
        return JNI_FALSE;
    } else {
        return jpegloader->is_gray();
    }
}
extern "C"
JNIEXPORT jboolean JNICALL
JPEGNAME(isrgb)(
        JNIEnv *env,
        jobject thiz) {
    if (jpegloader == NULL)
        return JNI_FALSE;
    else {
        return jpegloader->is_rgb();
    }
}

dlib::array2d<dlib::rgb_pixel> getJpegimage(JNIEnv *env) {
    if (jpegloader != NULL) {
        dlib::array2d<dlib::rgb_pixel> arr2d;
        jpegloader->get_image(arr2d);
        return arr2d;
    }
}

dlib::array2d<dlib::rgb_pixel> getJpegimage(JNIEnv *env, dlib::array2d<dlib::rgb_pixel> arr2d) {
    if (jpegloader != NULL){
        jpegloader->get_image(arr2d);
        return arr2d;
    }
}

extern "C"
JNIEXPORT void JNICALL
JPEGNAME(release)(
        JNIEnv *env,
        jobject thiz) {
    if (jpegloader == NULL)
        return;
    else {
        jpegloader = NULL;
    }
}

dlib::array2d<dlib::rgb_pixel>
loadbmp(JNIEnv *env, dlib::array2d<dlib::rgb_pixel> arr2d, std::string filename) {
    dlib::load_bmp(arr2d, filename.c_str());
    return arr2d;
}

dlib::array2d<dlib::rgb_pixel>
loadimage(JNIEnv *env, dlib::array2d<dlib::rgb_pixel> arr2d, std::string filename) {
    dlib::load_image(arr2d, filename.c_str());
    return arr2d;
}
