#ifndef _DXRESETTABLERESOURCE_H_
#define _DXRESETTABLERESOURCE_H_

#include "DirectXRendererExports.h"

#include <3D/GraphicsCardResources/Texture.h>
#include <list>

/**
  * This class is a superclass for all DirectX resources which need to be
  * notified on a lost or resetted device
  *
  * The overloaded operators (new and delete) registers the object in a
  * list of objectes which need to be notified
  */
class DIRECTXRENDERER_API DirectXResettableResource
{
public:
    virtual void OnDeviceLost() = 0;
    virtual void OnDeviceReset() = 0;

    virtual ~DirectXResettableResource() { DirectXResettableResource::notifyList.remove(this); }

    static void NotifyDeviceLost();
    static void NotifyDeviceReset();

protected:
    DirectXResettableResource() { DirectXResettableResource::notifyList.push_back(this); }

private:
    typedef std::list<DirectXResettableResource*> ResettableResourceList;

    //static list of all notifiable objects
    static ResettableResourceList notifyList;

    //prevent copying
    DirectXResettableResource(const DirectXResettableResource& other) {}
};

#endif
