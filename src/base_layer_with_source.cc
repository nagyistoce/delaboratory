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

#include "base_layer_with_source.h"
#include "layer_stack.h"

deBaseLayerWithSource::deBaseLayerWithSource(deColorSpace _colorSpace, deChannelManager& _channelManager, int _sourceLayerIndex, deLayerStack& _layerStack)
:deBaseLayer(_colorSpace, _channelManager),
sourceLayerIndex(_sourceLayerIndex),
layerStack(_layerStack)
{
}

deBaseLayerWithSource::~deBaseLayerWithSource()
{
}

const deBaseLayer& deBaseLayerWithSource::getSourceLayer() const
{
    const deBaseLayer* layer = layerStack.getLayer(sourceLayerIndex);
    return *layer;
}    

const deImage& deBaseLayerWithSource::getSourceImage() const
{
    return getSourceLayer().getLayerImage();
}

const deImage& deBaseLayerWithSource::getOtherLayerImage(int a) const
{
    deBaseLayer* applied = layerStack.getLayer(a);

    const deImage& appliedImage = applied->getLayerImage();
}    

deColorSpace deBaseLayerWithSource::getSourceColorSpace() const
{
    return getSourceLayer().getColorSpace();
}
