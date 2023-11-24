//
// begin license header
//
// This file is part of Pixy CMUcam5 or "Pixy" for short
//
// All Pixy source code is provided under the terms of the
// GNU General Public License v2 (http://www.gnu.org/licenses/gpl-2.0.html).
// Those wishing to use Pixy source code, software and/or
// technologies under different licensing terms should contact us at
// cmucam@cs.cmu.edu. Such licensing terms are available for
// all portions of the Pixy codebase presented here.
//
// end license header
//
// Arduino ICSP SPI link class

#ifndef _PIXY2PI_H
#define _PIXY2PI_H

#include "TPixy2.h"
#include <wiringPiSPI.h>

#define PIXY_SPI_CLOCKRATE 2000000
#define PIXY_SPI_CHANNEL 0

class Link2SPI
{
public:
  int8_t open(uint32_t arg)
  {
    return wiringPiSPISetup(PIXY_SPI_CHANNEL, PIXY_SPI_CLOCKRATE);
  }

  void close()
  {
  }

  int16_t recv(uint8_t *buf, uint8_t len, uint16_t *cs = NULL)
  {
    if (cs)
      *cs = 0;

    for (uint8_t i = 0; i < len; i++)
    {
      buf[i] = 0x00; // Ensure that we read a byte
      wiringPiSPIDataRW(PIXY_SPI_CHANNEL, &buf[i], 1);
      if (cs)
        *cs += buf[i];
    }
    return len;
  }

  int16_t send(uint8_t *buf, uint8_t len)
  {
    uint8_t i;
    for (i = 0; i < len; i++)
      wiringPiSPIDataRW(PIXY_SPI_CHANNEL, &buf[i], 1);
    return len;
  }
};

typedef TPixy2<Link2SPI> Pixy2;

#endif
