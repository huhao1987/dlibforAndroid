#include <jni.h>
#include <stdio.h>      /* printf, NULL */
#include <stdlib.h>
#include <vector>
using namespace std;

static jclass java_util_ArrayList;
static jmethodID java_util_ArrayList_;
jmethodID java_util_ArrayList_size;
jmethodID java_util_ArrayList_get;
jmethodID java_util_ArrayList_add;
static thread_local JNIEnv* env;

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
std::vector<jint> getintVector(JNIEnv *env,jobject arraylst){
    jint len=0;
    len=env->CallIntMethod(arraylst,java_util_ArrayList_size);
    std::vector<jint> result;
    result.reserve(len);
    for(jint i=0;i<len;i++){
        jint element= static_cast<jint>(env->CallIntMethod(arraylst,java_util_ArrayList_get,i));
//        const char* pchars = env->GetStringUTFChars(element, nullptr);
        result.emplace_back(element);
    }
    return result;
}


