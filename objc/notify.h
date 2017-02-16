#import <Foundation/Foundation.h>
#import <objc/runtime.h>

NSString *fakeBundleIdentifier = nil;

@implementation NSBundle (swizle)
- (NSString *)__bundleIdentifier{
  if (self == [NSBundle mainBundle]) {
    return fakeBundleIdentifier ? fakeBundleIdentifier : @"com.apple.terminal";
  } else {
    return [self __bundleIdentifier];
  }
}
@end

BOOL installNSBundleHook(){
  Class class = objc_getClass("NSBundle");
  if (class) {
    method_exchangeImplementations(class_getInstanceMethod(class, @selector(bundleIdentifier)),
                                   class_getInstanceMethod(class, @selector(__bundleIdentifier)));
    return YES;
  }
  return NO;
}

@interface NotificationCenterDelegate : NSObject<NSUserNotificationCenterDelegate>
@property (nonatomic, assign) BOOL keepRunning;
@end

@implementation NotificationCenterDelegate
- (void)userNotificationCenter:(NSUserNotificationCenter *)center didDeliverNotification:(NSUserNotification *)notification{
  self.keepRunning = NO;
}
@end
