#include <jni.h>
#include <string>
#include <stdio.h>      /* printf, NULL */
#include <stdlib.h>
using namespace std;

unsigned  long long getUint64_t( JNIEnv *env,jstring num){
    const char *str=env->GetStringUTFChars(num,NULL);
    return strtoull(str,NULL,0);
}