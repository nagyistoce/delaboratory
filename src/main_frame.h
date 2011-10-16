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

#ifndef _DE_MAIN_FRAME_H
#define _DE_MAIN_FRAME_H

#include "wx/wx.h"
class deProject;
class deImageAreaPanel;
class deLayerGridPanel;

class deMainFrame: public wxFrame
{
private:
    deProject* project;
    wxPanel* hPanel;
    wxPanel* topPanel;
    deLayerGridPanel* layerGridPanel;
    wxPanel* controlPanel;
    wxSizer* mainSizer;
    deImageAreaPanel* leftPanel;
    bool full;

	void onTestImage(wxCommandEvent& event);
	void onQuit(wxCommandEvent& event);
	void onSaveProject(wxCommandEvent& event);
	void onNewProject(wxCommandEvent& event);
	void onOpenProject(wxCommandEvent& event);
	void onHelpColorSpaces(wxCommandEvent& event);
	void onHelpColorSpaces2(wxCommandEvent& event);
	void onHelpColorSpaces3(wxCommandEvent& event);
	void onHelpColorSpaces4(wxCommandEvent& event);
	void onHelpColorSpaces5(wxCommandEvent& event);
	void onLABColors1(wxCommandEvent& event);
	void onLABColors2(wxCommandEvent& event);
	void onLABColors5(wxCommandEvent& event);
	void onMemoryInfo(wxCommandEvent& event);

public:
	deMainFrame(const wxSize& size, deProject* _project);

    void showPanels();
    void hidePanels();

    void onKey(int key);

	DECLARE_EVENT_TABLE()
};


#endif