#include <jni.h>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <sstream>
#include <vector>
#include <android/bitmap.h>


#include <dlib/image_io.h>
#include <dlib/image_processing/object_detector.h>
#include <dlib/image_processing/frontal_face_detector.h>

#include <android/log.h>

using namespace std;
using namespace dlib;

static thread_local JNIEnv *env;
#define  LOG_TAG    "DlibforAndroid"

#define RETANGLEMETHOD(NAME)\
    Java_au_hao_and_dlibmodule_Utils_DataUtils_##NAME
#define  LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)
#define  LOGE(...)  __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)


unsigned long long getUint64_t(JNIEnv *env, jstring num) {
    const char *str = env->GetStringUTFChars(num, NULL);
    return strtoull(str, NULL, 0);
}

std::string jstring2str(JNIEnv *env, jstring jstr) {
    char *rtn = NULL;
    jclass clsstring = env->FindClass("java/lang/String");
    jstring strencode = env->NewStringUTF("GB2312");
    jmethodID mid = env->GetMethodID(clsstring, "getBytes", "(Ljava/lang/String;)[B");
    jbyteArray barr = (jbyteArray) env->CallObjectMethod(jstr, mid, strencode);
    jsize alen = env->GetArrayLength(barr);
    jbyte *ba = env->GetByteArrayElements(barr, JNI_FALSE);
    if (alen > 0) {
        rtn = (char *) malloc(alen + 1);
        memcpy(rtn, ba, alen);
        rtn[alen] = 0;
    }
    env->ReleaseByteArrayElements(barr, ba, 0);
    std::string stemp(rtn);
    free(rtn);
    return stemp;
}



std::vector<jobject> getVector(JNIEnv *env, jobject vlist) {
    jclass cls_arraylist = env->GetObjectClass(vlist);
    jmethodID araylist_get = env->GetMethodID(cls_arraylist, "get", "(I)Ljava/lang/Object;");
    jmethodID arraylist_size = env->GetMethodID(cls_arraylist, "size", "()I");
    jint len = env->CallIntMethod(vlist, arraylist_size);
    LOGD("get java ArrayList1 by C++ , then print it, size=%d", len);
    std::vector<jobject> result;
    for (jint i = 0; i < len; i++) {
        jobject objinarr = env->CallObjectMethod(vlist, araylist_get, i);
//        jclass cls_arr = env->GetObjectClass(objinarr);
//        jmethodID getnum = env->GetMethodID(cls_arr, "getName", "Ljava/lang/Object;");
//        jobject num = env->CallObjectMethod(objinarr, getnum);
        result.push_back(objinarr);
    }
    return result;
}

//Get int vector
std::vector<int> getintVector(JNIEnv *env, jobject vlist) {
    jclass cls_arraylist = env->GetObjectClass(vlist);
    jmethodID araylist_get = env->GetMethodID(cls_arraylist, "get", "(I)Ljava/lang/Object;");
    jmethodID arraylist_size = env->GetMethodID(cls_arraylist, "size", "()I");
    jint len = env->CallIntMethod(vlist, arraylist_size);
    LOGD("get java ArrayList1 by C++ , then print it, size=%d/n", len);
    std::vector<int> result;
    for (jint i = 0; i < len; i++) {
        jobject objinarr = env->CallObjectMethod(vlist, araylist_get, i);
        jclass cls_arr = env->GetObjectClass(objinarr);
        jmethodID getnum = env->GetMethodID(cls_arr, "intValue", "()I");
        jint num = env->CallIntMethod(objinarr, getnum);
        result.push_back(num);
    }
    return result;
}
std::vector<std::string> getStringVector(JNIEnv *env, jobject vlist) {
    jclass cls_arraylist = env->GetObjectClass(vlist);
    jmethodID araylist_get = env->GetMethodID(cls_arraylist, "get", "(I)Ljava/lang/Object;");
    jmethodID arraylist_size = env->GetMethodID(cls_arraylist, "size", "()I");
    jint len = env->CallIntMethod(vlist, arraylist_size);
    LOGD("get java ArrayList1 by C++ , then print it, size=%d", len);
    std::vector<std::string> result;
    for (jint i = 0; i < len; i++) {
        jstring objinarr = (jstring)env->CallObjectMethod(vlist, araylist_get, i);
//        jclass cls_arr = env->GetObjectClass(objinarr);
//        jmethodID getName = env->GetMethodID(cls_arr, "getString", "()Ljava/lang/String;");
//        jstring name = (jstring)env->CallObjectMethod(objinarr, getName);
        std::string s=jstring2str(env,objinarr);
        result.push_back(s);
    }
    return result;
}

