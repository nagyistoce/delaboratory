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

#ifndef _DE_PROPERTY_CHOICE_UI_H
#define _DE_PROPERTY_CHOICE_UI_H

#include "choice.h"
class dePropertyChoice;
class deLayerProcessor;
class deLayerFrame;

class dePropertyChoiceUI:public deChoice
{
    private:
        dePropertyChoice& property;
        deLayerProcessor& layerProcessor;

        int layerIndex;

        deLayerFrame& parent;

    public:
        dePropertyChoiceUI(deWindow& window, dePropertyChoice& _property, deLayerProcessor& _layerProcessor, int _layerIndex, deLayerFrame& _parent);
        virtual ~dePropertyChoiceUI();

        virtual void onChoose(int index);

        void setFromProperty();

};        


#endif
