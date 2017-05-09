#import <UIKit/UIKit.h>
#import "application_p.h"
#import "appdelegate.h"

#import <application.h>
Application* application = 0;

Application_p::Application_p(Application* owner, int argc, char** argv)
 : _q(owner), _argc(argc), _argv(argv)
{
    application = owner;
}

Application_p::~Application_p()
{
}

int Application_p::exec()
{
    @autoreleasepool {
        return UIApplicationMain(
                                 _argc,
                                 _argv,
                                 nil,
                                 NSStringFromClass([AppDelegate class])
                                 );
    }
}
