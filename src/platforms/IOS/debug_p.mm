#import "debug_p.h"
#import <Foundation/Foundation.h>

void Debug_p::log(const char* message)
{
	NSLog([NSString stringWithUTF8String:message]);
}
