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

#include "property.h"

deProperty::deProperty(const std::string& _name)
:name(_name)
{
    label = "";
    blendOnly = false;
    size = false;
    others = false;
}

deProperty::~deProperty()
{
}

std::string deProperty::getName() const
{
    return name;
}

std::string deProperty::getLabel() const
{
    if (label == "")
    {
        return name;
    }
    else
    {
        return label;
    }
}

void deProperty::setLabel(const std::string& _label)
{
    label = _label;
}

void deProperty::setBlendOnly()
{
    blendOnly = true;
}

void deProperty::setSize()
{
    size = true;
}

void deProperty::setOthers()
{
    others = true;
}
