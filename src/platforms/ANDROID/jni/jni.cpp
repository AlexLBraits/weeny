#include <jni.h>
#include <stdlib.h>
#include <queue>
#include <WApplication.h>

#include <android/log.h>

//-----------------------------------------------------------------------------
// Globals.
//-----------------------------------------------------------------------------
extern WApplication* application;
JavaVM* mJavaVM = nullptr;

/*******************************************************************************
                 Functions called by JNI
*******************************************************************************/
// Library init
extern "C" jint JNI_OnLoad (JavaVM* vm, void* reserved)
{
  JNIEnv *env;
  mJavaVM = vm;
  if (vm->GetEnv ((void**) &env, JNI_VERSION_1_4) != JNI_OK)
  {
    // LOGD ("Failed to get the environment using GetEnv()");
    return -1;
  }
  return JNI_VERSION_1_4;
}

int main(int argc, const char* argv[]);

extern "C"
void Java_@ANDROID_JNI_NATIVE_METHOD_NAME@_init (JNIEnv* env, jobject obj, jobjectArray strArray)
{
  __android_log_write(ANDROID_LOG_ERROR, "WEENY", "JNI_NATIVE_METHOD_INIT");
  
  int argc = 1;
  const char* argv[] = {"dll_main"};
  main(argc, argv);
  application->initialize();
}

// Resize
extern "C"
void Java_@ANDROID_JNI_NATIVE_METHOD_NAME@_reshape (
  JNIEnv* env, jobject jcls,
  jint _width, jint _height)
{
  application->resize(_width, _height);
}

extern "C"
void Java_@ANDROID_JNI_NATIVE_METHOD_NAME@_display (JNIEnv* env, jobject cls) 
{
  application->draw();
}

// Quit
extern "C"
void Java_@ANDROID_JNI_NATIVE_METHOD_NAME@_quit (JNIEnv* env, jobject cls)
{
}

extern "C"
void Java_@ANDROID_JNI_NATIVE_METHOD_NAME@_onKey (JNIEnv* env, jobject cls, jint keycode, jint isDown)
{
}

extern "C"
void Java_@ANDROID_JNI_NATIVE_METHOD_NAME@_onTouch (
  JNIEnv* env, jobject cls,
  jint action, jint pointerFingerId,
  jfloat x, jfloat y)
{
}
