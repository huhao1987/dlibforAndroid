#include <jni.h>
#include <stdio.h>      /* printf, NULL */
#include <stdlib.h>
#include <vector>
#include <android/log.h>
#include <cstdlib>
#include <string>

using namespace std;

static jclass java_util_ArrayList;
static jmethodID java_util_ArrayList_;
jmethodID java_util_ArrayList_size;
jmethodID java_util_ArrayList_get;
jmethodID java_util_ArrayList_add;
static thread_local JNIEnv* env;
#define  LOG_TAG    "DlibforAndroid"

#define  LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)
#define  LOGE(...)  __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)
void init() {
    java_util_ArrayList      = static_cast<jclass>(env->NewGlobalRef(env->FindClass("java/util/ArrayList")));
    java_util_ArrayList_     = env->GetMethodID(java_util_ArrayList, "<init>", "(I)V");
    java_util_ArrayList_size = env->GetMethodID (java_util_ArrayList, "size", "()I");
    java_util_ArrayList_get  = env->GetMethodID(java_util_ArrayList, "get", "(I)Ljava/lang/Object;");
    java_util_ArrayList_add  = env->GetMethodID(java_util_ArrayList, "add", "(Ljava/lang/Object;)Z");
}
unsigned long long getUint64_t( JNIEnv *env,jstring num){
    const char *str=env->GetStringUTFChars(num,NULL);
    return strtoull(str,NULL,0);
}

std::string jstring2str(JNIEnv* env, jstring jstr)
{
    char*   rtn   =   NULL;
    jclass   clsstring   =   env->FindClass("java/lang/String");
    jstring   strencode   =   env->NewStringUTF("GB2312");
    jmethodID   mid   =   env->GetMethodID(clsstring,   "getBytes",   "(Ljava/lang/String;)[B");
    jbyteArray   barr=   (jbyteArray)env->CallObjectMethod(jstr,mid,strencode);
    jsize   alen   =   env->GetArrayLength(barr);
    jbyte*   ba   =   env->GetByteArrayElements(barr,JNI_FALSE);
    if(alen   >   0)
    {
        rtn   =   (char*)malloc(alen+1);
        memcpy(rtn,ba,alen);
        rtn[alen]=0;
    }
    env->ReleaseByteArrayElements(barr,ba,0);
    std::string stemp(rtn);
    free(rtn);
    return   stemp;
}
std::vector<jobject> getVector(JNIEnv *env,jobject vlist) {
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
std::vector<int> getintVector(JNIEnv *env,jobject vlist){
    jclass cls_arraylist=env->GetObjectClass(vlist);
    jmethodID araylist_get=env->GetMethodID(cls_arraylist,"get","(I)Ljava/lang/Object;");
    jmethodID arraylist_size = env->GetMethodID(cls_arraylist,"size","()I");
    jint len = env->CallIntMethod(vlist,arraylist_size);
    LOGD("get java ArrayList1 by C++ , then print it, size=%d/n",len);
    std::vector<int> result;
    for(jint i=0;i<len;i++){
        jobject objinarr = env->CallObjectMethod(vlist,araylist_get,i);
        jclass cls_arr = env->GetObjectClass(objinarr);
        jmethodID getnum=env->GetMethodID(cls_arr,"intValue","()I");
        jint num=env->CallIntMethod(objinarr,getnum);
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


