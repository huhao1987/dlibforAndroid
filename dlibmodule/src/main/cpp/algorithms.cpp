#include <jni.h>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <sstream>

#include <dlib/matrix.h>
#include <dlib/statistics/statistics.h>

#include <MathUtils.cpp>
using namespace dlib;
using namespace std;

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


