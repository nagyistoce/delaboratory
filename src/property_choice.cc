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

#include "property_choice.h"
#include "str.h"
#include "logger.h"

dePropertyChoice::dePropertyChoice(const std::string& _name, const std::vector<std::string> _choices)
:deProperty(_name), choices(_choices)
{
    value = 0;
}

dePropertyChoice::~dePropertyChoice()
{
}

void dePropertyChoice::set(std::string s)
{
    std::vector<std::string>::const_iterator i = choices.begin();
    int index = 0;
    while (i != choices.end())
    {
        if (*i == s)
        {
            value = index;
            return;
        }
        i++;
        index++;
    }
    logError("can't set choice value " + s);
    value = -1;
}

std::string dePropertyChoice::get() const
{
    if (value < 0)
    {
        return "";
    }
    if ((unsigned)value >= choices.size())
    {
        return "";
    }
    return choices[value];
}

int dePropertyChoice::getIndex() const
{
    return value;
}

void dePropertyChoice::setIndex(int index)
{
    value = index;
}

std::vector<std::string> createNumbers(int index)
{
    std::vector<std::string> result;
    int i;
    for (i = 0; i < index; i++)
    {
        result.push_back(str(i));
    }
    return result;
}
