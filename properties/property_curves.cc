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

#include "property_curves.h"
#include "str.h"

dePropertyCurves::dePropertyCurves(const std::string& _name, int _size)
:deProperty(_name), size(_size)
{
    horizontalChannel = -1;
    int i;
    for (i = 0; i < size; i++)
    {
        curves.push_back( new deBaseCurve());
    }
}

dePropertyCurves::~dePropertyCurves()
{
    int i;
    for (i = 0; i < size; i++)
    {
        delete curves[i];
    }
}

void dePropertyCurves::setHorizontalChannel(int channel)
{
    horizontalChannel = channel;
}

int dePropertyCurves::getHorizontalChannel() const
{
    return horizontalChannel;
}

bool dePropertyCurves::onKey(int key, int i, deValue p)
{
    deValue v = -1;

    if (key == 'W')
    {
        v = 1.0;            
    }

    if (key == 'B')
    {
        v = 0.0;            
    }

    if (key == 'A')
    {
        if (size == 4)
        {
            if (i == 0)
            {
                v = 4.0 / 100.0;
            }
            if (i == 1)
            {
                v = 3.0 / 100.0;
            }
            if (i == 2)
            {
                v = 15.0 / 100.0;
            }
            if (i == 3)
            {
                v = 0;
            }
        }
    }

    if (key == 'S')
    {
        if (size == 4)
        {
            if (i == 0)
            {
                v = 15.0 / 100.0;
            }
            if (i == 1)
            {
                v = 35.0 / 100.0;
            }
            if (i == 2)
            {
                v = 55.0 / 100.0;
            }
            if (i == 3)
            {
                v = 0;
            }
        }
    }

    if (key == 'D')
    {
        if (size == 4)
        {
            if (i == 0)
            {
                v = 69.0 / 100.0;
            }
            if (i == 1)
            {
                v = 53.0 / 100.0;
            }
            if (i == 2)
            {
                v = 54.0 / 100.0;
            }
            if (i == 3)
            {
                v = 53.0 / 100.0;
            }
        }
    }

    if (key == 'G')
    {
        if (size == 4)
        {
            if (i == 0)
            {
                v = 9.0 / 100.0;
            }
            if (i == 1)
            {
                v = 7.0 / 100.0;
            }
            if (i == 2)
            {
                v = 9.0 / 100.0;
            }
            if (i == 3)
            {
                v = 0.0 / 100.0;
            }
        }
    }

    if (key == 'H')
    {
        if (size == 4)
        {
            if (i == 0)
            {
                v = 12.0 / 100.0;
            }
            if (i == 1)
            {
                v = 17.0 / 100.0;
            }
            if (i == 2)
            {
                v = 22.0 / 100.0;
            }
            if (i == 3)
            {
                v = 0.0 / 100.0;
            }
        }
    }

    if (key == ' ')
    {
        v = p;
    }

    if (v >= 0)
    {
        curves[i]->addPoint(p, v);
        curves[i]->build();
        return true;
    }

    return false;


}
