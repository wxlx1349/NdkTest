package com.example.wangxi.ndktest;

import android.os.Bundle;
import android.os.Environment;
import android.support.v7.app.AppCompatActivity;
import android.util.Log;
import android.view.View;

import java.io.File;

public class MainActivity extends AppCompatActivity {

    // Used to load the 'native-lib' library on application startup.


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);


    }

    public void onCrypt(View view) {
        String normal_path = Environment.getExternalStorageDirectory().getAbsolutePath() + File.separatorChar + "xiaomei.jpeg";
        String crypt_path = Environment.getExternalStorageDirectory().getAbsolutePath() + File.separatorChar + "xiaomei_crypt.jpeg";
        Cryptor.crypt(normal_path, crypt_path);
        Log.d("jason", "加密完成" + normal_path);
    }

    public void onDecrypt(View view) {
        String crypt_path = Environment.getExternalStorageDirectory().getAbsolutePath() + File.separatorChar + "xiaomei_crypt.jpeg";
        String decrypt_path = Environment.getExternalStorageDirectory().getAbsolutePath() + File.separatorChar + "xiaomei_decrypt.jpeg";
        Cryptor.decrypt(crypt_path, decrypt_path);
        Log.d("jason", "解密完成");
    }

    public void onDiff(View view){
        String normal_path = Environment.getExternalStorageDirectory().getAbsolutePath() + File.separatorChar + "xiaomei.jpeg";
        String path_pattern = Environment.getExternalStorageDirectory().getAbsolutePath() + File.separatorChar + "xiaomei_%d.jpeg";
        NDKFileUtils.diff(normal_path,path_pattern,3);
        Log.d("jason", "分割完成");
    }

    public void onPatch(View view){
        String merge_path = Environment.getExternalStorageDirectory().getAbsolutePath() + File.separatorChar + "xiaomei_merge.jpeg";
        String path_pattern = Environment.getExternalStorageDirectory().getAbsolutePath() + File.separatorChar + "xiaomei_%d.jpeg";
        NDKFileUtils.patch(path_pattern,3,merge_path);
        Log.d("jason", "合成完成");
    }
}
