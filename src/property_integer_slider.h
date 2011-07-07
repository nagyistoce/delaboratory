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

#ifndef _DE_PROPERTY_VALUE_SLIDER_H
#define _DE_PROPERTY_VALUE_SLIDER_H

#include "slider.h"
class dePropertyInteger;

class dePropertyIntegerSlider:public deSlider
{
    private:
        dePropertyInteger& property;

    public:
        dePropertyIntegerSlider(wxWindow *parent, dePropertyInteger& _property, int range);
        virtual ~dePropertyIntegerSlider();

        virtual void onValueChange(deValue integer);
};        

#endif
