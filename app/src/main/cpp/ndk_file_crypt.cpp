#include <jni.h>
#include <string>
#include "com_example_wangxi_ndktest_Cryptor.h"

char password[] = "mynameisjason888";
//加密
JNIEXPORT void JNICALL Java_com_example_wangxi_ndktest_Cryptor_crypt
        (JNIEnv *env, jclass jcls, jstring normal_path_jstr, jstring crypt_path_jstr) {
    const char *normal_path = env->GetStringUTFChars(normal_path_jstr, JNI_FALSE);
    const char *crypt_path = env->GetStringUTFChars(crypt_path_jstr, JNI_FALSE);

    //打开文件
    FILE *normal_fp = fopen(normal_path, "rb");
    FILE *crypt_fp = fopen(crypt_path, "wb");
    //一次读取一个字符
    int ch;
    int i = 0;  //循环使用密码中的字母进行异或运算
    int pwd_len = strlen(password);
    while ((ch = fgetc(normal_fp)) != EOF) {//End of File
        //写入（异或运算）
        fputc(ch ^ password[i % pwd_len], crypt_fp);
        i++;
    }
    fclose(crypt_fp);
    fclose(normal_fp);

};

JNIEXPORT void JNICALL Java_com_example_wangxi_ndktest_Cryptor_decrypt
        (JNIEnv *env, jclass jcls, jstring crypt_path_jstr, jstring decrypt_path_jstr) {
    const char *crypt_path = env->GetStringUTFChars(crypt_path_jstr, JNI_FALSE);
    const char *decrypt_path = env->GetStringUTFChars(decrypt_path_jstr, JNI_FALSE);

    FILE *crypt_fp = fopen(crypt_path, "rb");
    FILE *decrypt_fp = fopen(decrypt_path, "wb");

    int i = 0;
    int pwd_len = strlen(password);
    int ch;
    while ((ch = fgetc(crypt_fp)) != EOF) {
        fputc(ch ^ password[i % pwd_len], decrypt_fp);
        i++;
    }
    fclose(crypt_fp);
    fclose(decrypt_fp);

};
