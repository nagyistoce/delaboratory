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

#ifndef _DE_SAMPLER_PANEL_H
#define _DE_SAMPLER_PANEL_H

#include "wx/wx.h"
#include <vector>
#include "color_space.h"
#include "gradient_panel.h"
class deSampler;
class deProject;
class deImageOld;

class deSamplerPanel:public wxPanel
{
private:
    deSampler& sampler;
    deProject& project;

    wxChoice* colorSpaceChoice;
    deColorPanelOld* colorPanel;
    wxStaticText* v1;
    wxStaticText* v2;
    wxStaticText* v3;
    wxStaticText* v4;

    wxStaticBoxSizer* sizerS;

    std::vector<deColorSpace> colorSpaces;

    void choose(wxCommandEvent &event);

    void update(const deImageOld& image);

public:
	deSamplerPanel(wxWindow* parent, deSampler& _sampler, deProject& _project);
	virtual ~deSamplerPanel();

    void update();
    void setChoice();

};

#endif
