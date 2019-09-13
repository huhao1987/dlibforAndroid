#include <jni.h>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <sstream>
#include <vector>


#include <dlib/image_io.h>

#include <dlib/image_processing/frontal_face_detector.h>

#include <android/log.h>

using namespace std;
using namespace dlib;

static jclass java_util_ArrayList;
static jmethodID java_util_ArrayList_;
jmethodID java_util_ArrayList_size;
jmethodID java_util_ArrayList_get;
jmethodID java_util_ArrayList_add;
static thread_local JNIEnv *env;
#define  LOG_TAG    "DlibforAndroid"

#define RETANGLEMETHOD(NAME)\
    Java_au_hao_and_dlibmodule_Utils_DataUtils_##NAME
#define  LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)
#define  LOGE(...)  __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)

void init() {
    java_util_ArrayList = static_cast<jclass>(env->NewGlobalRef(
            env->FindClass("java/util/ArrayList")));
    java_util_ArrayList_ = env->GetMethodID(java_util_ArrayList, "<init>", "(I)V");
    java_util_ArrayList_size = env->GetMethodID(java_util_ArrayList, "size", "()I");
    java_util_ArrayList_get = env->GetMethodID(java_util_ArrayList, "get", "(I)Ljava/lang/Object;");
    java_util_ArrayList_add = env->GetMethodID(java_util_ArrayList, "add", "(Ljava/lang/Object;)Z");
}

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



//    jint len=0;
//    len=env->CallIntMethod(vlist,java_util_ArrayList_size);
//    std::vector<jint> result;
//    result.reserve(len);
//    for(jint i=0;i<len;i++){
//        jint element= static_cast<jint>(env->CallIntMethod(vlist,java_util_ArrayList_get,i));
////        const char* pchars = env->GetStringUTFChars(element, nullptr);
//        result.emplace_back(element);
//    }
//    return NULL;
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