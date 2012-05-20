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

#include "basic_layer.h"
#include "process_linear.h"
#include "color_space_utils.h"
#include "channel_manager.h"

deBasicLayer::deBasicLayer(deColorSpace _colorSpace, int _sourceLayer, deLayerStack& _layerStack, deChannelManager& _channelManager, deViewManager& _viewManager)
:deLayerOld(_colorSpace, _sourceLayer, _layerStack, _channelManager)
{
    getBasicSettings(colorSpace, settings1, settings2);

    std::copy(settings1.begin(), settings1.end(), std::back_inserter(settings));
    std::copy(settings2.begin(), settings2.end(), std::back_inserter(settings));

    int n = settings.size();
    int i;
    for (i = 0; i < n; i++)
    {
        deBasicSetting& setting = settings[i];
        std::string n = setting.getName();
        dePropertyValue* p = new dePropertyValue(n);
        p->setMin(setting.getMin());
        p->setMax(setting.getMax());
        int c = setting.getChannel();
        if (c >= 0)
        {
            p->setChannelInProperty(c);
        }
        basicProperties.push_back(p);
    }

    int nn = getColorSpaceSize(colorSpace);
    curves = new deBaseCurve[nn];

    shiftIndex = -1;
    shiftValue = 0.0;

    int j;
    for (j = 0; j < n; j++)
    {
        deBasicSetting& s = settings[j];
        if (s.isShift())
        {
            for (i = 0; i < nn; i++)
            {
                if (s.affects(i))
                {
                    shiftIndex = i;
                }
            }        
        }
    }
}

deBasicLayer::~deBasicLayer()
{
    int n = settings.size();
    int i;
    for (i = 0; i < n; i++)
    {
        dePropertyValue* p = basicProperties[i];
        delete p;
    }

    delete [] curves;
}

bool deBasicLayer::isChannelNeutral(int index)
{
    return false;
}    

void deBasicLayer::reset()
{
    int nn = settings.size();
    int j;
    for (j = 0; j < nn; j++)
    {
        basicProperties[j]->set(0.0);
    }
}

void deBasicLayer::save(xmlNodePtr root)
{
    saveCommon(root);
    saveBlend(root);
}

void deBasicLayer::load(xmlNodePtr root)
{
    loadBlend(root);

    xmlNodePtr child = root->xmlChildrenNode;

    while (child)
    {
        child = child->next;
    }        
}

void deBasicLayer::updateCurve(int i)
{
    deValue brightness = 0.0;
    deValue contrast = 0.0;

    int n = settings.size();
    int j;
    for (j = 0; j < n; j++)
    {
        deBasicSetting& s = settings[j];
        if (s.affects(i))
        {
            deValue scale = s.getScale();
            dePropertyValue* p = basicProperties[j];
            if (s.isContrast())
            {
                contrast += scale * p->get();
            }
            if (s.isBrightness())
            {
                brightness += scale * p->get();
            }
        }
    }

    deBaseCurve& curve = curves[i];

    deValue p1 = 1.0 / 4.0;
    deValue p2 = 1.0 - 1.0 / 4.0;

    deValue h0 = brightness + 0.0  + (-0.5 * contrast);
    deValue h1 = brightness + p1   + (p1 - 0.5) * contrast;
    deValue h2 = brightness + p2   + (1.0 - p2) * contrast;
    deValue h3 = brightness + 1.0  + 0.5 * contrast;

    clip(h0);
    clip(h1);
    clip(h2);
    clip(h3);

    curve.clearPoints();
    curve.addPoint(0, h0);
    curve.addPoint(p1, h1);
    curve.addPoint(p2, h2);
    curve.addPoint(1, h3);
    curve.build();

}

int deBasicLayer::getNumberOfSettings()
{
    int n = settings.size();
    return n;
}

int deBasicLayer::getSeparator()
{
    int n = settings1.size();
    return n;
}

dePropertyValue* deBasicLayer::getBasicProperty(int n)
{
    dePropertyValue* p = basicProperties[n];
    return p;
}

void deBasicLayer::onUpdateProperties()
{
    int n = getColorSpaceSize(colorSpace);
    int i;
    for (i = 0; i < n; i++)
    {
        updateCurve(i);
    }        

    int nn = settings.size();
    int j;
    for (j = 0; j < nn; j++)
    {
        deBasicSetting& s = settings[j];
        if (s.isShift())
        {
            shiftValue = basicProperties[j]->get();
        }
    }
}

dePropertyValue* deBasicLayer::getBasicProperty(const std::string& name)
{
    int n = settings.size();
    int i;
    for (i = 0; i < n; i++)
    {
        dePropertyValue* p = basicProperties[i];
        if (p->getName() == name)
        {
            return p;
        }
    }

    return NULL;
}

bool deBasicLayer::updateMainImageSingleChannel(int i)
{
    const deImage& sourceImage = getSourceImage();

    int s = sourceImage.getChannelIndex(i);

    if ((isChannelNeutral(i)) || (!isChannelEnabled(i)))
    {
        mainLayerImage.disableChannel(i, s);
        return true;
    }

    deChannel* sourceChannel = channelManager.getChannel(s);
    if (sourceChannel)
    {
        mainLayerImage.enableChannel(i);
        int c = mainLayerImage.getChannelIndex(i);
        deChannel* channel = channelManager.getChannel(c);

        if (channel)
        {
            if (i == shiftIndex)
            {
                shiftChannel(sourceChannel->getPixels(), channel->getPixels(), shiftValue, mainLayerImage.getChannelSize().getN());    
            }
            else
            {
                curves[i].process(sourceChannel->getPixels(), channel->getPixels(), mainLayerImage.getChannelSize().getN());
            }
        }
    }

    return true;

}
