/*---------------------------------------------------------*\
| RGBController_SINNERController.h                          |
|                                                           |
|   RGBController for SINNER model                          |
|                                                           |
|   Mitsuyo (Mitsuyo Amusement)                 05 Jul 2024 |
|                                                           |
|   This file is part of the OpenRGB project                |
|   SPDX-License-Identifier: GPL-2.0-only                   |
\*---------------------------------------------------------*/

#pragma once

#include "RGBController.h"
#include "SINNERController.h"

class RGBController_SINNERController : public RGBController
{
public:
    RGBController_SINNERController(SINNERController* controller_ptr);
    ~RGBController_SINNERController();

    void        SetupZones();
    void        ResizeZone(int zone, int new_size);

    void        DeviceUpdateLEDs();
    void        UpdateZoneLEDs(int zone);
    void        UpdateSingleLED(int led);

    void        DeviceUpdateMode();

private:
    SINNERController* controller;
};
