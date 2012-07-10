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

#include "operation_processor.h"
#include "layer_processor.h"
#include "logger.h"
#include "project.h"
#include "layer_stack.h"
#include "base_layer_with_properties.h"
#include "color_space_utils.h"

deOperationProcessor::deOperationProcessor(deLayerProcessor& _layerProcessor, deProject& _project)
:layerProcessor(_layerProcessor), project(_project)
{
}

deOperationProcessor::~deOperationProcessor()
{
}

void deOperationProcessor::addNewLayerOnTop(deBaseLayer* layer)
{
    logInfo("before add new layer on top");
    layerProcessor.addLayerInLayerProcessor(layer);
    logInfo("after add new layer on top");
}

void deOperationProcessor::removeTopLayer()
{
    logInfo("before remove top layer");
    layerProcessor.removeTopLayerInLayerProcessor();
    logInfo("after remove top layer");
}

void deOperationProcessor::execute(const std::string& operation)
{
    if (operation == "remove")
    {
        removeTopLayer();
        project.onRemoveTopLayer();
        return;
    }

    bool ok = false;
    if (tryExecuteBasicOperation(operation))
    {
        ok = true;
    }
    else
    {
        deBaseLayer* layer = project.createNewLayer(operation);

        if (layer)
        {
            addNewLayerOnTop(layer);
            ok = true;
        }
    }        

    if (ok)
    {
        project.onAddNewLayer();
    }        
}

void deOperationProcessor::initProfile(const std::string& profile)
{
    if (profile == "cmyk_auto_levels")
    {
        execute("CMYK");
        execute("levels");
    }
    if (profile == "bw")
    {
        execute("BW");
    }
    if (profile == "c2g")
    {
        execute("c2g");
    }
    if (profile == "vignette")
    {
        execute("LAB");
        execute("vignette");
    }
}


bool deOperationProcessor::executeOperation(deColorSpace colorSpace, const std::string& operation)
{
    deViewManager& viewManager = project.getViewManager();

    viewManager.setLastView();

    deColorSpace currentColorSpace = viewManager.getColorSpace();

    if (colorSpace != currentColorSpace)
    {
        deBaseLayer* layer1 = project.createNewLayer(getColorSpaceName(colorSpace));

        if (layer1)
        {
            addNewLayerOnTop(layer1);
            viewManager.setLastView();
        }
        else
        {
            return false;
        }
    }        

    deBaseLayer* layer2 = project.createNewLayer(operation);

    if (layer2)
    {
        addNewLayerOnTop(layer2);
        viewManager.setLastView();
    }
    else
    {
        return false;
    }

    project.openLayerFrame(project.getLayerStack().getSize() - 1);

    return true;
}

bool deOperationProcessor::tryExecuteBasicOperation(const std::string& operation)
{
    if (operation == "CMYK curves")
    {
        return executeOperation(deColorSpaceCMYK, "curves");
    }
    
    if (operation == "CMYK levels")
    {
        return executeOperation(deColorSpaceCMYK, "levels");
    }

    if (operation == "LAB vignette")
    {
        return executeOperation(deColorSpaceLAB, "vignette");
    }

    if (operation == "LAB local contrast")
    {
        return executeOperation(deColorSpaceLAB, "local_contrast");
    }

    if (operation == "BW local contrast")
    {
        return executeOperation(deColorSpaceBW, "local_contrast");
    }

    if (operation == "RGB curves")
    {
        return executeOperation(deColorSpaceRGB, "curves");
    }

    if (operation == "RGB levels")
    {
        return executeOperation(deColorSpaceRGB, "levels");
    }

    if (operation == "LAB curves")
    {
        return executeOperation(deColorSpaceLAB, "curves");
    }

    if (operation == "BW curve")
    {
        return executeOperation(deColorSpaceBW, "curves");
    }

    if (operation == "BW vignette")
    {
        return executeOperation(deColorSpaceBW, "vignette");
    }

    if (operation == "RGB tone")
    {
        return executeOperation(deColorSpaceRGB, "tone");
    }

    if (operation == "RGB shadows")
    {
        return executeOperation(deColorSpaceRGB, "recover_shadows");
    }

    if (operation == "RGB highlights")
    {
        return executeOperation(deColorSpaceRGB, "recover_highlights");
    }

    if (operation == "BW gradient")
    {
        return executeOperation(deColorSpaceBW, "gradient");
    }
    if (operation == "RGB gradient")
    {
        return executeOperation(deColorSpaceRGB, "gradient");
    }
    if (operation == "CMYK gradient")
    {
        return executeOperation(deColorSpaceCMYK, "gradient");
    }
    if (operation == "LAB gradient")
    {
        return executeOperation(deColorSpaceLAB, "gradient");
    }

    if (operation == "LAB wb")
    {
        return executeOperation(deColorSpaceLAB, "white_balance");
    }

    if (operation == "LAB saturation")
    {
        return executeOperation(deColorSpaceLAB, "saturation");
    }

    if (operation == "HSV equalizer")
    {
        return executeOperation(deColorSpaceHSV, "equalizer");
    }

    if (operation == "LCH equalizer")
    {
        return executeOperation(deColorSpaceLCH, "equalizer");
    }

    return false;
}

void getSupportedColorsOperations(std::vector<std::string>& actions)
{
    actions.push_back("CMYK curves");
    actions.push_back("CMYK levels");
    actions.push_back("RGB curves");
    actions.push_back("RGB levels");
    actions.push_back("LAB wb");
    actions.push_back("LAB saturation");
    actions.push_back("LAB curves");
    actions.push_back("BW curve");
    actions.push_back("HSV equalizer");
    actions.push_back("LCH equalizer");
}

void getSupportedOtherOperations(std::vector<std::string>& actions)
{
    actions.push_back("RGB shadows");
    actions.push_back("RGB highlights");
    actions.push_back("LAB vignette");
    actions.push_back("LAB local contrast");
    actions.push_back("BW vignette");
    actions.push_back("BW local contrast");
    actions.push_back("LAB gradient");
    actions.push_back("BW gradient");
    actions.push_back("RGB gradient");
    actions.push_back("CMYK gradient");
}
