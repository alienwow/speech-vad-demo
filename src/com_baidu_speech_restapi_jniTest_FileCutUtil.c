// FileCut.cpp: 定义 DLL 应用程序的导出函数。
//
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include "stdafx.h"
#include "../thirdparty/webrtc/common_audio/vad/include/webrtc_vad.h"
#include "simple_vad.h"
#include "period_format.h"
#include "file_cut.h"
#include "common.h"
#include "com_baidu_speech_restapi_jniTest_FileCutUtil.h"
// 16000 采样率 10ms，  大小 = 160 * 16bits/8 = 320字节 ,

int run(FILE *fp, simple_vad *vad, struct cut_info *cut);
int add_period_activity(struct periods *per, int is_active, int is_last);

JNIEXPORT jint JNICALL Java_com_baidu_speech_restapi_jniTest_FileCutUtil_setFile
  (JNIEnv * env
  , jobject obj
  , jcharArray fileName_Java
  , jcharArray output_filename_prefix_Java
  , jcharArray output_dir_Java) {
    //filename
    jchar* array = (*env)->GetCharArrayElements(env,fileName_Java, JNI_FALSE);
    uint32_t arraysize = (*env)->GetArrayLength(env, fileName_Java);
    char filename[arraysize+1];   
    for(int i = 0; i < arraysize; i++){
        filename[i] = array[i];   
    }   
    filename[arraysize] = '\0';

    //output_filename_prefix
    jchar* array1 = (*env)->GetCharArrayElements(env,output_filename_prefix_Java, JNI_FALSE);
    uint32_t arraysize1 = (*env)->GetArrayLength(env, output_filename_prefix_Java);
    char output_filename_prefix[arraysize1+1];   
    for(int i = 0; i < arraysize1; i++){
        output_filename_prefix[i] = array1[i];   
    }   
    output_filename_prefix[arraysize1] = '\0';

    //output_dir
    jchar* array2 = (*env)->GetCharArrayElements(env,output_dir_Java, JNI_FALSE);
    uint32_t arraysize2 = (*env)->GetArrayLength(env, output_dir_Java);
    char output_dir[arraysize2+1];   
    for(int i = 0; i < arraysize2; i++){
        output_dir[i] = array2[i];   
    }   
    output_dir[arraysize2] = '\0';

    FILE *fp = fopen(filename, "rb");
    if (fp == NULL) {
        fprintf(stderr, "%s does not exist\n", filename);
        return 3;
    }
    simple_vad *vad = simple_vad_create();
    if (vad == NULL) {
        return 4;
    }
    FILE *fp2 = fopen(filename, "rb");
    struct cut_info *cut = cut_info_create(fp2);
    snprintf(cut->output_filename_prefix, sizeof(cut->output_filename_prefix), "%s",
             output_filename_prefix);
    snprintf(cut->output_file_dir, sizeof(cut->output_file_dir), "%s",
             output_dir);
    int res = run(fp, vad, cut);

    fclose(fp);
    fclose(fp2);
    simple_vad_free(vad);
    cut_info_free(cut);
    printf("PROGRAM FINISH\n");
    return res;
}

int run(FILE *fp, simple_vad *vad, struct cut_info *cut) {

    int16_t data[FRAME_SIZE];
    int res = 0;
    struct periods *per = periods_create();

    while (res == 0) {
        res = read_int16_bytes(fp, data);
        if (res <= 1) {
            int is_last = (res == 1);
            int is_active = process_vad(vad, data);
            add_period_activity(per, is_active, is_last);
            int vad_file_res = cut_add_vad_activity(cut, is_active, is_last);
            if (vad_file_res < 0) {
                printf("file write success %s\n", cut->result_filename);
            }
        } else if (ferror(fp)) {
            printf("read failed  ferror result  : %d\n", ferror(fp));
        }

    }
    periods_free(per);

    if (res != 1) {
        fprintf(stderr, "read file error %d\n", res);
        return res;
    }
    return 0;
}


int add_period_activity(struct periods *per, int is_active, int is_last) {
    static int old_is_active = 0;
    static int count = 0;
    int res_add = period_add_vad_activity(per, is_active, is_last);
    if (res_add != 0) {
        return res_add;
    }
    if (is_active != old_is_active) {
        // printf("%s,%d \n", old_is_active ? "A" : "I", count);
        // I,1  表示之前的1个FRAME是 INACTIVE的；
        // I,1 A,10 表示之前的1个FRAME是 INACTIVE的；第2-10个FRAME是ACTIVE的
        // periods_print(per);
        old_is_active = is_active;
    }
    count += 1;
    if (is_last) {
        periods_print(per);
        printf("total frames %d\n", count);
    }
}