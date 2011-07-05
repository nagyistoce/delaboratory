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

#include "nd_type.h"


std::string getNDTypeName(deNDType type)
{
    switch (type)
    {
        case deNDHorizontal:
            return "horizontal";
        case deNDVertical:
            return "vertical";
        case deNDVignette:
            return "vignette";
        case deNDFlat:
            return "flat";
        default:
            return "unknown";
    }
}

deNDType ndTypeFromString(const std::string& s)
{
    if (s == "horizontal")
    {
        return deNDHorizontal;
    }

    if (s == "vertical")
    {
        return deNDVertical;
    }

    if (s == "vignette")
    {
        return deNDVignette;
    }

    if (s == "flat")
    {
        return deNDFlat;
    }

    return deNDInvalid;
}

void getSupportedNDTypes(std::vector<deNDType>& result)
{
    result.push_back(deNDHorizontal);
    result.push_back(deNDVertical);
    result.push_back(deNDVignette);
    result.push_back(deNDFlat);
}
