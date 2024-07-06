/*---------------------------------------------------------*\
| SINNERController.h                                        |
|                                                           |
|   Driver for SINNER model                                 |
|                                                           |
|   Mitsuyo (Mitsuyo Amusement)                 05 Jul 2024 |
|                                                           |
|   This file is part of the OpenRGB project                |
|   SPDX-License-Identifier: GPL-2.0-only                   |
\*---------------------------------------------------------*/

#pragma once

#include <array>
#include <string>
#include <vector>
#include <hidapi/hidapi.h>
#include "RGBController.h"

#define SINNER_PACKET_SIZE       39

enum
{
    MODE_DIRECT                    = 0x01,
    MODE_BUILTIN                   = 0x00,
};

class SINNERController
{
public:
    SINNERController(hid_device* dev_handle, char *_path);
    ~SINNERController();

    std::string   GetDeviceName();
    std::string   GetSerial();
    std::string   GetLocation();

    unsigned char GetLedRed();
    unsigned char GetLedGreen();
    unsigned char GetLedBlue();
    void          SendUpdate(RGBColor * colors);
    void          SetMode(unsigned char mode);

private:
    std::string             device_name;
    std::string             serial;
    std::string             location;
    hid_device*             dev;

    unsigned char           current_red;
    unsigned char           current_green;
    unsigned char           current_blue;

    void SendUpdate();
};
