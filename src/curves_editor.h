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

#ifndef _DE_CURVES_EDITOR_H
#define _DE_CURVES_EDITOR_H

#include "action_frame.h"
class deCurvesPanel;
class deGradientPanel1;
class deLayerProcessor;
class deChannelManager;

class deCurvesEditor:public deActionFrame
{
    private:
        deCurvesPanel* curvesPanel;

        void choose(wxCommandEvent &event);
        void click(wxCommandEvent &event);

        deGradientPanel1* leftBar;
        deGradientPanel1* bottomBar;

        wxChoice* channelChoice;
        wxButton* reset;
        wxButton* invert;
        wxButton* const0;
        wxButton* const05;
        wxButton* const1;
        wxButton* angle1;
        wxButton* angle2;
        wxButton* angle3;
        wxButton* angle4;
        wxButton* angle5;
        wxButton* random1;
        wxButton* random2;
        wxButton* random3;
        wxButton* random4;
        wxButton* random5;
        wxButton* s1;
        wxButton* s2;
        wxButton* s3;
        wxButton* is1;
        wxButton* is2;

    public:
        deCurvesEditor(wxWindow *parent, deLayerOld& _layer, deLayerProcessor& _layerProcessor, deLayerFrameManager& _frameManager, int _layerIndex, deChannelManager& _channelManager);
        virtual ~deCurvesEditor();

        virtual bool onImageClick(deValue x, deValue y);
        virtual void onKey(int key);

};


#endif
