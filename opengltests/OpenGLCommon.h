#ifndef _OPENGL_COMMON_H
#define _OPENGL_COMMON_H

typedef struct {
    
    GLfloat x;
    GLfloat y;
    GLfloat z;
} Vector3D;


static inline Vector3D vec(const GLfloat x, const GLfloat y, const GLfloat z)
{
    Vector3D v;
    v.x = x;
    v.y = y;
    v.z = z;
	return v;
}


#endif
