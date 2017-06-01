#include "application_p.h"
#include <jni.h>

extern JavaVM* mJavaVM;
WApplication* application = 0;

#include <android/log.h>

WApplication_p::WApplication_p(WApplication* owner, int argc, char** argv)
	: _q(owner)
{
	mJavaVM = 0;
	application = owner;
	
	__android_log_write(ANDROID_LOG_ERROR, "WEENY", "Application_p::Application_p");
}

WApplication_p::~WApplication_p()
{
	
}

int WApplication_p::exec()
{
	return 0;
}
