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

#include "apply_image_frame.h"
#include "apply_image_layer.h"
#include "property_choice_ui.h"
#include "property_boolean_ui.h"
#include "layer_processor.h"

deApplyImageFrame::deApplyImageFrame(wxWindow *parent, deActionLayer& _layer, deLayerProcessor& _layerProcessor, deLayerFrameManager& _frameManager)
:deActionFrame(parent, _layer, _frameManager), layerProcessor(_layerProcessor)
{
    deApplyImageLayer& applyImageLayer = dynamic_cast<deApplyImageLayer&>(layer);

    wxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);
    SetSizer(mainSizer);

    appliedLayer = new dePropertyChoiceUI(this, applyImageLayer.getAppliedLayer(), applyImageLayer, layerProcessor);
    mainSizer->Add(appliedLayer);

    applySingleChannel = new dePropertyBooleanUI(this, applyImageLayer.getApplySingleChannel(), applyImageLayer, layerProcessor);
    mainSizer->Add(applySingleChannel);

    int i;
    for (i = 0; i < 4; i++)
    {
        int style = 0;
        if (i == 0)
        {
            style = wxRB_GROUP;
        }
        wxRadioButton* b = new wxRadioButton(this, wxID_ANY, _T(""), wxDefaultPosition, wxDefaultSize, style);
        mainSizer->Add(b, 0);
        channels[i] = b;
    }

    setChannels();

    Fit();

    Connect(wxEVT_COMMAND_RADIOBUTTON_SELECTED, wxCommandEventHandler(deApplyImageFrame::select));
}

deApplyImageFrame::~deApplyImageFrame()
{
}

void deApplyImageFrame::select(wxCommandEvent &event)
{
    deApplyImageLayer& applyImageLayer = dynamic_cast<deApplyImageLayer&>(layer);

    int i = event.GetId();
    int j;
    for (j = 0; j < 4; j++)
    {
        if (channels[j]->GetId() == i)
        {
            applyImageLayer.setAppliedChannel(j);
        }
    }

    int index = layer.getIndex();
    layerProcessor.markUpdateAllChannels(index);
}

void deApplyImageFrame::setChannels()
{
    deApplyImageLayer& applyImageLayer = dynamic_cast<deApplyImageLayer&>(layer);

    deColorSpace colorSpace = applyImageLayer.getAppliedColorSpace();
    int n = getColorSpaceSize(colorSpace);
    int s = applyImageLayer.getAppliedChannel();
    int i;
    for (i = 0; i < 4; i++)
    {
        if (i < n)
        {
            std::string name = getChannelName(colorSpace, i);
            channels[i]->SetLabel(wxString::FromAscii(name.c_str()));
            channels[i]->Show();
        }
        else
        {
            channels[i]->Hide();
        }
        if (applyImageLayer.isSingleChannel())
        {
            channels[i]->Enable();
        }
        else
        {
            channels[i]->Disable();
        }
        if (i == s)
        {
            channels[i]->SetValue(1);
        }
    }
}

void deApplyImageFrame::onUpdateProperties()
{
    setChannels();
}

