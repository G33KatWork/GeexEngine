#include "DirectXResettableResource.h"

DirectXResettableResource::ResettableResourceList DirectXResettableResource::notifyList = DirectXResettableResource::ResettableResourceList();

void DirectXResettableResource::NotifyDeviceLost()
{
    for(ResettableResourceList::const_iterator i = notifyList.begin(); i != notifyList.end(); ++i)
        (*i)->OnDeviceLost();
}

void DirectXResettableResource::NotifyDeviceReset()
{
    for(ResettableResourceList::const_iterator i = notifyList.begin(); i != notifyList.end(); ++i)
        (*i)->OnDeviceReset();
}
