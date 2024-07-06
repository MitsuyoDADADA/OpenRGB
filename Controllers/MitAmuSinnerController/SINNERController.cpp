/*---------------------------------------------------------*\
| SINNERController.cpp                                      |
|                                                           |
|   Driver for SINNER model                                 |
|                                                           |
|   Mitsuyo (Mitsuyo Amusement)                 05 Jul 2024 |
|                                                           |
|   This file is part of the OpenRGB project                |
|   SPDX-License-Identifier: GPL-2.0-only                   |
\*---------------------------------------------------------*/

#include <cstring>
#include <chrono>
#include <thread>
#include "SINNERController.h"

using namespace std::chrono_literals;

SINNERController::SINNERController(hid_device* dev_handle, char *_path)
{
    dev             = dev_handle;
    location        = _path;

    const int szTemp = 256;
    wchar_t tmpName[szTemp];

    hid_get_manufacturer_string(dev, tmpName, szTemp);
    std::wstring wName = std::wstring(tmpName);
    device_name        = std::string(wName.begin(), wName.end());

    hid_get_product_string(dev, tmpName, szTemp);
    wName  = std::wstring(tmpName);
    device_name.append(" ").append(std::string(wName.begin(), wName.end()));

    hid_get_serial_number_string(dev, tmpName, szTemp);
    wName  = std::wstring(tmpName);
    serial = std::string(wName.begin(), wName.end());

}

SINNERController::~SINNERController()
{
    if(dev)
    {
        hid_close(dev);
    }
}

std::string SINNERController::GetDeviceName()
{
    return device_name;
}

std::string SINNERController::GetSerial()
{
    return serial;
}

std::string SINNERController::GetLocation()
{
    return("HID: " + location);
}

void SINNERController::SendUpdate(RGBColor* colors)
{
        unsigned char buffer[SINNER_PACKET_SIZE] = { 0x00 };
        memset(buffer, 0x00, SINNER_PACKET_SIZE);
/*--------------------------------------*\
| Protocol:                              |
|Rid    Magic   Cmd     Data * 12        |
|0x02   0xF1    0xXX    (0xXX 0xXX 0xXX) |
|Cmd: 0x01 - Direct      R    G    B     |
|     0x00 - Build in effects            |
\*_-------------------------------------*/

        buffer[0] = 0x02;
        buffer[1] = 0xF1;
        buffer[2] = 0x01;
        for(unsigned int color_idx = 0; color_idx < 12; color_idx++)
        {
            buffer[3 + (color_idx * 3)] = RGBGetRValue(colors[color_idx]);
            buffer[4 + (color_idx * 3)] = RGBGetGValue(colors[color_idx]);
            buffer[5 + (color_idx * 3)] = RGBGetBValue(colors[color_idx]);
        }

        hid_write(dev, buffer, SINNER_PACKET_SIZE);
}


void SINNERController::SetMode(unsigned char mode)
{
    unsigned char buffer[SINNER_PACKET_SIZE] = { 0x00 };
    memset(buffer, 0x00, SINNER_PACKET_SIZE);
    buffer[0] = 0x02;
    buffer[1] = 0xF1;
    buffer[2] = mode;
    hid_write(dev, buffer, SINNER_PACKET_SIZE);
}
