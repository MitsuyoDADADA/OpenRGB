/*---------------------------------------------------------*\
| RGBController_SINNERController.cpp                        |
|                                                           |
|   RGBController for SINNER model                          |
|                                                           |
|   Mitsuyo (Mitsuyo Amusement)                 05 Jul 2024 |
|                                                           |
|   This file is part of the OpenRGB project                |
|   SPDX-License-Identifier: GPL-2.0-only                   |
\*---------------------------------------------------------*/

#include "RGBController_SINNERController.h"

#define NA              0xFFFFFFFF

/**------------------------------------------------------------------*\
    @name Mitsuyo Amusement IIDX Controller SINNER model
    @category Gamepad
    @type USB
    @save :x:
    @direct :white_check_mark:
    @effects :white_check_mark:
    @detectors DetectSINNER
    @comment
\*-------------------------------------------------------------------*/

static unsigned int scratch_matrix_map[5][5] =
    { {NA, 10, 11, 0, NA},
      {9, NA, NA, NA, 1},
      {8,  NA, NA, NA, 2},
      {7,  NA, NA, NA, 3},
      {NA, 6,  5,  4, NA},
      };

RGBController_SINNERController::RGBController_SINNERController(SINNERController* controller_ptr)
{
    controller          = controller_ptr;

    name                = "IIDX Controller SINNER model";
    vendor              = "Mitsuyo Amusement";
    type                = DEVICE_TYPE_GAMEPAD;
    description         = controller->GetDeviceName();
    serial              = controller->GetSerial();
    location            = controller->GetLocation();

    mode Direct;
    Direct.name       = "Direct";
    Direct.value      = MODE_DIRECT;
    Direct.flags      = MODE_FLAG_HAS_PER_LED_COLOR;
    Direct.color_mode = MODE_COLORS_PER_LED;
    modes.push_back(Direct);

    mode BuiltIn;
    BuiltIn.name       = "Built In";
    BuiltIn.value      = MODE_BUILTIN;
    BuiltIn.flags      = 7;
    BuiltIn.color_mode = 0;
    modes.push_back(BuiltIn);

    SetupZones();
}

RGBController_SINNERController::~RGBController_SINNERController()
{
    delete controller;
}

void RGBController_SINNERController::SetupZones()
{
    zone SINNER_zone;
    SINNER_zone.name          = "Turntable";
    SINNER_zone.type          = ZONE_TYPE_MATRIX;
    SINNER_zone.leds_min      = 12;
    SINNER_zone.leds_max      = 12;
    SINNER_zone.leds_count    = 12;
    SINNER_zone.matrix_map             = new matrix_map_type;
    SINNER_zone.matrix_map->height     = 5;
    SINNER_zone.matrix_map->width      = 5;
    SINNER_zone.matrix_map->map        = (unsigned int *)&scratch_matrix_map;
    zones.push_back(SINNER_zone);

    for(unsigned int led_idx = 0; led_idx < 12; led_idx++)
    {
        led new_led;
        new_led.name = std::to_string(led_idx + 1);
        leds.push_back(new_led);
    }


    SetupColors();

}

void RGBController_SINNERController::ResizeZone(int /*zone*/, int /*new_size*/)
{
    /*---------------------------------------------------------*\
    | This device does not support resizing zones               |
    \*---------------------------------------------------------*/
}

void RGBController_SINNERController::DeviceUpdateLEDs()
{
    for (std::size_t led = 0; led < colors.size(); led++)
    {
        UpdateSingleLED(led);
    }
}

void RGBController_SINNERController::UpdateZoneLEDs(int /*zone*/)
{
    DeviceUpdateLEDs();
}

void RGBController_SINNERController::UpdateSingleLED(int led)
{
    if(modes[active_mode].value == MODE_DIRECT){
        controller->SendUpdate(zones[0].colors);
    }
}

void RGBController_SINNERController::DeviceUpdateMode()
{
    controller->SetMode(modes[active_mode].value);
}
