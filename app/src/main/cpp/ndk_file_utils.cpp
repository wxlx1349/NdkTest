#include "com_example_wangxi_ndktest_NDKFileUtils.h"
#include <jni.h>
#include <stdlib.h>
#include <stdio.h>

#include <android/log.h>

//#define LOGI(FORMAT,...) __android_log_print(ANDROID_LOG_INFO,"jason",FORMAT,__VA_ARGS__)
//#define LOGE(FORMAT,...) __android_log_print(ANDROID_LOG_ERROR,"jason",FORMAT,__VA_ARGS__)

//获取文件大小
long get_file_size(char *path){
    FILE *fp = fopen(path,"rb");
    fseek(fp,0,SEEK_END);
    return ftell(fp);
}

void readFileToFile(FILE *fr,FILE *fw,int len){
    if(len<=0){
        return;
    }
    int i=0;
    for(;i<len;i++){
        fputc(fgetc(fr),fw);
    }
}

JNIEXPORT void JNICALL Java_com_example_wangxi_ndktest_NDKFileUtils_diff
(JNIEnv *env, jclass jcls, jstring path_str, jstring path_pattern_jstr, jint file_num){
    const char* path=env->GetStringUTFChars(path_str,JNI_FALSE);
    const char* path_pattern=env->GetStringUTFChars(path_pattern_jstr,JNI_FALSE);

    //得到分割之后的子文件的路径列表
    char ** patches = (char **) malloc(sizeof(char*) * file_num);
    int i=0;
    for(;i<file_num;i++){
        //元素赋值
        //需要分割的文件：C://jason/liuyan.png
        //子文件：C://jason/liuyan_%d.png
        patches[i]= (char *) malloc(sizeof(char) * 100);
        sprintf(patches[i],path_pattern,i+1);
//        LOGI("patch path:%s",patches[i]);
    }

    //不断读取path文件，循环写入file_num个文件中
    //	整除
    //	文件大小：90，分成9个文件，每个文件10
    //	不整除
    //	文件大小：110，分成9个文件，
    //	前(9-1)个文件为(110/(9-1))=13
    //	最后一个文件(110%(9-1))=6
    int file_size=get_file_size((char *) path);
    FILE *fpr=fopen(path,"rb");
    if(file_size%file_num==0){
        int part=file_size/file_num;
        int i=0;
        for(;i<file_num;i++){
            FILE *fw=fopen(patches[i],"wb");
           readFileToFile(fpr,fw,part);
            fclose(fw);
        }
    } else{
        int part=file_size/(file_num-1);
        int i=0;
        for(;i<file_num-1;i++){
            FILE *fw=fopen(patches[i],"wb");
            readFileToFile(fpr,fw,part);
            fclose(fw);
        }
        int lastPart=file_size%(file_num-1);
        FILE *fw=fopen(patches[file_num-1],"wb");
        readFileToFile(fpr,fw,lastPart);
        fclose(fw);
    }

    fclose(fpr);

    //释放
    i=0;
    for(;i<file_num;i++){
        free(patches[i]);
    }
    free(patches);

    env->ReleaseStringUTFChars(path_str,path);
    env->ReleaseStringUTFChars(path_pattern_jstr,path_pattern);

};



/*
 * Class:     com_example_wangxi_ndktest_NDKFileUtils
 * Method:    patch
 * Signature: (Ljava/lang/String;ILjava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_com_example_wangxi_ndktest_NDKFileUtils_patch
(JNIEnv *env, jclass jcls, jstring path_pattern_str, jint file_num, jstring merge_path_str){
    const char* merge_path=env->GetStringUTFChars(merge_path_str,NULL);
    const char* path_pattern=env->GetStringUTFChars(path_pattern_str,NULL);
    //得到分割之后的子文件的路径列表
    char **patches = (char **) malloc(sizeof(char*) * file_num);
    int i = 0;
    for (; i < file_num; i++) {
        patches[i] = (char *) malloc(sizeof(char) * 100);
        //元素赋值
        //需要分割的文件：C://jason/liuyan.png
        //子文件：C://jason/liuyan_%d.png
        sprintf(patches[i], path_pattern, (i+1));
    }

    FILE *fpw=fopen(merge_path,"wb");
    i=0;
    for(;i<file_num;i++){
        int file_size=get_file_size(patches[i]);
        FILE *fr=fopen(patches[i],"rb");
        readFileToFile(fr,fpw,file_size);
        fclose(fr);
    }
    fclose(fpw);
    i=0;
    for(;i<file_num;i++){
        free(patches[i]);
    }
    free(patches);

    env->ReleaseStringUTFChars(merge_path_str,merge_path);
    env->ReleaseStringUTFChars(path_pattern_str,path_pattern);

};