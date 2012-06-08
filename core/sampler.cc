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

#include "sampler.h"

deSampler::deSampler()
{
    x = -1;
    y = -1;
    colorSpace = deColorSpaceCMYK;
    enabled = false;
    selected = false;
}

deSampler::~deSampler()
{
}

void deSampler::setPosition(deValue _x, deValue _y)
{
    x = _x;
    y = _y;
}

void deSampler::setColorSpace(deColorSpace c)
{
    colorSpace = c;
}

bool deSampler::isEnabled() const
{
    return enabled;
}

void deSampler::enable()
{
    enabled = true;
}

void deSampler::disable()
{
    enabled = false;
}

bool deSampler::isSelected() const
{
    return selected;
}

void deSampler::setSelected(bool s)
{
    selected = s;
}
