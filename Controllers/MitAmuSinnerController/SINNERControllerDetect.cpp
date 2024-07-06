/*---------------------------------------------------------*\
| SINNERControllerDetect.cpp                                |
|                                                           |
|   Detector for SINNER model                               |
|                                                           |
|   Mitsuyo (Mitsuyo Amusement)                 05 Jul 2024 |
|                                                           |
|   This file is part of the OpenRGB project                |
|   SPDX-License-Identifier: GPL-2.0-only                   |
\*---------------------------------------------------------*/

#include <hidapi/hidapi.h>
#include "Detector.h"
#include "SINNERController.h"
#include "RGBController.h"
#include "RGBController_SINNERController.h"

#define SINNER_VID                        0xCAFF

#define SINNER_PID                        0x4005

/******************************************************************************************\
*                                                                                          *
*   DetectSINNERControllers                                                                *
*                                                                                          *
*       Tests the USB address to see if any IIDX controllers exists there.                 *
*                                                                                          *
\******************************************************************************************/

void DetectSINNER(hid_device_info* info, const std::string&)
{
    hid_device* dev = hid_open_path(info->path);
    if(dev)
    {
        SINNERController* controller = new SINNERController(dev, info->path);
        RGBController_SINNERController* rgb_controller = new RGBController_SINNERController(controller);
        // Constructor sets the name
        ResourceManager::get()->RegisterRGBController(rgb_controller);
    }
}

REGISTER_HID_DETECTOR_IPU("Mitsuyo Amusement IIDX Controller SINNER model",          DetectSINNER,          SINNER_VID,   SINNER_PID,     0,    0x0001,     0x0004);