//set retangle as java object
jobject getrectangle(
        JNIEnv *env,
        rectangle rectangle) {
    jclass retangleclass = env->FindClass( "au/hao/and/dlibmodule/Objects/Rectangle");
    jmethodID retmethod = env->GetMethodID(retangleclass, "<init>", "()V");
    jfieldID left = env->GetFieldID(retangleclass, "left", "J");
    jfieldID top = env->GetFieldID(retangleclass, "top", "J");
    jfieldID right = env->GetFieldID(retangleclass, "right", "J");
    jfieldID bottom = env->GetFieldID(retangleclass, "bottom", "J");
    jfieldID width = env->GetFieldID(retangleclass, "width", "J");
    jfieldID height = env->GetFieldID(retangleclass, "height", "J");
    jfieldID area = env->GetFieldID(retangleclass, "area", "J");
    jobject newretangle = env->NewObject(retangleclass, retmethod);
    env->SetLongField(newretangle, left, rectangle.left());
    env->SetLongField(newretangle, top, rectangle.top());
    env->SetLongField(newretangle, right, rectangle.right());
    env->SetLongField(newretangle, bottom, rectangle.bottom());
    env->SetLongField(newretangle, width, rectangle.width());
    env->SetLongField(newretangle, height, rectangle.height());
    env->SetLongField(newretangle, area, rectangle.area());
    return newretangle;
}

jobject getdrectangle(
        JNIEnv *env,
        drectangle rectangle) {
    jclass retangleclass = env->FindClass( "au/hao/and/dlibmodule/Objects/Drectangle");
    jmethodID retmethod = env->GetMethodID(retangleclass, "<init>", "()V");
    jfieldID left = env->GetFieldID(retangleclass, "left", "D");
    jfieldID top = env->GetFieldID(retangleclass, "top", "D");
    jfieldID right = env->GetFieldID(retangleclass, "right", "D");
    jfieldID bottom = env->GetFieldID(retangleclass, "bottom", "D");
    jfieldID width = env->GetFieldID(retangleclass, "width", "D");
    jfieldID height = env->GetFieldID(retangleclass, "height", "D");
    jfieldID area = env->GetFieldID(retangleclass, "area", "D");
    jobject newretangle = env->NewObject(retangleclass, retmethod);
    env->SetDoubleField(newretangle, left, rectangle.left());
    env->SetDoubleField(newretangle, top, rectangle.top());
    env->SetDoubleField(newretangle, right, rectangle.right());
    env->SetDoubleField(newretangle, bottom, rectangle.bottom());
    env->SetDoubleField(newretangle, width, rectangle.width());
    env->SetDoubleField(newretangle, height, rectangle.height());
    env->SetDoubleField(newretangle, area, rectangle.area());
    return newretangle;
}

//set retangle as java object
jobject getPoint(
        JNIEnv *env,
        point& p) {
    jclass pointclass = env->FindClass( "au/hao/and/dlibmodule/Objects/Point");
    jmethodID pointmethod = env->GetMethodID(pointclass, "<init>", "()V");
    jfieldID x = env->GetFieldID(pointclass, "x", "J");
    jfieldID y = env->GetFieldID(pointclass, "y", "J");
    jfieldID z = env->GetFieldID(pointclass, "z", "J");
    jobject newpoint = env->NewObject(pointclass, pointmethod);

    env->SetLongField(newpoint, x, p.x());
    env->SetLongField(newpoint, y, p.y());
    env->SetLongField(newpoint, z, p.z());
    return newpoint;
}
jobject getrecArrayList(JNIEnv *env, std::vector<dlib::rectangle> vector) {
    //ArrayList Object
    jclass cls_ArrayList = env->FindClass("java/util/ArrayList");
    jmethodID construct = env->GetMethodID(cls_ArrayList, "<init>", "()V");
    jobject obj_ArrayList = env->NewObject(cls_ArrayList, construct, "");
    jmethodID arrayList_add = env->GetMethodID(cls_ArrayList, "add", "(Ljava/lang/Object;)Z");
    for (auto v :vector) {
        env->CallBooleanMethod(obj_ArrayList, arrayList_add, getrectangle(env, v));
    }
    return obj_ArrayList;
}

