#include <jni.h>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <sstream>
#include <vector>

#include <dlib/image_io.h>
#include <dlib/image_processing.h>
#include <dlib/image_processing/object_detector.h>
#include <dlib/image_processing/generic_image.h>

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
correlation_tracker *corrtracker = NULL;
#define METHODNAME(NAME)\
    Java_au_hao_and_dlibmodule_Imageprocessing_ObjectDetection_##NAME

#define METHODOFTRACKNAME(NAME)\
    Java_au_hao_and_dlibmodule_Imageprocessing_CorrelationTracker_##NAME
//    Frontal_Face_detector
extern "C"
JNIEXPORT jobject JNICALL
METHODNAME(getfrontalfacedetector)(
        JNIEnv *env,
        jobject,
        jstring filename
) {
    std::string str = jstring2str(env, filename);
    jpegloader = new jpeg_loader(str.c_str());
    frontal_face_detector detector = get_frontal_face_detector();
    dlib::array2d<dlib::rgb_pixel> facearr;
    jpegloader->get_image(facearr);
//    pyramid_up(facearr);
    std::vector<dlib::rectangle> dets = detector(facearr);
    return getrecArrayList(env, dets);
}


////Object_detector
////TODo Not be finished
//extern "C"
//JNIEXPORT jobject JNICALL
//METHODNAME(ojbectdetector)(
//        JNIEnv *env,
//        jobject,
//        jstring filename
//) {
//
//    objectdetector = new object_detector();
//}

extern "C"
JNIEXPORT void JNICALL
METHODOFTRACKNAME(initcorrelationtracker)(
        JNIEnv *env,
        jobject,
        jstring filename
) {
    corrtracker = new correlation_tracker();
}

extern "C"
JNIEXPORT jobject JNICALL
METHODOFTRACKNAME(starttrack)(
        JNIEnv *env,
        jobject,
        jobject list) {
    std::vector<dlib::drectangle> result;
    if (corrtracker != NULL) {
        std::vector<std::string> vector=getStringVector(env,list);
        dlib::array2d<dlib::rgb_pixel> img;
        frontal_face_detector detector = get_frontal_face_detector();

        for(int i=0;i<vector.size();i++){
            drectangle d;
            load_image(img, vector[i].c_str());
            if(i==0)
            {
                std::vector<dlib::rectangle> dets = detector(img);
                dlib::rectangle det = dets[0];
                corrtracker->start_track(img, centered_rect(det, det.width(), det.height()));
                 d= corrtracker->get_position();
            }
            else{
                corrtracker->update(img);
                d = corrtracker->get_position();
            }
            result.push_back(d);
            LOGD("the face in %d: %d %d %d %d", i,d.area());
        }
    }
    jobject arraylist=getdrecArrayList(env,result);
    return arraylist;
}