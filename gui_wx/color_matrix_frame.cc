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

#include "color_matrix_frame.h"
#include "color_matrix.h"
#include "gradient_panel.h"
#include "project.h"
#include "layer_stack.h"
#include "base_layer.h"
#include "channel_manager.h"
#include "wx/notebook.h"
#include "conversion_processor.h"

#define LAB_TILE_SIZE 20
#define ALL_TILES_SIZE 800

deColorMatrixFrame2::deColorMatrixFrame2(wxWindow *parent, deProject& project, int channelHorizontal, int channelVertical, int channelAverage, int width, int height, dePalette3* palette)
:deHelpFrame(parent, "color matrix")
{

    const deViewManager& viewManager = project.getViewManager();
    int view = viewManager.getView();

    deLayerStack& layerStack = project.getLayerStack();

    const deBaseLayer* layer = layerStack.startReadLayer(view);

    const deImageOld& originalImage = layer->getLayerImage();

    deChannelManager& channelManager = project.getPreviewChannelManager();
    deSize channelSize = originalImage.getChannelSize();
    int n = channelSize.getN();

    deImageOld LABImage(deColorSpaceLAB, channelManager);
    LABImage.allocateChannels();

    deConversionProcessor p;
    deConversionCPU cpu(4);
    p.convertImage(originalImage, LABImage, cpu);

    int nn = width * height;

    int min = (n / 1.5) / nn;

    const deValue* valuesVertical = LABImage.startRead(channelVertical);
    const deValue* valuesHorizontal = LABImage.startRead(channelHorizontal);
    const deValue* valuesAverage = LABImage.startRead(channelAverage);

    if ((!valuesVertical) || (!valuesHorizontal) || (!valuesAverage))
    {
        logError("LABImage broken in color matrix frame");
    }

    int tilesW = width;
    int tilesH = height;

    deColorMatrix colorMatrix(tilesW , tilesH);

    colorMatrix.buildZoomed(valuesHorizontal, valuesVertical, valuesAverage, n, min);

    wxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);
    SetSizer(mainSizer);

    int s = 0;

    wxSizer* LABMapSizer = new wxFlexGridSizer(tilesW, s, s);
    mainSizer->Add(LABMapSizer);

    deConversionProcessor cp;

    int x;
    int y;
    for (y = tilesH - 1; y >= 0; y--)
    {
        for (x = 0; x < tilesW; x++)
        {
            int style = 0;

            deValue vx = 0;
            deValue vy = 0;
            bool center;
            deValue a = colorMatrix.get(x, y, min, vx, vy, center);

            style = wxBORDER_NONE;
            if ((center) && (a < 0))
            {
                style = wxBORDER_SIMPLE;
            }

            deColorPanelOld* colorPanel = new deColorPanelOld(this, wxSize(ALL_TILES_SIZE / width, ALL_TILES_SIZE / height), style);
            LABMapSizer->Add(colorPanel);

            if (a >= 0)
            {

                deValue v1 = 0;
                deValue v2 = 0;
                deValue v3 = 0;
                switch (channelHorizontal)
                {
                    case 0:
                        v1 = vx;
                        break;
                    case 1:
                    {
                        v2 = vx;
                        break;
                    }                        
                    case 2:
                        v3 = vx;
                        break;
                    default:
                        break;
                }
                switch (channelVertical)
                {
                    case 0:
                        v1 = vy;
                        break;
                    case 1:
                        v2 = vy;
                        break;
                    case 2:
                        v3 = vy;
                        break;
                    default:
                        break;
                }
                switch (channelAverage)
                {
                    case 0:
                        v1 = a;
                        break;
                    case 1:
                        v2 = a;
                        break;
                    case 2:
                        v3 = a;
                        break;
                    default:
                        break;
                }

                deValue r;
                deValue g;
                deValue b;
                deValue z;
                cp.convert(deColorSpaceLAB, v1, v2, v3, 0, deColorSpaceRGB, r, g, b, z);
                colorPanel->setRGB(r, g, b);
            }                
            else
            {
            }

        }
    }     
    LABImage.finishRead(channelVertical);
    LABImage.finishRead(channelHorizontal);
    LABImage.finishRead(channelAverage);
    Fit();

    layerStack.finishReadLayer(view);
}

deColorMatrixFrame2::~deColorMatrixFrame2()
{
}

#define LAB_TILES 20

