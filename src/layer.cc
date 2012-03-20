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
#include <sstream>
#include "xml.h"
#include "str.h"
#include "layer_processor.h"
#include "logger.h"
#include "property_value.h"

deLayer::deLayer(const std::string& _name, deColorSpace _colorSpace, int _index, int _sourceLayer)
:name(_name), 
mutex(wxMUTEX_RECURSIVE),
colorSpace(_colorSpace), 
index(_index), 
sourceLayer(_sourceLayer)
{
    logMessage("creating layer " + str(index) + " " + name);
}

deLayer::~deLayer()
{
    logMessage("destroying layer " + str(index) + " " + name);
    while (valueProperties.size() > 0)
    {
       std::vector<dePropertyValue*>::iterator i = valueProperties.begin();
       dePropertyValue* p = *i;
       delete p;
       valueProperties.erase(i);
    }       
    logMessage("destroyed layer " + str(index) + " " + name);
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

void deLayer::saveCommon(xmlNodePtr node)
{
    saveChild(node, "type", getType());
    saveChild(node, "name", name);
    saveChild(node, "index", str(index));
    saveChild(node, "source", str(sourceLayer));
    saveChild(node, "color_space", getColorSpaceName(colorSpace));
}

bool deLayer::updateImageThreadCall()
{
//    std::cout << "updateImageThreadCall :(" << std::endl;
    return updateImage();
}

void deLayer::lockLayer()
{
    lockWithLog(mutex, "layer mutex");
}

void deLayer::unlockLayer()
{
    //log("layer " + str(index) + " unlock");
    mutex.Unlock();
}

void deLayer::process(deLayerProcessType type, int channel)
{
    switch (type)
    {
        case deLayerProcessFull:
        {
            processFull();
            break;
        }
        case deLayerProcessSingleChannel:
        {
            processChannel(channel);
            break;
        }
        case deLayerProcessBlend:
        {
            processBlend();
            break;
        }
        default:
            break;
    }
}

void deLayer::processFull()
{
//    std::cout << "processFull :(" << std::endl;
    updateImageThreadCall();
}

void deLayer::processBlend()
{
}

void deLayer::processChannel(int channel)
{
}

std::string deLayer::getLabel() const 
{
    return getType();
}    

int deLayer::registerPropertyValue(const std::string& _name)
{
    dePropertyValue* p = new dePropertyValue(_name);
    valueProperties.push_back(p);
    return valueProperties.size() - 1;
}

dePropertyValue* deLayer::getPropertyValue(int index)
{
    if ((index < 0) || (index >= valueProperties.size()))
    {
        return NULL;
    }
    return valueProperties[index];
}

void deLayer::saveValueProperties(xmlNodePtr root)
{
    int n = getNumberOfValueProperties();
    int i;
    for (i = 0; i < n; i++)
    {
        dePropertyValue* p = getPropertyValue(i);
        p->save(root);
    }
}    

void deLayer::loadValueProperties(xmlNodePtr root)
{
    int n = getNumberOfValueProperties();
    int i;
    for (i = 0; i < n; i++)
    {
        dePropertyValue* p = getPropertyValue(i);
        p->load(root);
    }
}       

dePropertyValue* deLayer::getPropertyValue(const std::string& _name)
{
    int n = getNumberOfValueProperties();
    int i;
    for (i = 0; i < n; i++)
    {
        dePropertyValue* p = getPropertyValue(i);
        if (p->getName() == _name)
        {
            return p;
        }
    }
    return NULL;
}
