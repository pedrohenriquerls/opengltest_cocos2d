#ifndef _BOX_h
#define _BOX_h

#include "cocos2d.h"
#include "OpenGLCommon.h"

class Box : public cocos2d::CCSprite
{
    
public:
    
    Box();
    
    virtual void draw();
    
    static Box* boxWithSizeAndPosition(Vector3D size, Vector3D position, Vector3D camera, const char* level);
    
    void setPosition(Vector3D vector);

    void setSize(Vector3D vector);
    
    void setCamera(Vector3D vector);
    
    void setTop(cocos2d::CCTexture2D* texture);
    
    void setSide(cocos2d::CCTexture2D* texture);
    
    void setTopSelected(cocos2d::CCTexture2D* texture);
    
    void setSelectedValue(bool value);
    
    void setHeight(GLfloat value);
    
    Vector3D getSize();
    
    float getHeight();
    
    bool getSelected();
    
    cocos2d::CCPoint getTopLeft();
    
    cocos2d::CCPoint getBottomRight();
    
    
private:
	Vector3D position;
    Vector3D size;
    Vector3D camera;
    
    CCSprite* boxTop;
    CCSprite* boxTopSelected;
    CCSprite* boxSide;
    
    cocos2d::CCPoint screenTopLeft;
    cocos2d::CCPoint screenBottomRight;
    
    bool selected;
    
    static cocos2d::CCTexture2D* createTopTexture(GLfloat r, GLfloat g, GLfloat b, const char* level);
    static cocos2d::CCTexture2D* createSideTexture();
    
    
    
};

#endif
 