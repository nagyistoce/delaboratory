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

#ifndef _DE_COLOR_SPACE_H
#define _DE_COLOR_SPACE_H

#include "value.h"
#include <string>
#include <vector>
#include <wx/wx.h>

enum deColorSpace
{
    deColorSpaceInvalid,
    deColorSpaceRGB,
    deColorSpaceBW,
    deColorSpaceLAB,
    deColorSpaceCMY,
    deColorSpaceCMYK,
    deColorSpaceHSV,
    deColorSpaceHSL,
    deColorSpaceXYZ,
    deColorSpaceLCH
};

int getColorSpaceSize(const deColorSpace& colorSpace);
void getColorSpaceChannelRanges(const deColorSpace& colorSpace, int index, deValue& min, deValue& max);
std::string getColorSpaceName(deColorSpace colorSpace);
std::string getChannelName(deColorSpace colorSpace, int channel);
deColorSpace colorSpaceFromString(const std::string& name);

void getSupportedColorSpaces(std::vector<deColorSpace>& result);
void getSupportedConversions(const deColorSpace& colorSpace, std::vector<deColorSpace>& result);

wxColour getChannelwxColour(deColorSpace colorSpace, int channel);

deValue getPresentationValue(deColorSpace colorSpace, int channel, deValue v);

#endif