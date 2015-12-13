#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "Box.h"
#include <math.h>

class HelloWorld : public cocos2d::CCLayer
{
public:
	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();  

    
    void tick(cocos2d::ccTime dt);

	// there's no 'id' in cpp, so we recommand to return the exactly class pointer
	static cocos2d::CCScene* scene();
	
	// a selector callback
	virtual void menuCloseCallback(CCObject* pSender);
    
    virtual void ccTouchesBegan(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);
    
    virtual void didAccelerate(cocos2d::CCAcceleration* pAccelerationValue);
    
    void setCameraAngle(Vector3D angle);

	// implement the "static node()" method manually
	LAYER_NODE_FUNC(HelloWorld);
    
private:

    cocos2d::CCSet *set;
    
    Vector3D cameraAngle;

};

#endif // __HELLOWORLD_SCENE_H__
