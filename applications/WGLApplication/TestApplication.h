#ifndef _TESTAPPLICATION_H_
#define _TESTAPPLICATION_H_

#include <Platform/Windows/WindowsOpenGLApplication.h>

class TestApplication : public WindowsOpenGLApplication
{
public:
    TestApplication();

    virtual bool OnInitialize();
    virtual void OnUpdate();
    virtual void OnRedraw();
    virtual void OnTerminate();

protected:
    VertexBuffer *buf;
    IndexBuffer *index;
    Effect *effect;

    float lr; //left right
    float ud; //up down
    float zoom;
    float rotrightleft;
    float rotupdown;

    Matrix4 world;
    Matrix4 projection;
    Matrix4 view;

    struct GLVERTEX {float x, y, z; float r, g, b;};
};

#endif