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

#include "str_wx.h"

std::string str(wxString& ws)
{
    char cstring[1024];
    strncpy(cstring, (const char*)ws.mb_str(wxConvUTF8), 1023);

    return cstring;
}    

wxString str2wx(const std::string& s)
{
    const char* c = s.c_str();
    wxString result(c, wxConvUTF8);

    return result;
}    
