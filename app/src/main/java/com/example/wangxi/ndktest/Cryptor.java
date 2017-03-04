package com.example.wangxi.ndktest;

public class Cryptor {

	
	public native static void crypt(String normal_path, String crypt_path);
	
	
	public native static void decrypt(String crypt_path, String decrypt_path);
	
	static{
		System.loadLibrary("ndk_file_crypt");
	}
}