deColorMatrixFrame::deColorMatrixFrame(wxWindow *parent, deProject& _project, int tileRW, int tileRH, int tileW, int tileH, int palW, int palH, int palSize, deValue margin)
:deHelpFrame(parent, "color matrix"), project(_project)
{
    wxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);
    SetSizer(mainSizer);

    wxNotebook* notebook = new wxNotebook(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0, _T("notebook"));
    mainSizer->Add(notebook, 1, wxEXPAND);

    wxPanel* imagePanel = new wxPanel(notebook);
    notebook->AddPage(imagePanel, _T("image"));
    wxSizer* imageSizer = new wxBoxSizer(wxVERTICAL);
    imagePanel->SetSizer(imageSizer);

    wxPanel* LABPanel = new wxPanel(notebook);
    notebook->AddPage(LABPanel, _T("LAB"));
    wxSizer* LABSizer = new wxBoxSizer(wxVERTICAL);
    LABPanel->SetSizer(LABSizer);

    wxPanel* palettePanel = new wxPanel(notebook);
    notebook->AddPage(palettePanel, _T("palette"));
    wxSizer* paletteSizer = new wxBoxSizer(wxVERTICAL);
    palettePanel->SetSizer(paletteSizer);

    palette = NULL;
    palette2 = NULL;
    paletteLAB = NULL;

    const deViewManager& viewManager = project.getViewManager();
    int view = viewManager.getView();

    deLayerStack& layerStack = project.getLayerStack();

    const deBaseLayer* layer = layerStack.startReadLayer(view);

    const deImageOld& image = layer->getLayerImage();
    deColorSpace colorSpace = image.getColorSpace();

    deConversionProcessor cp;

    palette = new dePalette3(colorSpace);
    paletteLAB = new dePalette3(deColorSpaceLAB);

    deSize channelSize = image.getChannelSize();

    int cs = channelSize.getW();

    int w = channelSize.getW() / tileW;
    int h = channelSize.getH() / tileH;

    int n = w * h;

    int s = 2;

    wxSizer* sizer = new wxFlexGridSizer(w, s, s);
    imageSizer->Add(sizer);

    int i;

    int y = 0;
    int x = 0;

    for (i = 0; i < n; i++)
    {
        deColorPanelOld* colorPanel = new deColorPanelOld(imagePanel, wxSize(tileRW, tileRH), 0);
        sizer->Add(colorPanel);

        int x1 = x * tileW;
        int x2 = (x + 1) * tileW;
        int y1 = y * tileH;
        int y2 = (y + 1) * tileH;

        deValue sum1 = 0;
        deValue sum2 = 0;
        deValue sum3 = 0;

        deValue v1;
        deValue v2;
        deValue v3;

        int xx;
        int yy;
        const deValue* values1 = image.startRead(0);
        const deValue* values2 = image.startRead(1);
        const deValue* values3 = image.startRead(2);

        for (yy = y1; yy < y2; yy++)
        {
            int p = cs * yy + x1;
            for (xx = x1; xx < x2; xx++)
            {
                v1 = values1[p];
                v2 = values2[p];
                v3 = values3[p];
                sum1 += v1;
                sum2 += v2;
                sum3 += v3;
                p++;
            }
        }

        image.finishRead(0);
        image.finishRead(1);
        image.finishRead(2);

        int ts = tileW * tileH;

        sum1 /= ts;
        sum2 /= ts;
        sum3 /= ts;
        deValue sum4 = 0;

        palette->addColor(deColor4(sum1, sum2, sum3, sum4));

        deValue r;
        deValue g;
        deValue b;

        deValue z;
        cp.convert(colorSpace, sum1, sum2, sum3, 0, deColorSpaceRGB, r, g, b, z);

        deValue L;
        deValue A;
        deValue B;

        cp.convert(colorSpace, sum1, sum2, sum3, 0, deColorSpaceLAB, L, A, B, z);

        paletteLAB->addColor(deColor4(L, A, B, 0));

        colorPanel->setRGB(r, g, b);

        x++;
        if (x == w)
        {
            x = 0;
            y++;
        }
    }

    deValue minA;
    deValue maxA;
    paletteLAB->getMinMax(2, minA, maxA);
    deValue minB;
    deValue maxB;
    paletteLAB->getMinMax(3, minB, maxB);

    deValue deltaA = maxA - minA;
    deValue deltaB = maxB - minB;
    deValue delta = deltaA;
    if (deltaB > delta)
    {
        delta = deltaB;
    }

    deValue step = delta / LAB_TILES;

    int tiles = deltaA / step + 1;

    wxSizer* LABMapSizer = new wxFlexGridSizer(tiles, s, s);
    LABSizer->Add(LABMapSizer);

    deValue A;
    deValue B;
    deValue rB;


    for (rB = minB; rB < maxB; rB += step)
    {
        B = maxB + minB - rB;

        for (A = minA; A < maxA; A += step)
        {
            deColorPanelOld* colorPanel = new deColorPanelOld(LABPanel, wxSize(LAB_TILE_SIZE, LAB_TILE_SIZE), 0);
            LABMapSizer->Add(colorPanel);

            deValue L = 1.0;

            if (paletteLAB->find23(A, A + step, B, B + step, L))
            {
                deValue r;
                deValue g;
                deValue b;
                deValue z;
                cp.convert(deColorSpaceLAB, L, A, B, 0, deColorSpaceRGB, r, g, b, z);
                colorPanel->setRGB(r, g, b);
            }                
        }
    }

    palette2 = new dePalette3(colorSpace);

    palette2->optimize(*palette, palSize, margin);

    int s2 = 5;

    wxSizer* sizerS = new wxStaticBoxSizer(wxHORIZONTAL, palettePanel,  _T("palette"));
    paletteSizer->Add(sizerS);
    
    wxSizer* palSizer = new wxFlexGridSizer(palSize / 2, s2, s2);
    sizerS->Add(palSizer);

    for (i = 0; i < palette2->getSize(); i++)
    {
        deColorPanelOld* colorPanel = new deColorPanelOld(palettePanel, wxSize(palW, palH), 0);
        palSizer->Add(colorPanel);

        deValue r;
        deValue g;
        deValue b;

        deColor4 c = palette2->getColor(i);

        deValue z;
        cp.convert(colorSpace, c.getV1(), c.getV2(), c.getV3(), 0, deColorSpaceRGB, r, g, b, z);

        colorPanel->setRGB(r, g, b);
    }

    Fit();

    layerStack.finishReadLayer(view);

}

deColorMatrixFrame::~deColorMatrixFrame()
{
    if (palette)
    {
        delete palette;
    }        
    if (palette2)
    {
        delete palette2;
    }        
    if (paletteLAB)
    {
        delete paletteLAB;
    }        
}

