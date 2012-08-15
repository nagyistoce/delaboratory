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

#ifndef _DE_USM_H
#define _DE_USM_H

#include "value.h"
#include "size.h"
#include "blur.h"
class deImageOld;

bool unsharpMask(const deValue* source, deValue* destination, deSize& size, deValue a, deValue r, deValue t, deBlurType type);
bool autoDodgeBurn(const deValue* source, deValue* destination, deSize& size, deValue r1, deValue r2, deValue t, bool burn);
bool shadowsHighlights(deValue r, int channel, const deImageOld& sourceImage, deImageOld& mainLayerImage, bool shadows);

#endif    
