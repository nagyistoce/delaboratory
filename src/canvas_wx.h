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

#ifndef _DE_CANVAS_WX_H
#define _DE_CANVAS_WX_H

#include "canvas.h"
#include <wx/wx.h>

class deCanvasWX:public deCanvas
{
    private:
        wxDC& dc;
    public:
        deCanvasWX(wxDC& _dc);
        ~deCanvasWX();

        virtual void clear();

        virtual void setPen(int r, int g, int b);
        virtual void setBrush(int r, int g, int b);

        virtual void drawCircle(int x, int y, int r);
        virtual void drawLine(int x1, int y1, int x2, int y2);
        virtual void drawBitmap(deBitmap& bitmap);
        virtual void drawTriangle(int x1, int y1, int x2, int y2, int x3, int y3);

};


#endif
