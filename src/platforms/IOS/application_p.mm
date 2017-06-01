#import <UIKit/UIKit.h>
#import "application_p.h"
#import "appdelegate.h"

#import <WApplication.h>
WApplication* application = 0;

WApplication_p::WApplication_p(WApplication* owner, int argc, char** argv)
 : _q(owner), _argc(argc), _argv(argv)
{
    application = owner;
}

WApplication_p::~WApplication_p()
{
}

int WApplication_p::exec()
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
