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

#ifndef _DE_LAYER_FACTORY_H
#define _DE_LAYER_FACTORY_H

class deLayer;
class deLayerStack;
#include <string>
#include <list>

class deLayerFactory
{
    private:
    public:
        deLayerFactory();
        virtual ~deLayerFactory();

        deLayer* createLayer(const std::string& type, deLayerStack& stack, int index, const std::string& name);
        void getSupportedLayers(std::list<std::string>& layers);
};

#endif
