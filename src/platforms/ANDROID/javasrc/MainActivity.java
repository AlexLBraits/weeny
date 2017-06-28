package @ANDROID_PACKAGE_NAME@;

import android.app.Activity;
import android.content.Context;
import android.content.Intent;
import android.content.pm.ActivityInfo;
import android.opengl.GLSurfaceView;
import android.opengl.GLES20;
import android.os.Build;
import android.os.Bundle;
import android.os.Environment;
import android.util.Log;
import android.view.*;
// import javax.microedition.khronos.egl.EGL10;
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
// private WEENYEngineStarter engine;
  private MyGLSurfaceView mGLView;
// private GPGSHelper mGPGSHelper;

  @Override
  protected void onCreate (Bundle savedInstanceState) {
    super.onCreate (savedInstanceState);

    Log.d("WEENY", "Activity::onCreate");

    // fullscreen
    requestWindowFeature (Window.FEATURE_NO_TITLE);
    getWindow().addFlags ( WindowManager.LayoutParams.FLAG_FULLSCREEN );

    Log.d("WEENY", "JAVASTARTER sdk_int:" + Build.VERSION.SDK_INT);
    mGLView = new MyGLSurfaceView (this);
    setContentView (mGLView);
  }

  @Override
  protected void onStart () {
    Log.d("WEENY", "Activity::onStart");
    super.onResume();
  }

  @Override
  protected void onResume () {
    Log.d("WEENY", "Activity::onResume");
    super.onResume();
  }

  @Override
  protected void onPause () {
    Log.d("WEENY", "Activity::onPause");
    super.onPause();
  }

  @Override
  protected void onStop () {
    Log.d("WEENY", "Activity::onStop");
    super.onStop ();
  }

  @Override
  protected void onRestart () {
    Log.d("WEENY", "Activity::onRestart");
    super.onRestart ();
  }

  @Override
  public void onDestroy () {
    Log.d("WEENY", "Activity::onDestroy");
    super.onDestroy();
  }

  @Override
  public void onLowMemory() {
    Log.d("WEENY", "Activity::onLowMemory");
    super.onLowMemory();
  }

  @Override
  public void onWindowFocusChanged(boolean hasFocus) {
    Log.d("WEENY", "Activity::onWindowFocusChanged " + hasFocus);
    super.onWindowFocusChanged(hasFocus);
  }

  // Key events
  @Override
  public boolean onKeyDown(int keyCode, KeyEvent event) {
    Log.d("WEENY", "Activity::onKeyDown " + keyCode + " " + event);
    return super.onKeyDown(keyCode, event);
  }

  class MyGLSurfaceView extends GLSurfaceView implements View.OnKeyListener, View.OnTouchListener {
  public MyGLSurfaceView (Context context)
  {
    super(context);

    setEGLContextClientVersion (2);

    setFocusable (true);
    setFocusableInTouchMode (true);
    requestFocus ();
    setOnKeyListener (this);
    setOnTouchListener (this);

    setRenderer (new MyRenderer());
    // Render the view only when there is a change in the drawing data
    setRenderMode(GLSurfaceView.RENDERMODE_WHEN_DIRTY);
  }

  // Key events
  public boolean onKey (View v, int keyCode, KeyEvent event) {
    Log.d("WEENY", "Activity::onKey " + keyCode + " " + event);
    return true;
  }

  // Touch events
  public boolean onTouch (View v, MotionEvent event) {
    Log.d("WEENY", "Activity::onTouch " + event);
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
      Log.d("WEENY", "Activity::initialize 222222222222222222");
    }
    else
    {
      GLES20.glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
      
      String APKPath = getApplicationInfo().sourceDir;
      String ESDPath = Environment.getExternalStorageDirectory().toString ();
      String internalPath = getFilesDir().toString();

      Log.d("WEENY", "Activity::initialize");
      init (new String[] {APKPath, ESDPath, internalPath});

      inited = true;
    }
  }
  
  public void onDrawFrame (GL10 gl) {
    GLES20.glClear(GLES20.GL_COLOR_BUFFER_BIT);
    display ();
  }
  
  public void onSurfaceChanged (GL10 gl, int w, int h) {
    GLES20.glViewport(0, 0, w, h);
    reshape (w, h);
  }

  }
}
