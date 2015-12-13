#include "Box.h"
#include "Glu.h"

using namespace cocos2d;

Box::Box()
{
}

CCTexture2D* Box::createTopTexture(GLfloat r, GLfloat g, GLfloat b, const char* level) 
{
    float textureSize = 256;
    
    CCRenderTexture *rt = CCRenderTexture::renderTextureWithWidthAndHeight(textureSize, textureSize);
    
    rt->beginWithClear(r, g, b, 1.0);
    
    std::string file = (std::string(level) + std::string(".png"));
    CCSprite *levelImage = CCSprite::spriteWithFile(file.c_str());
    levelImage->setBlendFunc((ccBlendFunc){GL_ONE, GL_ONE_MINUS_SRC_ALPHA});
    levelImage->setPosition(ccp(textureSize/2, textureSize/2));
    levelImage->visit();
    
    CCSprite *frame = CCSprite::spriteWithFile("frame.png");
    frame->setBlendFunc((ccBlendFunc){GL_ONE, GL_ONE_MINUS_SRC_ALPHA});
    frame->setPosition(ccp(textureSize/2, textureSize/2));
    frame->visit();
    
    rt->end();

    return rt->getSprite()->getTexture();
}


CCTexture2D* Box::createSideTexture()
{
    float textureSize = 256;
    
    CCRenderTexture *rt = CCRenderTexture::renderTextureWithWidthAndHeight(textureSize, textureSize);
    
    rt->beginWithClear(0.6, 0.6, 0.6, 1.0);
    
    CCSprite *pattern = CCSprite::spriteWithFile("metal.jpg");
    
    pattern->setBlendFunc((ccBlendFunc){GL_ONE, GL_ONE_MINUS_SRC_ALPHA});
    pattern->setPosition(ccp(textureSize/2, textureSize/2));
    pattern->visit();
    
    rt->end();
    
    return rt->getSprite()->getTexture();
}


Box* Box::boxWithSizeAndPosition(Vector3D size, Vector3D position, Vector3D camera, const char* level)
{
    Box *box = new Box();    
    
    box->setPosition(position);
    box->setSize(size);
    box->setCamera(camera);
    
    box->autorelease();
     
    box->setSelectedValue(false);
       
//    box->setTop(createTopTexture(0.0, 0.4, 0.9, level));    
 
//    box->setTopSelected(createTopTexture(1.0, 1.0, 0.2, level));

    box->setSide(createSideTexture());
    
    return box;
}

void Box::setTop(cocos2d::CCTexture2D* texture)
{
    boxTop = new CCSprite();
    boxTop->initWithTexture(texture);
}

void Box::setSide(cocos2d::CCTexture2D* texture)
{
    boxSide = new CCSprite();
    boxSide->initWithTexture(texture);
}

void Box::setTopSelected(cocos2d::CCTexture2D* texture)
{
    boxTopSelected = new CCSprite();
    boxTopSelected->initWithTexture(texture);
}

void Box::setPosition(Vector3D vector)
{
    position = vector;
}

void Box::setSize(Vector3D vector)
{
    size = vector;
}

void Box::setCamera(Vector3D vector)
{
    camera = vector;
}

void Box::setSelectedValue(bool value)
{
    selected = value;
}

void Box::setHeight(GLfloat value)
{
    size.z = value;
}

bool Box::getSelected()
{
    return selected;
}

GLfloat Box::getHeight()
{
    return size.z;
}

Vector3D Box::getSize()
{
    return size;
}


CCPoint Box::getTopLeft()
{
    return screenTopLeft;
}

CCPoint Box::getBottomRight()
{
    return screenBottomRight;
}


void Box::draw()
{
    
    GLfloat maxX = size.x / 2.0f;
    GLfloat minX = maxX * -1;
    
    GLfloat maxY = size.y / 2.0f;
    GLfloat miny = maxY * -1;
   
    const GLfloat frontVertices[] = {
		minX, miny, size.z,
        maxX, miny, size.z,
        minX, maxY, size.z,
        maxX, maxY, size.z,
	};
	const GLfloat backVertices[] = {
		minX, miny, 0.0f,
        minX, maxY, 0.0f,
        maxX, miny, 0.0f,
        maxX, maxY, 0.0f,
	};
	const GLfloat leftVertices[] = {
		minX, miny, size.z,
        minX, maxY, size.z,
        minX, miny, 0.0f,
        minX, maxY, 0.0f,
	};
	const GLfloat rightVertices[] = {
		maxX, miny, 0.0f,
        maxX, maxY, 0.0f,
        maxX, miny, size.z,
        maxX, maxY, size.z,
	};
	const GLfloat topVertices[] = {
		minX, maxY, size.z,
        maxX, maxY, size.z,
        minX, maxY, 0.0f,
        maxX, maxY, 0.0f,
	};
	const GLfloat bottomVertices[] = {
		minX, miny, size.z,
        minX, miny, 0.0f,
        maxX, miny, size.z,
        maxX, miny, 0.0f,
	};
    
    const GLfloat textureCoordinates[] = {
		0, 0,
        1, 0,
        0, 1,
        1, 1,
	};
	
	glEnableClientState(GL_COLOR_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    glEnable(GL_TEXTURE_2D);
    
    
	glLoadIdentity();
    
    cocos2d::gluLookAt(camera.x, camera.y, camera.z, 0, 0, 0, 0, 1, 0); //OK
    
    
    GLfloat modelview[16]; 
    GLfloat projection[16];
    GLint viewport[4];
    
    glGetFloatv( GL_MODELVIEW_MATRIX, modelview );
    glGetFloatv( GL_PROJECTION_MATRIX, projection );
    glGetIntegerv( GL_VIEWPORT, viewport );
    
    
    float winZ;

    gluProject(frontVertices[6]+position.x, frontVertices[7]+position.y, frontVertices[8], modelview, projection, viewport, &this->screenTopLeft.x, &this->screenTopLeft.y, &winZ);
    gluProject(frontVertices[3]+position.x, frontVertices[4]+position.y, frontVertices[5], modelview, projection, viewport, &screenBottomRight.x, &screenBottomRight.y, &winZ);

	glTranslatef(position.x, position.y, position.z);

    
//    if(selected) 
//    {
//        glBindTexture(GL_TEXTURE_2D, boxTopSelected->getTexture()->getName());
//    }
//    else 
//    {
//        glBindTexture(GL_TEXTURE_2D, boxTop->getTexture()->getName());
//        
//    }
    
    glTexCoordPointer(2, GL_FLOAT, 0,  textureCoordinates);
    
    glVertexPointer(3, GL_FLOAT, 0, frontVertices);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	
    glBindTexture(GL_TEXTURE_2D, boxSide->getTexture()->getName());
    glTexCoordPointer(2, GL_FLOAT, 0,  textureCoordinates);
    
    glVertexPointer(3, GL_FLOAT, 0, backVertices);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	
    
    glVertexPointer(3, GL_FLOAT, 0, leftVertices);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    
    glVertexPointer(3, GL_FLOAT, 0, rightVertices);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    
    glVertexPointer(3, GL_FLOAT, 0, topVertices);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    
    glVertexPointer(3, GL_FLOAT, 0, bottomVertices);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    
	
	glEnableClientState(GL_COLOR_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    glEnable(GL_TEXTURE_2D);


    
}

