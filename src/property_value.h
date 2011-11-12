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

#ifndef _DE_PROPERTY_VALUE_H
#define _DE_PROPERTY_VALUE_H

#include "value.h"
#include <string>
#include <libxml/parser.h>
class deActionLayer;

class dePropertyValue
{
    private:
        deValue value;
        deActionLayer& layer;
        std::string name;
        std::string label;

        deValue min;
        deValue max;
        deValue defaultValue;
    public:
        dePropertyValue(deActionLayer& _layer, const std::string& _name);
        virtual ~dePropertyValue();

        void set(deValue _value);
        void setAndUpdate(deValue _value);
        deValue get() const;

        void save(xmlNodePtr root) const;
        void load(xmlNodePtr root);

        std::string getName() const;
        deValue getMin() const;
        deValue getMax() const;
        deValue getDefault() const;
};

#endif