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

#include "property_value_slider.h"
#include "property_value.h"

dePropertyValueSlider::dePropertyValueSlider(wxWindow *parent, int _sliderRange, dePropertyValue& _property)
:deSlider(parent, _property.getName(), _sliderRange, _property.getMin(), _property.getMax(), _property.getDefault()),
property(_property)
{
}

dePropertyValueSlider::~dePropertyValueSlider()
{
}

void dePropertyValueSlider::onValueChange(deValue value, bool finished)
{
}