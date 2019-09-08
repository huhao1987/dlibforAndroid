#include <jni.h>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <sstream>
#include <vector>

#include <android/log.h>
#include <dlib/matrix.h>
#include <dlib/statistics/statistics.h>
#include <dlib/geometry.h>

#include <MathUtils.cpp>
using namespace dlib;
using namespace std;

#define  LOG_TAG    "DlibforAndroid"

#define  LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)
#define  LOGE(...)  __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)
#define METHODNAME(NAME)\
    Java_au_hao_and_dlibmodule_Algorithms_##NAME

//binomial_random_vars_are_different
extern "C" JNIEXPORT double JNICALL
METHODNAME(binomialrandomvarsaredifferent)(
        JNIEnv *env,
        jobject /* this */,
        jstring k1s,jstring n1s,jstring k2s,jstring n2s) {
    unsigned long long k1=getUint64_t(env,k1s);
    unsigned long long n1=getUint64_t(env,n1s);
    unsigned long long k2=getUint64_t(env,k2s);
    unsigned long long n2=getUint64_t(env,n2s);
    return binomial_random_vars_are_different(k1,n1,k2,n2);;
}

//std::vector vectora;
//std::vector vectorb;
//
//extern "C"
//JNIEXPORT void JNICALL
//METHODNAME(setVectora)(
//        JNIEnv *env,
//        jobject,
//        int num,...
//        ){
//    va_list pvar;
//    va_start(pvar,num);
//    while (num>0){
//        vectora.emplace_back(va_arg(pvar,jint));
//    }
//    va_end(pvar);
//}
//
//extern "C"
//JNIEXPORT void JNICALL
//METHODNAME(setVectorb)(
//JNIEnv *env,
//jobject,
//int num,...
//){
//va_list pvar;
//va_start(pvar,num);
//while (num>0){
//vectora.emplace_back(va_arg(pvar,jint));
//}
//va_end(pvar);
//}
//correlation

extern "C"
JNIEXPORT double JNICALL
METHODNAME(correlation)(
        JNIEnv *env,
        jobject /* this */,
        jobject arraylist1,
        jobject arraylist2) {

    return NULL;
//        std::vector<jint> a=getintVector(env,arraylist1);
//        std::vector<jint> b=getintVector(env,arraylist2);
//    return correlation(a,b);
}



