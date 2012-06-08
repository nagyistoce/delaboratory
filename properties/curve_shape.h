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

#ifndef _DE_CURVE_SHAPE_H
#define _DE_CURVE_SHAPE_H

#include <map>
#include "value.h"
#include "curve_point.h"
#include <vector>

class deCurveFunctionBezier;

class deCurveShape
{
    private:
        int size;
        std::vector<deCurveFunctionBezier> functions;

    public:
        deCurveShape(int _size);
        ~deCurveShape();

        void build(const deCurvePoints& points);

        deValue calc(deValue value) const;
};

#endif
