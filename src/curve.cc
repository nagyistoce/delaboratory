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

#include "curve.h"
#include "channel.h"
#include <cmath>
#include <iostream>
#include <sstream>
#include <ctime>
#include "str.h"
#include "xml.h"

#define CURVE_POINT_PICK_DISTANCE 0.03
#define VERTICAL_STEP 0.01

deCurve::deCurve()
:shape(256)
{
    reset();
}

deCurve::~deCurve()
{
}

void deCurve::reset()
{
    points.clear();
    fill(1, 1, 0);
    shape.build(points);
}

void deCurve::invert()
{
    points.clear();
    fill(1, -1, 0);
    shape.build(points);
}

void deCurve::setConst(deValue v)
{
    points.clear();
    points.push_back(deCurvePoint(0,v));
    points.push_back(deCurvePoint(1,v));
    shape.build(points);
}

void deCurve::setAngle(int a)
{
    if (a < 4)
    {
        deValue p1 = a / 8.0;
        deValue p2 = 1 - p1;
        points.clear();
        points.push_back(deCurvePoint(0,0));
        points.push_back(deCurvePoint(p1,0));
        points.push_back(deCurvePoint(p2,1));
        points.push_back(deCurvePoint(1,1));
    }
    else
    {
        deValue p1 = (a - 3) / 8.0;
        deValue p2 = 1 - p1;
        points.clear();
        points.push_back(deCurvePoint(0,p1));
        points.push_back(deCurvePoint(1,p2));
    }
    shape.build(points);
}

void deCurve::fill(int n, deValue a, deValue r)
{
    points.clear();
    double step = 1.0 / n;
    double p = 0.0;

    srand(time(0));

    while (p <= 1.0)
    {
        double y = p;
        if (a < 0)
        {
            y = 1.0 - y;
        }
        deValue rr = r * ( (double) rand() / RAND_MAX );
        rr = 2 * rr - r;
        y+= rr;
        if (y < 0)
        {
            y = 0;
        }
        if (y > 1)
        {
            y = 1;
        }

        points.push_back(deCurvePoint(p,y));
        p+=step;
    }
    shape.build(points);
}

deValue deCurve::calcValue(deValue value)
{
    return shape.calc(value);
}

void deCurve::process(const deChannel& source, deChannel& destination, int n)
{
    const deValue* pixels = source.getPixels();

    int i;
    for (i = 0; i < n; i++)
    {
        deValue value = pixels[i];
        deValue result = shape.calc(value);

        destination.setValueClip(i, result);
    }
}

int deCurve::findPoint(deValue x, deValue y) const
{
    deCurvePoints::const_iterator j;
    int i = 0;

    for (j = points.begin(); j != points.end(); j++)
    {
        const deCurvePoint& point = *j;
        deValue xx = x - point.getX();
        float yy = y - point.getY();
        if (sqrt (xx * xx + yy * yy) < CURVE_POINT_PICK_DISTANCE)
        {
            return i;
        }
        i++;
    }

    return -1;
}

int deCurve::addPoint(deValue x, deValue y)
{
    if ((x <= 0) || (x >= 1))
    {
        return -1;
    }
    if ((y < 0) || (y > 1))
    {
        return -1;
    }

    points.push_back(deCurvePoint(x,y));

    shape.build(points);

    return points.size() - 1;
}

void deCurve::deletePoint(int p)
{
    deCurvePoints::iterator i = points.begin();
    while (p > 0)
    {
        i++;
        p--;
    }

    deValue xx = (*i).getX();

    points.erase(i);

    if (xx == 0)
    {
        points.push_back(deCurvePoint(0,0));
    }
    if (xx == 1)
    {
        points.push_back(deCurvePoint(1,1));
    }

    shape.build(points);
}

void deCurve::movePoint(int p, deValue x, deValue y)
{
    if ((x < 0) || (x > 1))
    {
        return;
    }
    if ((y < 0) || (y > 1))
    {
        return;
    }

    deCurvePoints::iterator i = points.begin();
    while (p > 0)
    {
        i++;
        p--;
    }

    deValue xx = (*i).getX();

    if (xx == 0)
    {
        x = 0;
    }
    else
    {
        if (x == 0)
        {
            return;
        }
    }

    if (xx == 1)
    {
        x = 1;
    }
    else
    {
        if (x == 1)
        {
            return;
        }
    }

    (*i).move(x, y);
    shape.build(points);
}

void deCurve::movePointUp(int p)
{
    movePointStep(p, -1);
}

void deCurve::movePointDown(int p)
{
    movePointStep(p, 1);
}    

void deCurve::movePointStep(int p, int dir)
{
    deCurvePoints::iterator i = points.begin();
    while (p > 0)
    {
        i++;
        p--;
    }

    deValue xx = (*i).getX();
    deValue yy = (*i).getY();

    yy += dir * VERTICAL_STEP;

    if (yy < 0.0)
    {
        yy = 0.0;
    }
    if (yy > 1.0)
    {
        yy = 1.0;
    }

    (*i).move(xx, yy);
    shape.build(points);
}

const deCurvePoints& deCurve::getPoints() const
{
    return points;
}

const deCurvePoint& deCurve::getPoint(int n) const
{
    deCurvePoints::const_iterator i = points.begin();
    while (n > 0)
    {
        i++;
        n--;
    }
    return *i;
}

void deCurve::getControlPoints(deCurvePoints& points) const
{
    shape.getControlPoints(points);
}

void deCurve::getCurvePoints(deCurvePoints& points) const
{
    shape.getCurvePoints(points);
}

void deCurve::save(xmlNodePtr node) const
{
    deCurvePoints::const_iterator i;
    
    for (i = points.begin(); i != points.end(); i++)
    {
        xmlNodePtr child = xmlNewChild(node, NULL, BAD_CAST("point"), NULL);
        const deCurvePoint& point = *i;

        saveChild(child, "x", str(point.getX()));
        saveChild(child, "y", str(point.getY()));

    }        
}

void deCurve::loadPoint(xmlNodePtr node) 
{
    xmlNodePtr child = node->xmlChildrenNode;

    std::string xStr = "";
    std::string yStr = "";

    while (child)
    {
        if ((!xmlStrcmp(child->name, BAD_CAST("x")))) 
        {
            xStr = getContent(child);
        }            

        if ((!xmlStrcmp(child->name, BAD_CAST("y")))) 
        {
            yStr = getContent(child);
        }            

        child = child->next;
    }

    deValue x = 0;
    deValue y = 0;

    {
        x = getValue(xStr);
    }

    {
        y = getValue(yStr);
    }

    points.push_back(deCurvePoint(x,y));
}

void deCurve::load(xmlNodePtr node) 
{
    points.clear();

    xmlNodePtr child = node->xmlChildrenNode;

    while (child)
    {
        if ((!xmlStrcmp(child->name, BAD_CAST("point")))) 
        {
            loadPoint(child);
        }            

        child = child->next;
    }

    shape.build(points);
}

bool deCurve::isNeutral() const
{
    if (points.size() != 2)
    {
        return false;
    }
    deCurvePoints::const_iterator i = points.begin();
    deCurvePoint a = *i;
    if (a.getY() != 0)
    {
        return false;
    }
    i++;
    deCurvePoint b = *i;
    if (b.getY() != 1)
    {
        return false;
    }
    return true;
}