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

#ifndef _DE_PRESET_H
#define _DE_PRESET_H

#include <string>
#include "value.h"
#include "base_layer_with_properties.h"

class dePreset
{
    private:
        dePreset(const dePreset&);
        dePreset& operator =(const dePreset&);

        std::map<std::string, deValue> numericValues;
        std::vector<std::string> operations;

    protected:
        const std::string name;

    public:
        dePreset(const std::string& _name)
        :name(_name)
        {
        }

        virtual ~dePreset()
        {
        }

        std::string getName() {return name;};

        void apply(deBaseLayerWithProperties& layer) const;
        void addNumericValue(const std::string& n, deValue v);
        void addOperation(const std::string& n);

};


#endif
