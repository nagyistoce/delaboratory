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

#ifndef _DE_ZOOM_PANEL_H
#define _DE_ZOOM_PANEL_H

#include <wx/wx.h>
class deProject;

class deZoomPanel:public wxPanel
{
    private:
        deProject& project;
        wxButton* full;
        wxButton* max;
        wxCheckBox* realtime;
    public:
        deZoomPanel(wxWindow* parent, deProject& _project);
        virtual ~deZoomPanel();

        void click(wxCommandEvent &event);

};

#endif