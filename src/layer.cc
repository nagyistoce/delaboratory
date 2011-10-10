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

deLayer::deLayer(const std::string& _name, deColorSpace _colorSpace, int _index, int _sourceLayer)
:name(_name), colorSpace(_colorSpace), index(_index), sourceLayer(_sourceLayer)
{
//    std::cout << "create layer with _index " << _index << std::endl;
//    std::cout << "create layer with index " << index << std::endl;
    actionFrame = NULL;
    blendFrame = NULL;
}

deLayer::~deLayer()
{
    if (actionFrame)
    {
        actionFrame->Close();
    }
    if (blendFrame)
    {
        blendFrame->Close();
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

void deLayer::setActionFrame(deActionFrame* frame)
{
    actionFrame = frame;
}

void deLayer::createActionFrame(wxWindow* parent)
{
}

void deLayer::closeBlendFrame()
{
    blendFrame = NULL;
}

void deLayer::setBlendFrame(deBlendFrame* frame)
{
    blendFrame = frame;
}

void deLayer::createBlendFrame(wxWindow* parent)
{
}

void deLayer::onImageClick(deValue x, deValue y)
{
    if (actionFrame)
    {
        actionFrame->onImageClick(x, y);
    }
}

void deLayer::save(xmlNodePtr node)
{
    {
        xmlNodePtr child = xmlNewChild(node, NULL, xmlCharStrdup("type"), NULL);
        xmlNodeSetContent(child, xmlCharStrdup(getType().c_str()));
    }

    {
        xmlNodePtr child = xmlNewChild(node, NULL, xmlCharStrdup("name"), NULL);
        xmlNodeSetContent(child, xmlCharStrdup(name.c_str()));
    }

    {
        std::ostringstream oss;
        oss << index;
        xmlNodePtr child = xmlNewChild(node, NULL, xmlCharStrdup("index"), NULL);
        xmlNodeSetContent(child, xmlCharStrdup(oss.str().c_str()));
    }        

    {
        std::ostringstream oss;
        oss << sourceLayer;
        xmlNodePtr child = xmlNewChild(node, NULL, xmlCharStrdup("source"), NULL);
        xmlNodeSetContent(child, xmlCharStrdup(oss.str().c_str()));
    }        

    {
        std::string c = getColorSpaceName(colorSpace);
        xmlNodePtr child = xmlNewChild(node, NULL, xmlCharStrdup("color_space"), NULL);
        xmlNodeSetContent(child, xmlCharStrdup(c.c_str()));
    }        

}
