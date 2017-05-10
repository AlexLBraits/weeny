#include "application_p.h"
#include <jni.h>

extern JavaVM* mJavaVM;
Application* application = 0;

#include <android/log.h>

Application_p::Application_p(Application* owner, int argc, char** argv)
	: _q(owner)
{
	mJavaVM = 0;
	application = owner;
	
	__android_log_write(ANDROID_LOG_ERROR, "WEENY", "Application_p::Application_p");
}

Application_p::~Application_p()
{
	
}

int Application_p::exec()
{
	return 0;
}
