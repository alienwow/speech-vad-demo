#include "com_baidu_speech_restapi_jniTest_FileCutUtil.h"
#include <stdio.h>

JNIEXPORT void JNICALL Java_com_baidu_speech_restapi_jniTest_FileCutUtil_finalize
  (JNIEnv * a, jobject b){
	printf("Wenhao.Wu1");
  }
JNIEXPORT jint JNICALL Java_com_baidu_speech_restapi_jniTest_FileCutUtil_setFile
  (JNIEnv * a, jobject b, jcharArray c, jcharArray d){
	printf("Wenhao.Wu2\n");
    // return 2;
  }