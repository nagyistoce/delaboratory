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

#ifndef _DE_RAW_MODULE_H
#define _DE_RAW_MODULE_H

#include <string>
class deStaticImage;
#include "color_space.h"
#include "dcraw_support.h"
#include "mutex.h"

class deRawModule
{
    private:
        mutable deMutex mutex;

        deRawLoader* loader;

        deRawModule(const deRawModule&);
        deRawModule& operator =(const deRawModule&);

        std::string dcraw_version;
        
    public:
        deRawModule();
        virtual ~deRawModule();

        void onInit();

        std::string getVersion() const;
        bool loadRAW(const std::string& fileName, deStaticImage& image, bool half, bool srgb, bool brighten);

        bool updateRawLoading(bool& failure);

        bool isActive() const;


};

#endif
