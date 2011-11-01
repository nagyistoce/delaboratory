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

#ifndef _DE_PREVIEW_MANAGER_H
#define _DE_PREVIEW_MANAGER_H

class deProject;
#include "color_space.h"

class deViewManager
{
    private:
        int view;
        deProject& project;
        bool single;
        int channel;
        bool showBlendMask;
        int blendMaskChannel;
        deValue scale;
        deValue offsetX;
        deValue offsetY;


    public:
        deViewManager(deProject& _project);
        virtual ~deViewManager();

        void setView(int v);
        int getView() const;

        void repaint();

        void setSingleChannel(int _channel);
        void setNormal();

        deColorSpace getColorSpace() const;

        bool isSingleChannel() const {return single;};
        int getChannel() const {return channel;};

        void showMask(int maskChannel);
        void hideThisMask(int maskChannel);
        void hideMask();

        void setScale(deValue _scale);
        deValue getScale() const;

        bool maskVisible() const;
        int getMaskChannel() const;

        void setHistogramChannel(int channel);
        void setOffset(deValue x, deValue y);
        deValue getOffsetX() const;
        deValue getOffsetY() const;

        deValue getRealScale() const;

};

#endif