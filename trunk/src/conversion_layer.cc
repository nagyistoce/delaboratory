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

#include "conversion_layer.h"
#include "layer_stack.h"
#include "preview.h"
#include "channels.h"
#include "channel.h"
#include <wx/wx.h>
#include "preview_stack.h"
#include "converter.h"

deConversionLayer::deConversionLayer(deLayerStack& _stack, int _index, const std::string& _name)
:deLayer(_stack, _index, _name)
{
}

deConversionLayer::~deConversionLayer()
{
}

void deConversionLayer::updatePreview(dePreviewStack& previewStack)
{
    const dePreview* sourcePreview = previewStack.getPreview(sourceLayer.getIndex());
    dePreview* preview = previewStack.getPreview(index);

    if ((sourcePreview) && (preview))
    {
        deConverter converter;
        converter.setSource(sourcePreview);
        converter.setDestination(preview);
        converter.convert();
    }
}
