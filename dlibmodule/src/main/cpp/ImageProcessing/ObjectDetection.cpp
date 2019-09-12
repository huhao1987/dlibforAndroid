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
#define METHODNAME(NAME)\
    Java_au_hao_and_dlibmodule_Imageprocessing_ObjectDetection_##NAME

extern "C"
JNIEXPORT jobject JNICALL
METHODNAME(getfrontalfacedetector)(
        JNIEnv *env,
        jobject,
        jstring filename
      ) {
    std::string str = jstring2str(env, filename);
    jpegloader =  new jpeg_loader(str.c_str());
    frontal_face_detector detector = get_frontal_face_detector();
    dlib::array2d<dlib::rgb_pixel> facearr;
    jpegloader->get_image(facearr);
//    pyramid_up(facearr);
    std::vector<dlib::rectangle> dets=detector(facearr);
    return getrecArrayList(env,dets);
}