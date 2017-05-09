package @ANDROID_PACKAGE_NAME@;

import android.app.Activity;
import android.content.Context;
import android.content.Intent;
import android.content.pm.ActivityInfo;
import android.opengl.GLSurfaceView;
import android.os.Build;
import android.os.Bundle;
import android.os.Environment;
import android.util.Log;
import android.view.*;
import javax.microedition.khronos.egl.EGL10;
import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.egl.EGLDisplay;
import javax.microedition.khronos.opengles.GL10;

public class @ANDROID_ACTIVITY_NAME@ extends Activity {

  public static native void init (String[] argv);
  public static native void reshape (int w, int h);
  public static native void display ();
  public static native void quit ();
  private static native void onKey (int keyCode, int isDown);
  private static native void onTouch (int action, int pointerFingerId, float x, float y);

  static {
    System.loadLibrary ("@ANDROID_ACTIVITY_NAME@");
  }

  public static @ANDROID_ACTIVITY_NAME@ mActivity;
// private SBBEngineStarter engine;
  private MyGLSurfaceView mGLView;
// private GPGSHelper mGPGSHelper;

  @Override
  protected void onCreate (Bundle savedInstanceState) {
    super.onCreate (savedInstanceState);

    Log.d("SBB", "Activity::onCreate");

    // fullscreen
    requestWindowFeature (Window.FEATURE_NO_TITLE);
    getWindow().addFlags ( WindowManager.LayoutParams.FLAG_FULLSCREEN );

    Log.d("SBB", "JAVASTARTER sdk_int:" + Build.VERSION.SDK_INT);
    mGLView = new MyGLSurfaceView (this);
    setContentView (mGLView);
  }

  @Override
  protected void onStart () {
    Log.d("SBB", "Activity::onStart");
    super.onResume();
  }

  @Override
  protected void onResume () {
    Log.d("SBB", "Activity::onResume");
    super.onResume();
  }

  @Override
  protected void onPause () {
    Log.d("SBB", "Activity::onPause");
    super.onPause();
  }

  @Override
  protected void onStop () {
    Log.d("SBB", "Activity::onStop");
    super.onStop ();
  }

  @Override
  protected void onRestart () {
    Log.d("SBB", "Activity::onRestart");
    super.onRestart ();
  }

  @Override
  public void onDestroy () {
    Log.d("SBB", "Activity::onDestroy");
    super.onDestroy();
  }

  @Override
  public void onLowMemory() {
    Log.d("SBB", "Activity::onLowMemory");
    super.onLowMemory();
  }

  @Override
  public void onWindowFocusChanged(boolean hasFocus) {
    Log.d("SBB", "Activity::onWindowFocusChanged " + hasFocus);
    super.onWindowFocusChanged(hasFocus);
  }

  // Key events
  @Override
  public boolean onKeyDown(int keyCode, KeyEvent event) {
    Log.d("SBB", "Activity::onKeyDown " + keyCode + " " + event);
    return super.onKeyDown(keyCode, event);
  }

  class MyGLSurfaceView extends GLSurfaceView implements View.OnKeyListener, View.OnTouchListener {
  public MyGLSurfaceView (Context context)
  {
    super(context);

    setEGLContextClientVersion (2);
    // if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.ICE_CREAM_SANDWICH){
    // setEGLConfigChooser(5, 6, 5, 0, 16, 8);
    // // setEGLConfigChooser(new ConfigChooser());
    // }
    //
    // getHolder().setFormat(PixelFormat.TRANSLUCENT);

    setFocusable (true);
    setFocusableInTouchMode (true);
    requestFocus ();
    setOnKeyListener (this);
    setOnTouchListener (this);

    // if(Build.VERSION.SDK_INT >= 11) {
    //   this.setPreserveEGLContextOnPause(true);
    // }
    setRenderer (new MyRenderer());
  }

  // Key events
  public boolean onKey (View v, int keyCode, KeyEvent event) {
    Log.d("SBB", "Activity::onKey " + keyCode + " " + event);
    return true;
  }

  // Touch events
  public boolean onTouch (View v, MotionEvent event) {
    Log.d("SBB", "Activity::onTouch " + event);
    return true;
  }

  }

  class MyRenderer implements GLSurfaceView.Renderer {

  boolean inited = false;
  boolean contentScaleFactorInited = false;

  public boolean isReady() {
    return inited;
  }

  public void onSurfaceCreated (GL10 gl, EGLConfig config) {
    if (inited)
    {
      Log.d("SBB", "Activity::initialize 222222222222222222");
    }
    else
    {
      String APKPath = getApplicationInfo().sourceDir;
      String ESDPath = Environment.getExternalStorageDirectory().toString ();
      String internalPath = getFilesDir().toString();

      Log.d("SBB", "Activity::initialize");
      init (new String[] {APKPath, ESDPath, internalPath});

      inited = true;
    }
  }

  public void onSurfaceChanged (GL10 gl, int w, int h) {
    reshape (w, h);
  }

  public void onDrawFrame (GL10 gl) {
    display ();
  }
  }

}
