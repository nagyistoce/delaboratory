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


#include "wx/wx.h"
#include "project.h"
#include "str.h"
#include "str_wx.h"
#include "layer_processor.h"
#include "logger.h"
#include "channel_manager.h"
#include "layer_stack.h"
#include "layer_frame_manager.h"
#include "static_image.h"
#include "raw_module.h"
#include "zoom_manager.h"
#include "operation_processor.h"
#include "main_window.h"
#include "gui.h"
#include "wx/stdpaths.h"

const std::string LOG_FILE_NAME = "debug.log";
const std::string LOG_LOCKS_FILE_NAME = "locks.log";

class deInitLogger
{
    private:
        wxString message;

    public:
        deInitLogger()
        {
//            std::string ucd = getUserConfigDir();
            std::string ucd = getUserDataDir();
            wxString ucd_wx = str2wx(ucd);

            if (wxDirExists(ucd_wx))
            {
                message = _T("");
            }
            else
            {
                if (wxMkdir(ucd_wx))
                {
                    message = _T("created user config dir ") + ucd_wx;
                }
                else
                {
                    message = _T("unable to create user config dir ") + ucd_wx;
                }
            }

            deLogger::getLogger().setFile(ucd + "/" + LOG_FILE_NAME);
        }

        wxString getMessage()
        {
            return message;
        }
};        


class deLaboratory: public wxApp
{	
    public:
        deLaboratory()
        :wxApp(),
         sourceImage(),
         processor(previewChannelManager, layerStack, layerFrameManager, mainWindow),
         project(processor, previewChannelManager, layerStack, layerFrameManager, sourceImage, rawModule, zoomManager, mainWindow, gui),
         operationProcessor(processor, project)
        {
            logInfo("deLaboratory constructor");

        }

        ~deLaboratory()
        {
            logInfo("deLaboratory destructor");
        }

    private:
    	virtual bool OnInit();
    	virtual int OnExit();
        deInitLogger initLogger;
        deMainWindow mainWindow;
        deSamplerManager samplerManager;
        deLayerStack layerStack;
        deLayerFrameManager layerFrameManager;
        deChannelManager previewChannelManager;
        deStaticImage sourceImage;
        deLayerProcessor processor;
        deRawModule rawModule;
        deZoomManager zoomManager;
        deGUI gui;
        deProject project;
        deOperationProcessor operationProcessor;

        virtual int FilterEvent(wxEvent& event);

};


IMPLEMENT_APP(deLaboratory)

int deLaboratory::FilterEvent(wxEvent& event)
{
    if  (event.GetEventType()==wxEVT_KEY_DOWN )
    {
        int key = ((wxKeyEvent&)event).GetKeyCode();

        project.onKey(key);
        mainWindow.onKey(key);
        return true;
    }

    return -1;
}


int deLaboratory::OnExit()
{
    logInfo("OnExit");
    return 0;
}   

bool deLaboratory::OnInit()
{
    logInfo("deLaboratory::OnInit");

    rawModule.onInit();

    std::string dcraw_version = rawModule.getVersion();

    if (dcraw_version == "")
    {
        dcraw_version = "dcraw not found";
    }
    else
    {
        dcraw_version = "dcraw version " + dcraw_version;
    }

    wxInitAllImageHandlers();

	int width = 1200;
	int height = 960;

	mainWindow.init( width, height, project, processor, samplerManager, zoomManager, dcraw_version, operationProcessor, previewChannelManager, gui);

    logInfo("show main frame");

    mainWindow.show();

    logInfo("set top level");

    mainWindow.setTopWindow();

    logInfo("startWorkerThread...");

    wxString ws = initLogger.getMessage();
    if (ws.size() > 0)
    {
        wxMessageBox(ws);
    }        

    processor.startWorkerThread();

    logInfo("process argc/argv...");

    if (argc > 1)
    {
        wxString a = argv[1];
        project.init(str(a));
        if (argc > 2)
        {
            wxString a2 = argv[2];
            operationProcessor.initProfile(str(a2));
        }            
    }

    logInfo("OnInit done");

	return TRUE;
} 


	
