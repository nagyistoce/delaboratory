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

#include "channel.h"
#include <string>
#include <cassert>

static wxMutex channelLockingMutex;

deChannel::deChannel(deImage& _image)
:image(_image), 
readSemaphore(4, 4),
writeMutex(wxMUTEX_RECURSIVE)
{
    pixels = NULL;
    maxReaders = 4;
}

deChannel::~deChannel()
{
    if (pixels)
    {
        deallocate();
    }
}

deValue* deChannel::getPixels()
{
    return pixels;
}

const deValue* deChannel::getPixels() const
{
    return pixels;
}

deValue deChannel::getValue(int pos) const
{
    return pixels[pos];
}

void deChannel::setValue(int pos, const deValue& value)
{
    pixels[pos] = value;
}

void deChannel::setValueClip(int pos, const deValue& value)
{
    if (value < 0)
    {
        pixels[pos] = 0;
        return;
    }
    if (value > 1)
    {
        pixels[pos] = 1;
        return;
    }
    pixels[pos] = value;
}

void deChannel::deallocate()
{
    lockWrite();
    assert(pixels);
    delete [] pixels;
    pixels = NULL;
    unlockWrite();
}

void deChannel::allocate(int size)
{
    lockWrite();
    assert(!pixels);
    pixels = new deValue [size];
    unlockWrite();
}

void deChannel::lockRead()
{
    readSemaphore.Wait();
}

void deChannel::unlockRead()
{
    readSemaphore.Post();
}

void deChannel::lockWrite()
{
    int i;
    for (i = 0; i < maxReaders; i++)
    {
        readSemaphore.Wait();
    }
    writeMutex.Lock();
}

void deChannel::unlockWrite()
{
    writeMutex.Unlock();
    int i;
    for (i = 0; i < maxReaders; i++)
    {
        readSemaphore.Post();
    }
}

void startChannelLocking()
{
    channelLockingMutex.Lock();
}

void finishChannelLocking()
{
    channelLockingMutex.Unlock();
}