jobject getdrecArrayList(JNIEnv *env, std::vector<dlib::drectangle> vector) {
    //ArrayList Object
    jclass cls_ArrayList = env->FindClass("java/util/ArrayList");
    jmethodID construct = env->GetMethodID(cls_ArrayList, "<init>", "()V");
    jobject obj_ArrayList = env->NewObject(cls_ArrayList, construct, "");
    jmethodID arrayList_add = env->GetMethodID(cls_ArrayList, "add", "(Ljava/lang/Object;)Z");
    for (auto v :vector) {
        env->CallBooleanMethod(obj_ArrayList, arrayList_add, getdrectangle(env, v));
    }
    return obj_ArrayList;
}
//arraylist for rectangle
jobject getrecarrArrayList(JNIEnv *env, std::vector<std::vector<dlib::rectangle>> vector2dlist) {
    //ArrayList Object
    jclass cls_ArrayList = env->FindClass("java/util/ArrayList");
    jmethodID construct = env->GetMethodID(cls_ArrayList, "<init>", "()V");
    jobject obj_ArrayList = env->NewObject(cls_ArrayList, construct, "");
    jmethodID arrayList_add = env->GetMethodID(cls_ArrayList, "add", "(Ljava/lang/Object;)Z");
    for (auto vector :vector2dlist) {
            env->CallBooleanMethod(obj_ArrayList, arrayList_add, getrecArrayList(env, vector));
    }
    return obj_ArrayList;
}

//arraylist for drectangle
jobject getrecarrArrayList(JNIEnv *env, std::vector<std::vector<dlib::drectangle>> vector2dlist) {
    //ArrayList Object
    jclass cls_ArrayList = env->FindClass("java/util/ArrayList");
    jmethodID construct = env->GetMethodID(cls_ArrayList, "<init>", "()V");
    jobject obj_ArrayList = env->NewObject(cls_ArrayList, construct, "");
    jmethodID arrayList_add = env->GetMethodID(cls_ArrayList, "add", "(Ljava/lang/Object;)Z");
    for (auto vector :vector2dlist) {
        env->CallBooleanMethod(obj_ArrayList, arrayList_add, getdrecArrayList(env, vector));
    }
    return obj_ArrayList;
}


jobject getpointArrayList(JNIEnv *env, full_object_detection shape) {
    //ArrayList Object
    jclass cls_ArrayList = env->FindClass("java/util/ArrayList");
    jmethodID construct = env->GetMethodID(cls_ArrayList, "<init>", "()V");
    jobject obj_ArrayList = env->NewObject(cls_ArrayList, construct, "");
    jmethodID arrayList_add = env->GetMethodID(cls_ArrayList, "add", "(Ljava/lang/Object;)Z");
    for (long n=0;n<shape.num_parts();n++) {
        env->CallBooleanMethod(obj_ArrayList, arrayList_add, getPoint(env, shape.part(n)));
    }
    return obj_ArrayList;
}

/**
 * Convert Bitmap to array2d
*From internet
 */
void convertBitmapToArray2d(JNIEnv* env,
                            jobject bitmap,
                            array2d<rgb_pixel>& out) {
    AndroidBitmapInfo bitmapInfo;
    void* pixels;
    int state;

    if (0 > (state = AndroidBitmap_getInfo(env, bitmap, &bitmapInfo))) {
        LOGD("L%d: AndroidBitmap_getInfo() failed! error=%d", __LINE__, state);
        return;
    } else if (bitmapInfo.format != ANDROID_BITMAP_FORMAT_RGBA_8888) {
        LOGD("L%d: Bitmap format is not RGB_565!", __LINE__);
    }

// Lock the bitmap for copying the pixels safely.
    if (0 > (state = AndroidBitmap_lockPixels(env, bitmap, &pixels))) {
        LOGD("L%d: AndroidBitmap_lockPixels() failed! error=%d", __LINE__, state);
        return;
    }

    LOGD("L%d: info.width=%d, info.height=%d", __LINE__, bitmapInfo.width, bitmapInfo.height);
    out.set_size((long) bitmapInfo.height, (long) bitmapInfo.width);

    char* line = (char*) pixels;
    for (int h = 0; h < bitmapInfo.height; ++h) {
        for (int w = 0; w < bitmapInfo.width; ++w) {
            uint32_t* color = (uint32_t*) (line + 4 * w);

            out[h][w].red = (unsigned char) (0xFF & ((*color) >> 24));
            out[h][w].green = (unsigned char) (0xFF & ((*color) >> 16));
            out[h][w].blue = (unsigned char) (0xFF & ((*color) >> 8));
        }

        line = line + bitmapInfo.stride;
    }

// Unlock the bitmap.
    AndroidBitmap_unlockPixels(env, bitmap);
}