package com.bq.tv.task.ui.functionitem;

import android.app.Dialog;
import android.content.Context;

public class ActionItem extends FunctionItem implements FunctionItem.OnClickBehavior{
    
    public ActionItem(Context context, Dialog dialog, int id, String intentStr) {
        super(context, dialog, id, intentStr);
        mOnClickBehavior=this;
    }

    @Override
    public void onClick() {
        // TODO Auto-generated method stub
        startActivityByAction();
        mDialog.dismiss();
    }
}