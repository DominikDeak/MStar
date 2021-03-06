package com.eostek.scifly.devicemanager.manage.garbage.listener;

import java.util.ArrayList;

import android.os.Bundle;
import android.os.Handler;
import android.os.Message;

import com.eostek.scifly.devicemanager.FileCollection;
import com.eostek.scifly.devicemanager.BaseTaskListener;
import com.eostek.scifly.devicemanager.util.Constants;
import com.eostek.scifly.devicemanager.util.Debug;

public class ScanBigFileTaskListener implements BaseTaskListener {
    
    private static final String TAG = ScanBigFileTaskListener.class.getSimpleName();

    private Handler mhandler;
    private Long size;
    private ArrayList<String> files;
    
    public ScanBigFileTaskListener(Handler mhandler) {
        super();
        this.mhandler = mhandler;
    }

    @Override
    public void onTaskStarted() {
        
    }

    @Override
    public void onProgress(FileCollection collection) {
        
    }

    @Override
    public void onTaskCancelled(FileCollection collection) {
        mhandler = null;

    }

    @Override
    public void onTaskCompleted(FileCollection collection) {
        files = collection.getFiles();
        if(files == null){
            Debug.e(TAG, "files null");
        }
        size = collection.getSize();
        Message msg = new Message();
        Bundle data = new Bundle();
        data.putStringArrayList("files",files);
        data.putLong("size", size);
        msg.setData(data);
        msg.what = Constants.GARBAGE_MSG_BIG_FILE_AVAILABLE;
        mhandler.sendMessage(msg);
        
        mhandler = null;
    }

}
