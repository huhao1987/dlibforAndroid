#include <jni.h>
#include <stdio.h>      /* printf, NULL */
#include <stdlib.h>
#include <vector>
#include <android/log.h>

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

//Not be used
std::vector<jint> getintVector(JNIEnv *env,jobject vlist){
    jclass cls_arraylist=env->GetObjectClass(vlist);
    jmethodID araylist_get=env->GetMethodID(cls_arraylist,"get","(I)Ljava/lang/Object;");
    jmethodID arraylist_size = env->GetMethodID(cls_arraylist,"size","()I");
    jint len = env->CallIntMethod(vlist,arraylist_size);
    LOGD("get java ArrayList1 by C++ , then print it, size=%d/n",len);
    for(jint i=0;i<len;i++){
        jobject objinarr = env->CallObjectMethod(vlist,araylist_get,i);
        jclass cls_arr = env->GetObjectClass(objinarr);
        jmethodID num=env->GetMethodID(cls_arr,"int",)
    }


    jint len=0;
    len=env->CallIntMethod(vlist,java_util_ArrayList_size);
    std::vector<jint> result;
    result.reserve(len);
    for(jint i=0;i<len;i++){
        jint element= static_cast<jint>(env->CallIntMethod(vlist,java_util_ArrayList_get,i));
//        const char* pchars = env->GetStringUTFChars(element, nullptr);
        result.emplace_back(element);
    }
    return result;
}


