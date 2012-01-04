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

#include "layer.h"
#include "action_frame.h"
#include "blend_frame.h"
#include <sstream>
#include "xml.h"
#include "str.h"

deLayer::deLayer(const std::string& _name, deColorSpace _colorSpace, int _index, int _sourceLayer)
:name(_name), colorSpace(_colorSpace), index(_index), sourceLayer(_sourceLayer)
{
    actionFrame = NULL;
    blendFrame = NULL;
}

deLayer::~deLayer()
{
    assert(!actionFrame);
    assert(!blendFrame);
}

void deLayer::closeFrames()
{
    if (actionFrame)
    {
        deFrame* frame = actionFrame;
        actionFrame->beforeClose();
        frame->Close();
    }
    if (blendFrame)
    {
        deFrame* frame = blendFrame;
        blendFrame->beforeClose();
        frame->Close();
    }
}

deColorSpace deLayer::getColorSpace() const
{
    return colorSpace;
}


std::string deLayer::getName() const
{
    return name;
}

bool deLayer::hasAction() const
{
    return false;
}

bool deLayer::hasBlending() const
{
    return false;
}

bool deLayer::canDisable() const
{
    return false;
}

bool deLayer::isEnabled() const
{
    return true;
}

void deLayer::setEnabled(bool e)
{
}

void deLayer::closeActionFrame()
{
    actionFrame = NULL;
}

void deLayer::setActionFrame(deFrame* frame)
{
    actionFrame = frame;
}

void deLayer::closeBlendFrame()
{
    blendFrame = NULL;
}

void deLayer::setBlendFrame(deBlendFrame* frame)
{
    blendFrame = frame;
}

bool deLayer::onImageClick(deValue x, deValue y)
{
    if (actionFrame)
    {
        deActionFrame* trueActionFrame = dynamic_cast<deActionFrame*>(actionFrame);
        if (trueActionFrame)
        {
            trueActionFrame->onImageClick(x, y);
            return true;    
        }            
    }
    return false;
}

void deLayer::saveCommon(xmlNodePtr node)
{
    saveChild(node, "type", getType());
    saveChild(node, "name", name);
    saveChild(node, "index", str(index));
    saveChild(node, "source", str(sourceLayer));
    saveChild(node, "color_space", getColorSpaceName(colorSpace));
}

bool deLayer::checkActionFrame() const
{
    return actionFrame != NULL;
}

bool deLayer::checkBlendFrame() const
{
    return blendFrame != NULL;
}

void deLayer::onKey(int key)
{
    if (actionFrame)
    {
        actionFrame->onKey(key);
    }
}

void deLayer::onUpdateProperties()
{
    if (actionFrame)
    {
        actionFrame->onUpdateProperties();
    }
    if (blendFrame)
    {
        blendFrame->onUpdateProperties();
    }
}

void deLayer::updateImageThreadCall()
{
    updateImage();
}
