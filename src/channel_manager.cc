/*
    delaboratory - color correction utility
    Copyright (C) 2011 Jacek Poplawski

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "channel_manager.h"
#include <cassert>
#include <iostream>
#include <wx/wx.h>
#include "logger.h"

static wxMutex channelManagerMutex;

deChannelManager::deChannelManager()
:channelSize(0,0)
{
}

deChannelManager::~deChannelManager()
{
    unsigned int i;
    for (i = 0; i < channels.size(); i++)
    {
        freeChannel(i);
    }
}

void deChannelManager::setChannelSize(const deSize& size)
{
    channelSize = size;
    destroyAllChannels();
}

int deChannelManager::allocateNewChannel()
{
    lock();

    deChannel* channel = new deChannel();
    channel->allocate(channelSize.getN());

    if (trashed.size() > 0)
    {
        std::set<int>::iterator i = trashed.begin();
        int c = *i;
        trashed.erase(c);
        channels[c] = channel;
        unlock();
        return c;
    }
    else
    {
        channels.push_back(channel);
        int c = channels.size() - 1;
        unlock();
        return c;
    }        

}

void deChannelManager::freeChannel(int index)
{
    lock();

    assert(index >= 0);
    assert((unsigned int)index < channels.size());

    if (channels[index])
    {
        delete channels[index];
        channels[index] = NULL;
        trashed.insert(index);
    }        
    else
    {
    }

    unlock();
}

deChannel* deChannelManager::getChannel(int index)
{
    if (index < 0)
    {
        return NULL;
    }
    assert((unsigned int)index < channels.size());
    tryAllocateChannel(index);
    return channels[index];
}

void deChannelManager::destroyAllChannels()
{
    unsigned int i;
    for (i = 0; i < channels.size(); i++)
    {
        if (channels[i])
        {
            tryDeallocateChannel(i);
        }            
    }
}

deSize deChannelManager::getChannelSize() const
{
    return channelSize;
}

void deChannelManager::lock()
{
    lockWithLog(channelManagerMutex, "channel manager mutex");
}

void deChannelManager::unlock()
{
    channelManagerMutex.Unlock();
}

int deChannelManager::getNumberOfAllocatedChannels() const
{
    int n = 0;
    unsigned int i;
    for (i = 0; i < channels.size(); i++)
    {
        if (channels[i])
        {
            if (channels[i]->isAllocated())
            {
                n++;
            }
        }
    }
    return n;
}

void deChannelManager::tryAllocateChannel(int index)
{
    lock();

    assert(index >= 0);
    assert((unsigned int)index < channels.size());
    if ((channels[index]))
    {
        if (!channels[index]->isAllocated())
        {
            channels[index]->allocate(channelSize.getN());
        }
    }

    unlock();
}

void deChannelManager::tryDeallocateChannel(int index)
{
    lock();

    assert(index >= 0);
    assert((unsigned int)index < channels.size());
    if ((channels[index]))
    {
        if (channels[index]->isAllocated())
        {
            channels[index]->deallocate();
        }
    }

    unlock();
}
