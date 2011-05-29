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

#include "curves_panel.h"
#include "curve.h"
#include "curves_layer.h"
#include <iostream>
#include <wx/dcbuffer.h>
#include "preview_stack.h"
#include "sampler.h"

BEGIN_EVENT_TABLE(deCurvesPanel, wxPanel)
EVT_PAINT(deCurvesPanel::paintEvent)
END_EVENT_TABLE()

#define CURVES_PANEL_SIZE 500

deCurvesPanel::deCurvesPanel(wxWindow* parent, deCurvesLayer& _layer, dePreviewStack& _stack, int _layerNumber)
:wxPanel(parent, wxID_ANY, wxDefaultPosition, wxSize(CURVES_PANEL_SIZE, CURVES_PANEL_SIZE)), layer(_layer), 
 bitmap(CURVES_PANEL_SIZE, CURVES_PANEL_SIZE), stack(_stack), layerNumber(_layerNumber)
{
    marker = -1;

    curve = NULL;
    selectedPoint = -1;

    SetBackgroundColour(*wxBLACK);
    Connect(wxEVT_LEFT_DOWN, wxMouseEventHandler(deCurvesPanel::click));
    Connect(wxEVT_LEFT_UP, wxMouseEventHandler(deCurvesPanel::release));
    Connect(wxEVT_MOTION, wxMouseEventHandler(deCurvesPanel::move));
}

deCurvesPanel::~deCurvesPanel()
{
}

void deCurvesPanel::changeChannel(int _channel)
{
    channel = _channel;
    marker = -1;
    curve = (layer.getCurves()[channel]);
    paint();
}

void deCurvesPanel::paintEvent(wxPaintEvent & evt)
{
    wxPaintDC dc(this);
    render(dc);
}

void deCurvesPanel::paint()
{
    wxClientDC dc(this);
    render(dc);
}

void deCurvesPanel::getPosition(wxMouseEvent &event, deValue& x, deValue &y)
{
    deValue d = 1.0 / (CURVES_PANEL_SIZE - 1);
    x = event.GetX() * d;
    y = 1 - (event.GetY() * d);
}

void deCurvesPanel::drawLine(wxDC& dc, deValue x1, deValue y1, deValue x2, deValue y2)
{
    int xx1 = (CURVES_PANEL_SIZE - 1) * x1;
    int xx2 = (CURVES_PANEL_SIZE - 1) * x2;
    int yy1 = (CURVES_PANEL_SIZE - 1) * (1 - y1);
    int yy2 = (CURVES_PANEL_SIZE - 1) * (1 - y2);
    dc.DrawLine(xx1, yy1, xx2, yy2);
}

void deCurvesPanel::drawPoint(wxDC& dc, deValue x, deValue y)
{
    int xx = (CURVES_PANEL_SIZE - 1) * x;
    int yy = (CURVES_PANEL_SIZE - 1) * (1 - y);
    dc.DrawCircle(xx, yy, 5);
}

void deCurvesPanel::drawLines(wxDC& dc)
{
    int g1 = 100;
    int g2 = 150;

    wxPen pen1(wxColour(g1, g1, g1));
    wxPen pen2(wxColour(g2, g2, g2));

    dc.SetPen(pen1);

    float y;
    for (y = 0.0; y <= 1.0; y += 0.25)
    {
        drawLine(dc, 0.0, y, 1.0, y);
    }        

    float x;
    for (x = 0.0; x <= 1.0; x += 0.25)
    {
        drawLine(dc, x, 0.0, x, 1.0);
    }        

    dc.SetPen(pen2);

    drawLine(dc, 0.0, marker, 1.0, marker);
    drawLine(dc, marker, 0.0, marker, 1.0);

}

void deCurvesPanel::drawCurve(wxDC& dc)
{
    if (!curve)
    {
        return;
    }
    deCurvePoints points;
    curve->getShapePoints(points);
    deCurvePoints::const_iterator i;

    deValue xp = -1;
    deValue yp = -1;

    for (i = points.begin(); i != points.end(); i++)
    {
        const deCurvePoint& point = *i;
        deValue x = point.getX();
        deValue y = point.getY();
        drawPoint(dc, x, y);
        if (xp >= 0)
        {
            drawLine(dc, xp, yp, x, y);
        }
        xp = x;
        yp = y;
    }
}

void deCurvesPanel::render(wxDC& dc_orig)
{
    wxBufferedDC dc(&dc_orig, bitmap, wxBUFFER_CLIENT_AREA);

    dc.SetBackground(*wxBLACK_BRUSH);
    dc.Clear();

    drawLines(dc);

    wxColour colour = getChannelwxColour(layer.getColorSpace(), channel);
    wxPen* pen = new wxPen(colour);
    dc.SetPen(*pen);

    drawCurve(dc);
}


void deCurvesPanel::click(wxMouseEvent &event)
{
    if (!curve)
    {
        return;
    }

    selectedPoint = -1;

    deValue x;
    deValue y;
    getPosition(event, x, y);
    int n = curve->findPoint(x, y);

    if (n >= 0)
    {
        selectedPoint = n;
    }
    else
    {
        selectedPoint = curve->addPoint(x, y);
    }

    const deCurvePoint& point = curve->getPoint(selectedPoint);
    grabX = point.getX() - x;
    grabY = point.getY() - y;

    update();
}

void deCurvesPanel::update()
{
    stack.updatePreviews(layerNumber);
    stack.refreshView();
    paint();
}

void deCurvesPanel::release(wxMouseEvent &event)
{
    if (selectedPoint)
    {
        deValue x;
        deValue y;
        getPosition(event, x, y);
        if ((x < -0.1) || (y < -0.1) || (x>1.1) || (y>1.1))
        {
            curve->deletePoint(selectedPoint);
        }
    }

    selectedPoint = -1;

    paint();

}

void deCurvesPanel::move(wxMouseEvent &event)
{
    if (!curve)
    {
        return;
    }

    if (selectedPoint >= 0)
    {
        deValue x;
        deValue y;
        getPosition(event, x, y);

        x+= grabX;
        y+= grabY;

        if (x < 0)
        {
            x = 0;
        }
        if (y < 0)
        {
            y = 0;
        }
        if (x > 1)
        {
            x = 1;
        }
        if (y > 1)
        {
            y = 1;
        }

        curve->movePoint(selectedPoint, x, y);
    }
    update();
}

void deCurvesPanel::traceSampler(deSampler* sampler)
{
    deValue values[4];
    bool result = sampler->getPixel(values[0], values[1], values[2], values[3], layer.getColorSpace());
    if (!result)
    {
        marker = -1;
        return;
    }
    deValue value = values[channel];
    marker = value;
    paint();
}
