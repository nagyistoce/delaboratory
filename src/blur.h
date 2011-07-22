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

#ifndef _DE_BLUR_H
#define _DE_BLUR_H

#include "value.h"
#include <set>
#include "property_channels.h"

enum deBlurDirection
{
    deBlurHorizontal,
    deBlurVertical
};

class dePreview;

void blur(const dePreview& sourcePreview, dePreview& destinationPreview, deBlurDirection direction, deValue radius, const deChannels& enabledChannels, deValue t);

#endif    
