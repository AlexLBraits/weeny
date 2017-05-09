package com.seventeenbullets.android.xgen;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

import android.app.Activity;
import android.opengl.GLSurfaceView;
import android.os.Environment;
import android.os.PowerManager;
import android.util.DisplayMetrics;
import android.util.Log;

import android.view.*;

import android.app.AlertDialog;
import android.widget.EditText;
import android.widget.TextView;
import android.content.DialogInterface;
import android.content.Intent;
import android.content.IntentFilter;
import android.content.Context;
import android.content.BroadcastReceiver;

import com.seventeenbullets.android.xgen.billing.PurchaseManager;
import com.seventeenbullets.android.xgen.SoundService;

public class XGenEngineStarter {

public static native void init (String[] argv);
public static native void reshape (int w, int h);
public static native void initgl ();
public static native void display ();
public static native void quit ();
public static native void pause ();
public static native void resume ();
private static native void onKey (int keyCode, int isDown);
private static native void onTouch (int action, int pointerFingerId, float x, float y);
private static native void setContentScaleFactor (float csf, int screenWidth, int screenHeight);
private static native void onInputValue (int result, String resultString);
public static native void onLowMemory ();
public static native void onSystemEvent (String event);


public final static boolean DEBUG = false;
private static Activity mActivity;
private static boolean inited = false;
private XGenRenderer mRenderer;
private PurchaseManager mPurchaseManager;
private SoundService mSoundService;
private boolean mIsDeviceLocked = false;
private boolean mIsActive = false;

private class RecieverScreen extends BroadcastReceiver {

@Override
public void onReceive(Context context, Intent intent) {
  if (intent.getAction().equals(Intent.ACTION_SCREEN_ON)) {
  } else if (intent.getAction().equals(Intent.ACTION_SCREEN_OFF)) {
    mIsDeviceLocked = true;
  } else if (intent.getAction().equals(Intent.ACTION_USER_PRESENT)) {
    if(mIsActive) {
      SoundService.onResume ();
    }
    mIsDeviceLocked = false;
  }
}
}

public XGenEngineStarter (Activity activity, String base64EncodedPublicKey) {
  mActivity = activity;
  mRenderer = new XGenRenderer();
  mPurchaseManager = new PurchaseManager(activity, base64EncodedPublicKey);
  mSoundService = new SoundService ();

  try {
    IntentFilter filter = new IntentFilter(Intent.ACTION_SCREEN_ON);
    filter.addAction(Intent.ACTION_SCREEN_OFF);
    filter.addAction(Intent.ACTION_USER_PRESENT);
    BroadcastReceiver mReceiver = new RecieverScreen();
    activity.registerReceiver(mReceiver, filter);
  } catch (Exception e) {
    e.printStackTrace();
  }

  inited = false;
}

public static Activity getActivity() {
  return mActivity;
}

public static void stopEngine () {
  android.os.Process.killProcess(android.os.Process.myPid());
}

// Key events
public static boolean onKey (View v, int keyCode, KeyEvent event) {
  int state = -1;
  if (event.getAction() == KeyEvent.ACTION_DOWN) {
    state = 1;
  } else if (event.getAction() == KeyEvent.ACTION_UP) {
    state = 0;
  }

  if(state != -1) {
    if(inited)
      XGenEngineStarter.onKey (keyCode, state);
    return true;
  }

  return false;
}

// Touch events
public boolean onTouch (View v, MotionEvent event) {
  if(!inited)
    return true;

  int pointerFingerId;
  float x;
  float y;
  int action = event.getAction () & MotionEvent.ACTION_MASK;

  if (action == MotionEvent.ACTION_MOVE) {
    int pointerCount = event.getPointerCount();
    for (int i = 0; i < pointerCount; i++) {
      pointerFingerId = event.getPointerId(i);
      x = event.getX(i);
      y = event.getY(i);
      XGenEngineStarter.onTouch (action, pointerFingerId, x, y);
    }
  } else {
    int i = event.getActionIndex();
    pointerFingerId = event.getPointerId(i);
    x = event.getX(i);
    y = event.getY(i);

    XGenEngineStarter.onTouch (
      action >= MotionEvent.ACTION_POINTER_DOWN ? action-MotionEvent.ACTION_POINTER_DOWN : action,
      pointerFingerId, x, y
      );
  }
  return true;
}

public void onPause () {
  mIsActive = false;
  XGenEngineStarter.pause();
  AndroidFacebookSDK.onPause();

  SoundService.onPause ();

  PowerManager powerManager = (PowerManager) mActivity.getSystemService(Context.POWER_SERVICE);
  boolean isScreenOn = powerManager.isScreenOn();
  if(!isScreenOn) {
    mIsDeviceLocked = true;
  }
}

public void onResume() {
  mIsActive = true;
  AndroidLocalNotificationManager.load();
  AndroidFacebookSDK.onResume();
  if(!mIsDeviceLocked) {
    SoundService.onResume ();
  }

  XGenEngineStarter.resume();
}

public void onDestroy() {
  AndroidFacebookSDK.onDestroy();
  mPurchaseManager.onDestroy();

  SoundService.onDestroy ();
}

public GLSurfaceView.Renderer getRenderer() {
  return mRenderer;
}

public boolean handleActivityResult(int requestCode, int resultCode, Intent data) {
  return mPurchaseManager.handleActivityResult(requestCode, resultCode, data);
}

class XGenRenderer implements GLSurfaceView.Renderer {

boolean inited = false;
boolean contentScaleFactorInited = false;

public boolean isReady() {
  return inited;
}

public void onSurfaceCreated (GL10 gl, EGLConfig config) {
  if(!inited) {
    String APKPath = XGenEngineStarter.mActivity.getApplicationInfo().sourceDir;
    String ESDPath = Environment.getExternalStorageDirectory ().toString ();
    String internalPath = XGenEngineStarter.mActivity.getFilesDir().toString();

    XGenEngineStarter.init (new String[] {APKPath, ESDPath, internalPath});

    inited = true;
    XGenEngineStarter.inited = true;
  } else {
    XGenEngineStarter.initgl();
  }
}

public void onSurfaceChanged (GL10 gl, int w, int h) {
  if(!contentScaleFactorInited) {
    contentScaleFactorInited = true;
    DisplayMetrics metrics = XGenEngineStarter.mActivity.getResources().getDisplayMetrics();
    float scale = Math.min(4.0f, Math.max(1.0f, metrics.density - 0.5f));
//                 if(w >= 1920 && h >= 1200){
//                     scale = 2.0f;
//                 }
    Log.d("XGenEngineStarter", String.format("Set contentScaleFactor density:%f, scale:%f, w:%d, h:%d", metrics.density, scale, w, h));
    XGenEngineStarter.setContentScaleFactor( scale, w, h);
  }

  XGenEngineStarter.reshape (w, h);
}

public void onDrawFrame (GL10 gl) {
  XGenEngineStarter.display ();
}
}


}
