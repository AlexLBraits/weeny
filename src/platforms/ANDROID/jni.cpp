#include <jni.h>
#include <stdlib.h>
#include <queue>
#include <application.h>

// #define JNI_NATIVE_METHOD_PREFIX Java_@ANDROID_JNI_NATIVE_METHOD_NAME@
#define JNI_NATIVE_METHOD_PREFIX Java_com_example_myapp_MyProject

#define JNI_NATIVE_METHOD_INIT 			Java_com_example_myapp_MyProject_init
#define JNI_NATIVE_METHOD_RESHAPE 	Java_com_example_myapp_MyProject_reshape
#define JNI_NATIVE_METHOD_DISPLAY 	Java_com_example_myapp_MyProject_display
#define JNI_NATIVE_METHOD_QUIT 			Java_com_example_myapp_MyProject_quit
#define JNI_NATIVE_METHOD_ON_KEY 		Java_com_example_myapp_MyProject_onKey
#define JNI_NATIVE_METHOD_ON_TOICH 	Java_com_example_myapp_MyProject_onTouch

#include <android/log.h>

//-----------------------------------------------------------------------------
// Globals.
//-----------------------------------------------------------------------------
extern Application* application;
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
void JNI_NATIVE_METHOD_INIT (JNIEnv* env, jobject obj, jobjectArray strArray)
{
  __android_log_write(ANDROID_LOG_ERROR, "SBB", "JNI_NATIVE_METHOD_INIT");
  
  int argc = 1;
  const char* argv[] = {"dll_main"};
  main(argc, argv);
  application->initialize();
}

// Resize
extern "C"
void JNI_NATIVE_METHOD_RESHAPE (
  JNIEnv* env, jobject jcls,
  jint _width, jint _height)
{
  application->resize(_width, _height);
}

extern "C"
void JNI_NATIVE_METHOD_DISPLAY (JNIEnv* env, jobject cls) 
{
  application->draw();
}

// Quit
extern "C"
void JNI_NATIVE_METHOD_QUIT (JNIEnv* env, jobject cls)
{
}

extern "C"
void JNI_NATIVE_METHOD_ON_KEY (JNIEnv* env, jobject cls, jint keycode, jint isDown)
{
}

extern "C"
void JNI_NATIVE_METHOD_ON_TOICH (
  JNIEnv* env, jobject cls,
  jint action, jint pointerFingerId,
  jfloat x, jfloat y)
{
}
