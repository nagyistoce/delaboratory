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

#include "switchable_layer.h"
#include "color_space_utils.h"
#include "property_boolean.h"

deSwitchableLayer::deSwitchableLayer(deColorSpace _colorSpace, deChannelManager& _channelManager, int _sourceLayerIndex, deLayerStack& _layerStack)
:deBaseLayerWithSource(_colorSpace, _channelManager, _sourceLayerIndex, _layerStack)
{
    int n = getColorSpaceSize(colorSpace);
    int i;
    for (i = 0; i < n; i++)
    {
        std::string n = getChannelName(colorSpace, i);
        createPropertyBoolean(n);
        getPropertyBoolean(n)->setSizer("channels");
        getPropertyBoolean(n)->setBlendOnly();
        enableChannel(i);
    }
}

deSwitchableLayer::~deSwitchableLayer()
{
}

void deSwitchableLayer::disableNotLuminance()
{
    int n = getColorSpaceSize(colorSpace);
    int i;
    for (i = 0; i < n; i++)
    {
        if (!isChannelLuminance(colorSpace, i))
        {
            disableChannel(i);
        }            
    }
}

void deSwitchableLayer::disableNotForSharpen()
{
    int n = getColorSpaceSize(colorSpace);
    int i;
    for (i = 0; i < n; i++)
    {
        if (!shouldChannelBeSharpened(colorSpace, i))
        {
            disableChannel(i);
        }            
    }
}

void deSwitchableLayer::disableAll()
{
    int n = getColorSpaceSize(colorSpace);
    int i;
    for (i = 0; i < n; i++)
    {
        disableChannel(i);
    }
}

bool deSwitchableLayer::isChannelEnabled(int index) const
{
    std::string n = getChannelName(colorSpace, index);
    const dePropertyBoolean* p = getPropertyBoolean(n);
    if (!p)
    {
        return false;
    }
    return p->get();
}

void deSwitchableLayer::enableChannel(int index)
{
    std::string n = getChannelName(colorSpace, index);
    dePropertyBoolean* p = getPropertyBoolean(n);
    if (p)
    {
        p->set(true);
    }        
}

void deSwitchableLayer::disableChannel(int index)
{
    std::string n = getChannelName(colorSpace, index);
    dePropertyBoolean* p = getPropertyBoolean(n);
    if (p)
    {
        p->set(false);
    }        
}

