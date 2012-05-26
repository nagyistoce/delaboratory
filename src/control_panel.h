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

#ifndef _DE_CONTROL_PANEL_H
#define _DE_CONTROL_PANEL_H

#include <wx/wx.h>
#include <map>
#include <vector>
#include "color_space.h"
class deProject;
class deLayerProcessor;
class deOperationProcessor;
class deChannelManager;

class deControlPanel:public wxPanel
{
    private:
        deProject& project;
        deLayerProcessor& layerProcessor;
        deOperationProcessor& operationProcessor;
        wxSizer* mainSizer;

        wxButton* exportSingle;
        wxButton* exportAll;
        wxButton* externalEditor;

        std::map<int, deColorSpace> convertButtonsColorSpaces;
        std::vector<wxButton*> convertButtons;

        std::map<int, std::string> actionButtonsNames;
        std::vector<wxButton*> actionButtons;

        deChannelManager& channelManager;

        wxButton* deleteLayer;

        void click(wxCommandEvent &event);

        //bool generateFinalImage(const std::string& app, const std::string& type, const std::string& name, bool saveAll, const std::string& dir);

    public:
        deControlPanel(wxWindow* parent, deProject& _project, deLayerProcessor& _processor, deOperationProcessor& _operationProcessor, deChannelManager& _channelManager);
        ~deControlPanel();


};


#endif
