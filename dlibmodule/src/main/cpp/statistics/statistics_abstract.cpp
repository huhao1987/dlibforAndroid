#include <jni.h>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <sstream>
#include <vector>

#include <android/log.h>
#include "../dlib/matrix.h"
#include "../dlib/statistics/statistics.h"
#include "../dlib/geometry.h"

#include "../MathUtils.cpp"

using namespace dlib;
using namespace std;

#define  LOG_TAG    "DlibforAndroid"

#define  LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)
#define  LOGE(...)  __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)
#define METHODNAME(NAME)\
    Java_au_hao_and_dlibmodule_statistics_statisticsAbstract_##NAME

//binomial_random_vars_are_different
extern "C" JNIEXPORT double JNICALL
METHODNAME(binomialrandomvarsaredifferent)(
        JNIEnv *env,
        jobject /* this */,
        jstring k1s, jstring n1s, jstring k2s, jstring n2s) {
    unsigned long long k1 = getUint64_t(env, k1s);
    unsigned long long n1 = getUint64_t(env, n1s);
    unsigned long long k2 = getUint64_t(env, k2s);
    unsigned long long n2 = getUint64_t(env, n2s);
    return binomial_random_vars_are_different(k1, n1, k2, n2);;
}

extern "C"
JNIEXPORT double JNICALL
METHODNAME(correlation)(
        JNIEnv *env,
        jobject /* this */,
        jobject arraylist1,
        jobject arraylist2) {
//    getintVector(env,arraylist1);
//    return NULL;
    std::vector<int> a = getintVector(env, arraylist1);
    std::vector<int> b = getintVector(env, arraylist2);
    return correlation(a, b);
}

extern "C"
JNIEXPORT double JNICALL
METHODNAME(meansignagreement)(
        JNIEnv *env,
        jobject /* this */,
        jobject arraylist1,
        jobject arraylist2) {
//    getintVector(env,arraylist1);
//    return NULL;
    std::vector<int> a = getintVector(env, arraylist1);
    std::vector<int> b = getintVector(env, arraylist2);
    return mean_sign_agreement(a, b);
}

extern "C"
JNIEXPORT jdouble JNICALL
METHODNAME(covariance)(
        JNIEnv *env,
        jobject,
        jobject a1,
        jobject a2) {
    std::vector<int> a = getintVector(env, a1);
    std::vector<int> b = getintVector(env, a2);
    return covariance(a, b);

}

extern "C"
JNIEXPORT jdouble JNICALL
METHODNAME(r1squared)(
        JNIEnv *env,
        jobject,
        jobject a1,
        jobject a2) {
    std::vector<int> a = getintVector(env, a1);
    std::vector<int> b = getintVector(env, a2);
    return r_squared(a, b);
}

extern "C"
JNIEXPORT jdouble JNICALL
METHODNAME(meansquarederror)(
        JNIEnv *env,
        jobject,
        jobject a1,
        jobject a2) {
    std::vector<int> a = getintVector(env, a1);
    std::vector<int> b = getintVector(env, a2);
    return mean_squared_error(a, b);
}
extern "C"
JNIEXPORT jdouble JNICALL
METHODNAME(eventcorrelation)(
        JNIEnv *env,
        jobject,
        jstring a_countstr,
        jstring b_countstr,
        jstring ab_countstr,
        jstring total_num_observationsstr) {
    unsigned long long a_count = getUint64_t(env, a_countstr);
    unsigned long long b_count = getUint64_t(env, b_countstr);
    unsigned long long ab_count = getUint64_t(env, ab_countstr);
    unsigned long long total_num_observations = getUint64_t(env, total_num_observationsstr);
    return event_correlation(a_count,b_count,ab_count,total_num_observations);
}

