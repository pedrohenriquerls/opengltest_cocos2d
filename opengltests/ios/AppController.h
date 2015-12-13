//
//  opengltestsAppController.h
//  opengltests
//
//  Created by Pedro Sousa on 17/05/12.
//  Copyright Indra 2012. All rights reserved.
//

@class RootViewController;

@interface AppController : NSObject <UIAccelerometerDelegate, UIAlertViewDelegate, UITextFieldDelegate,UIApplicationDelegate> {
    UIWindow *window;
    RootViewController	*viewController;
}

@end

