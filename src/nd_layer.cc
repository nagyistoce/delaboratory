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

#include "nd_layer.h"
#include "nd_frame.h"
#include "blend.h"
#include "preview_stack.h"
#include "size.h"
#include "preview.h"
#include "project.h"
#include "nd.h"

deNDLayer::deNDLayer(deLayerStack& _stack, int _index, const std::string& _name)
:deLayer(_stack, _index, _name), ndType(*this), blendMode(*this), channels(*this), xCenter(*this, "x center", -1, 1), yCenter(*this, "y center", -1, 1), power(*this, "power", -1, 1)
{
    blendMode.setBlendMode(deBlendMultiply);
    clearEnabledChannels();
}

deNDLayer::~deNDLayer()
{
}

dePreview* deNDLayer::createPreview(dePreviewStack& previewStack)
{
    const dePreview* sourcePreview = previewStack.getPreview(sourceLayer.getIndex());

    if (!sourcePreview)
    {
        return NULL;
    }

    const deSize& sourceSize = sourcePreview->getSize();

    dePreview* preview = new dePreview(colorSpace.getColorSpace(), sourceSize);

    deND nd;
    nd.setType(ndType.getNDType());
    nd.setXCenter(xCenter.getValue());
    nd.setYCenter(yCenter.getValue());
    nd.setPower(power.getValue());

    blend(*sourcePreview, nd, *preview, blendMode.getBlendMode(), channels.getChannels());

    return preview;
}

deActionFrame* deNDLayer::createActionFrame(wxWindow* parent, int layerNumber, deProject* project)
{
    return new deNDFrame(parent, *this, project->getPreviewStack(), layerNumber);
}

void deNDLayer::onChangeColorSpace()
{
    clearEnabledChannels();
}

void deNDLayer::enableChannel(int c)
{
    channels.insert(c);
}

void deNDLayer::clearEnabledChannels()
{
    channels.clear();
}

const deChannels& deNDLayer::getEnabledChannels() const
{
    return channels.getChannels();
}

void deNDLayer::saveSpecific(xmlNodePtr node)
{
    channels.save(node, "channels");
    xCenter.save(node, "x_center");
    yCenter.save(node, "y_center");
    power.save(node, "power");
    blendMode.save(node, "blend_mode");
}

void deNDLayer::loadSpecific(xmlNodePtr node)
{
    xmlNodePtr child = node->xmlChildrenNode;

    while (child)
    {
        if ((!xmlStrcmp(child->name, xmlCharStrdup("channels")))) 
        {
            channels.load(child);
        }

        if ((!xmlStrcmp(child->name, xmlCharStrdup("x_center")))) 
        {
            xCenter.load(child);
        }

        if ((!xmlStrcmp(child->name, xmlCharStrdup("y_center")))) 
        {
            yCenter.load(child);
        }

        if ((!xmlStrcmp(child->name, xmlCharStrdup("power")))) 
        {
            power.load(child);
        }

        if ((!xmlStrcmp(child->name, xmlCharStrdup("blend_mode")))) 
        {
            blendMode.load(child);
        }

        child = child->next;
    }
}
