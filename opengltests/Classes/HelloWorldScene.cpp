#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "Glu.h"

using namespace cocos2d;
using namespace CocosDenshion;

CCScene* HelloWorld::scene()
{
	// 'scene' is an autorelease object
	CCScene *scene = CCScene::node();
	
	// 'layer' is an autorelease object
	HelloWorld *layer = HelloWorld::node();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

bool HelloWorld::init()
{
	if ( !CCLayer::init() )
	{
		return false;
	}
	CCSize size = CCDirector::sharedDirector()->getWinSize();


	CCMenuItemImage *pCloseItem = CCMenuItemImage::itemFromNormalImage(
										"CloseNormal.png",
										"CloseSelected.png",
										this,
										menu_selector(HelloWorld::menuCloseCallback) );
    
	pCloseItem->setPosition( ccp(CCDirector::sharedDirector()->getWinSize().width - 90, 90) );


	CCMenu* pMenu = CCMenu::menuWithItems(pCloseItem, NULL);
	pMenu->setPosition( CCPointZero );
    
    
	this->addChild(pMenu, 1);

    set = new CCSet();
    
    
    Vector3D boxSize = vec(0.8f,0.8f,1.6f);
    
    
    Vector3D camera = vec(0.0f, 0.0f, 6.0f);
    
    
    set->addObject(Box::boxWithSizeAndPosition(boxSize, vec(-2.25f, 1.5f, 0.0f),camera, "1"));
    set->addObject(Box::boxWithSizeAndPosition(boxSize, vec(-0.75f, 1.5f, 0.0f),camera, "2"));
    set->addObject(Box::boxWithSizeAndPosition(boxSize, vec( 0.75f, 1.5f, 0.0f),camera, "3"));
    set->addObject(Box::boxWithSizeAndPosition(boxSize, vec( 2.25f, 1.5f, 0.0f),camera, "4"));
    
    set->addObject(Box::boxWithSizeAndPosition(boxSize, vec(-2.25f, 0.0f, 0.0f),camera, "5"));
    set->addObject(Box::boxWithSizeAndPosition(boxSize, vec(-0.75f, 0.0f, 0.0f),camera, "6"));
    set->addObject(Box::boxWithSizeAndPosition(boxSize, vec( 0.75f, 0.0f, 0.0f),camera, "7"));
    set->addObject(Box::boxWithSizeAndPosition(boxSize, vec( 2.25f, 0.0f, 0.0f),camera, "8"));
    
    set->addObject(Box::boxWithSizeAndPosition(boxSize, vec(-2.25f, -1.5f, 0.0f),camera, "9"));
    set->addObject(Box::boxWithSizeAndPosition(boxSize, vec(-0.75f, -1.5f, 0.0f),camera, "10"));
    set->addObject(Box::boxWithSizeAndPosition(boxSize, vec( 0.75f, -1.5f, 0.0f),camera, "11"));
    set->addObject(Box::boxWithSizeAndPosition(boxSize, vec( 2.25f, -1.5f, 0.0f),camera, "12"));
    
  
    CCSetIterator it;
    
    for( it = set->begin(); it != set->end(); it++) 
    {
        this->addChild((Box*)(*it));
    }

    schedule( schedule_selector(HelloWorld::tick) );
    
    setIsTouchEnabled(true);
    
    setIsAccelerometerEnabled(true);
    
	return true;
}

void HelloWorld::setCameraAngle(Vector3D angle)
{
    cameraAngle = angle;
}


void HelloWorld::ccTouchesBegan(CCSet *touches, CCEvent *pEvent)
{
    CCSetIterator it;
    CCTouch* touch;
    
    for( it = touches->begin(); it != touches->end(); it++) 
    {
        touch = (CCTouch*)(*it);
        
        if(!touch)
            break;        
        
        CCPoint winPos = touch->locationInView();
        winPos = CCDirector::sharedDirector()->convertToGL(winPos);
        
        //CCLog("x: %f   y: %f", winPos.x, winPos.y);
        
        CCSetIterator it;
        Box* box;
        
        for( it = set->begin(); it != set->end(); it++) 
        {
            box = (Box*)(*it);
            
            if(winPos.x > box->getTopLeft().x && winPos.x < box->getBottomRight().x && winPos.y > box->getBottomRight().y && winPos.y < box->getTopLeft().y)
            {
                box->setSelectedValue(true);   
            }   
        }
    }
}


void HelloWorld::didAccelerate(CCAcceleration* pAccelerationValue)
{
    float x = pow(pAccelerationValue->x * 2.0, 3);
    float y = pow(pAccelerationValue->y * 1.5, 2);
    

    if(pAccelerationValue->y < 0)
    {
        y *= -1;
    }

    
    CCSetIterator it;
    Box* box;
    
    for( it = set->begin(); it != set->end(); it++) 
    {
        box = (Box*)(*it);
        box->setCamera(vec(x, y, 6.0f));
    }
    
}


void HelloWorld::tick(ccTime dt)
{
    
    CCSetIterator it;
    Box* box;
    
    for( it = set->begin(); it != set->end(); it++) 
    {
        box = (Box*)(*it);
        
        
        if(box->getSelected())
        {
            GLfloat height = box->getHeight();
            
            if(height > 0.1)
            {        
                box->setHeight(height - 0.1f);
            }
        }
        
    }
}

void HelloWorld::menuCloseCallback(CCObject* pSender)
{
	CCDirector::sharedDirector()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}
