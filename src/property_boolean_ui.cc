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

#include "property_boolean_ui.h"
#include "property_boolean.h"
#include "layer.h"
#include "layer_processor.h"

dePropertyBooleanUIOld::dePropertyBooleanUIOld(wxWindow *parent, dePropertyBoolean& _property, deLayer& _layer, deLayerProcessor& _layerProcessor, int _layerIndex)
:deCheckBoxOld(parent, _property.getLabel()),
property(_property),
layer(_layer),
layerProcessor(_layerProcessor),
layerIndex(_layerIndex)
{
    setFromProperty();
}

dePropertyBooleanUIOld::~dePropertyBooleanUIOld()
{
}

void dePropertyBooleanUIOld::onCheck(bool c)
{
    property.set(c);

    layerProcessor.markUpdateAllChannels(layerIndex);
}

void dePropertyBooleanUIOld::setFromProperty()
{
    set(property.get());
}

dePropertyBooleanUI::dePropertyBooleanUI(deWindow& window, dePropertyBoolean& _property, deLayerProcessor& _layerProcessor, int _layerIndex)
:deCheckBox(window, _property.getLabel()),
property(_property),
layerProcessor(_layerProcessor),
layerIndex(_layerIndex)
{
    setFromProperty();
}

dePropertyBooleanUI::~dePropertyBooleanUI()
{
}

void dePropertyBooleanUI::onCheck(bool c)
{
    property.set(c);

    layerProcessor.markUpdateAllChannels(layerIndex);
}

void dePropertyBooleanUI::setFromProperty()
{
    set(property.get());
}
