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

#ifndef _DE_SEMAPHORE_H
#define _DE_SEMAPHORE_H

class deSemaphoreImpl;

class deSemaphore
{
    private:
        deSemaphoreImpl* impl;
        deSemaphore(const deSemaphore& s);
        deSemaphore& operator =(const deSemaphore& s);

    public:
        deSemaphore(int a, int b);
        ~deSemaphore();

        void wait();
        void post();
        
};


#endif
