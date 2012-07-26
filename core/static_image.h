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

#ifndef _DE_STATIC_IMAGE_H
#define _DE_STATIC_IMAGE_H

#include "color_space.h"
#include "mutex_read_write.h"
#include "size.h"
#include "mutex.h"
#include <vector>

class deStaticImage
{
    private:
        deColorSpace colorSpace;
        std::vector<deValue*> channels;
        std::vector<deMutexReadWrite*> mutexes;
        deSize size;
        mutable deMutex mutex;
        int lastRotate;

        const deValue* startReadStatic(int index);
        void finishReadStatic(int index);

        deStaticImage(const deStaticImage& i);
        deStaticImage& operator = (const deStaticImage& i);

    public:
        deStaticImage();

        virtual ~deStaticImage();

        void setColorSpace(deColorSpace c);
        deColorSpace getColorSpace() const;

        deValue* startWriteStatic(int index);
        void finishWriteStatic(int index);

        void setSize(const deSize& _size);
        deSize getStaticImageSize() const;

        void lock();
        void unlock();

        void setInfo(const std::string& s);

        bool isEmpty() const;

        void copyToChannel(int channel, deValue* destination, deValue z_x1, deValue z_y1, deValue z_x2, deValue z_y2, deSize destinationSize, bool mirrorX, bool mirrorY, int rotate, deValue contrast);

        deValue getAspect() const;
};

#endif
