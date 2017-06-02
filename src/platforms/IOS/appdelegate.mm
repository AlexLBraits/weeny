#import "appdelegate.h"
#import "view.h"

#import <application.h>

extern Application* Application;

@implementation AppDelegate

#pragma mark -
#pragma mark Application lifecycle

- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions
{
    UIScreen* mainScreen = [UIScreen mainScreen];
    CGRect frame = [mainScreen bounds];
    _window = [[UIWindow alloc] initWithFrame:frame];
    
    [_window setOpaque:YES];
    
    UIViewController* rootViewController = [[UIViewController alloc] init];
    [rootViewController prefersStatusBarHidden];
    [_window setRootViewController:rootViewController];
    [_window setScreen:[UIScreen mainScreen]];
    
    View* view = [[[View alloc] initWithFrame:[_window frame]] autorelease];
    
//    View  *view = [[View alloc] initWithFrame:[UIScreen mainScreen].bounds];
//    [myview setBackgroundColor:[UIColor grayColor]];
//    [self.view addSubview:myview];
    
    [rootViewController setView:view];
    
    // Override point for customization after application launch.
    
    [_window makeKeyAndVisible];
    
    [(View*)_window.rootViewController.view startAnimation];
    
    return YES;
}


- (void)applicationWillResignActive:(UIApplication *)application
{
    /*
     Sent when the application is about to move from active to inactive state. 
     This can occur for certain types of temporary interruptions (such as an 
     incoming phone call or SMS message) or when the user quits the application 
     and it begins the transition to the background state.
     Use this method to pause ongoing tasks, disable timers, and throttle 
     down OpenGL ES frame rates. Games should use this method to pause the game.
     */
    
    [(View*)_window.rootViewController.view stopAnimation];
}


- (void)applicationDidEnterBackground:(UIApplication *)application {
    /*
     Use this method to release shared resources, save user data, invalidate 
     timers, and store enough application state information to restore your 
     application to its current state in case it is terminated later.
     If your application supports background execution, called instead of 
     applicationWillTerminate: when the user quits.
     */
    
    [(View*)_window.rootViewController.view stopAnimation];
}


- (void)applicationWillEnterForeground:(UIApplication *)application {
    /*
     Called as part of transition from the background to the inactive 
     state: here you can undo many of the changes made on entering 
     the background.
     */
    
    [(View*)_window.rootViewController.view startAnimation];
}


- (void)applicationDidBecomeActive:(UIApplication *)application
{
    /*
     Restart any tasks that were paused (or not yet started) while 
     the application was inactive. If the application was previously in the 
     background, optionally refresh the user interface.
     */
    
    [(View*)_window.rootViewController.view startAnimation];
}


- (void)applicationWillTerminate:(UIApplication *)application {
    /*
     Called when the application is about to terminate.
     See also applicationDidEnterBackground:.
     */
    
    [(View*)_window.rootViewController.view stopAnimation];
}


#pragma mark -
#pragma mark Memory management

- (void)applicationDidReceiveMemoryWarning:(UIApplication *)application {
    /*
     Free up as much memory as possible by purging cached data objects that 
     can be recreated (or reloaded from disk) later.
     */
}

@end
