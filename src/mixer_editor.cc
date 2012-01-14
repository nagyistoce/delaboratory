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

#include "mixer_editor.h"
#include "color_space.h"
#include "mixer_layer.h"
#include "mixer_editor_channel.h"
#include "layer_processor.h"
#include "str.h"

deMixerEditor::deMixerEditor(wxWindow *parent, deActionLayer& _layer, deLayerProcessor& _layerProcessor, deLayerFrameManager& _frameManager)
:deActionFrame(parent, _layer, _frameManager)
{
    _layerProcessor.log("creating mixer editor");

    _layerProcessor.log("creating mixer editor - layer name: " + layer.getName());

    deMixerLayer& mixerLayer = dynamic_cast<deMixerLayer&>(_layer);

    deColorSpace colorSpace = layer.getColorSpace();

    _layerProcessor.log("creating mixer editor - sizer");

    wxSizer* sizer = new wxBoxSizer(wxVERTICAL);
    SetSizer(sizer);

    int n = getColorSpaceSize(colorSpace);

    _layerProcessor.log("creating mixer editor - channels: " + str(n));
    int i;
    for (i = 0; i < n; i++)
    {
        _layerProcessor.log("creating mixer editor channel " + str(i));
        deMixerEditorChannel* mixerEditorChannel = new deMixerEditorChannel(this, mixerLayer, i, _layerProcessor);
        sizer->Add(mixerEditorChannel);
        channels.push_back(mixerEditorChannel);
    }
    _layerProcessor.log("creating mixer editor - layout and fit");
    sizer->Layout();

    Fit();

    _layerProcessor.log("created mixer editor");
}

deMixerEditor::~deMixerEditor()
{
}

void deMixerEditor::onImageClick(deValue x, deValue y)
{
}