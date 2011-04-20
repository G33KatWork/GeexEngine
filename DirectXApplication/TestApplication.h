#ifndef _TESTAPPLICATION_H_
#define _TESTAPPLICATION_H_

#include <Platform/Windows/WindowsDirectXApplication.h>

class TestApplication : public WindowsDirectXApplication
{
public:
    TestApplication();

    virtual bool OnInitialize();
    virtual void OnUpdate();
    virtual void OnRedraw();
    virtual void OnTerminate();

protected:
    Effect* effect;
    VertexBuffer *buf;
    IndexBuffer *index;

    float lr; //left right
    float ud; //up down
    float zoom;
    float rotrightleft;
    float rotupdown;

    Matrix4 world;
    Matrix4 projection;
    Matrix4 view;

    struct D3DVERTEX {float x, y, z; float r, g, b;};
};

#endif