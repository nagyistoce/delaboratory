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

#ifndef _DE_RENDERER_H
#define _DE_RENDERER_H

class deChannelManager;
class deViewManager;
class deLayerProcessor;
class deLayerStack;
#include "size.h"
#include "rendered_image.h"
#include "mutex.h"

class deRenderer
{
    private:
        deRenderedImage renderedImage;
        deSize size;
        deChannelManager& channelManager;
        deMutex mutex;

        unsigned char* getCurrentImageData();

    public:
        deRenderer(deChannelManager& _channelManager);
        virtual ~deRenderer();

        bool render(deCanvas& canvas);
        bool prepareImage(const deViewManager& viewManager, deLayerProcessor& layerProcessor, deLayerStack& layerStack);
};

#endif
