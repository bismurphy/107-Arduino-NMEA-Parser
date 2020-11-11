/**
 * This software is distributed under the terms of the MIT License.
 * Copyright (c) 2020 LXRobotics.
 * Author: Alexander Entinger <alexander.entinger@lxrobotics.com>
 * Contributors: https://github.com/107-systems/107-Arduino-NMEA-Parser/graphs/contributors.
 */

#ifndef ARDUINO_MTK3333_NMEA_TYPES_H_
#define ARDUINO_MTK3333_NMEA_TYPES_H_

/**************************************************************************************
 * INCLUDE
 **************************************************************************************/

#include <time.h>
#include <math.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace nmea
{

/**************************************************************************************
 * TYPEDEF
 **************************************************************************************/

typedef struct
{
  int hour;
  int minute;
  int second;
  int microsecond;
} Time;

typedef struct
{
  int day;
  int month;
  int year;
} Date;

enum class RmcSource
{
  Unknown, GPS, Galileo, GLONASS, GNSS
};

typedef struct
{
  bool is_valid;
  RmcSource source;
  float latitude;
  float longitude;
  float speed;
  float course;
  float magnetic_variation;
  Time time_utc;
  Date date;
} RmcData;

enum class FixQuality
{
  Invalid, GPS_Fix, DGPS_Fix
};

typedef struct
{
  Time time_utc;
  float latitude;
  float longitude;
  int num_satellites;
  /* HDOP = Horizontal dilution of position */
  float hdop;
  /* Antenna altitude above/below mean sea level (Geoid). */
  float altitude;
  /* Geoidal separation N
   *  where
   *    h = N + H
   *  and
   *    h = height above ellipsoid
   *    H = elevation, orthometric height
   *    N = geoidal separation (some books call this the geoidal height)
   */
  float geoidal_separation;
  /* Age in seconds since last update from differential reference station. */
  int dgps_age;
  /* DGPS station id - 4 bytes + 1 byte 0 termination. */
  char dgps_id[5];
} GgaData;

/**************************************************************************************
 * CONST
 **************************************************************************************/

Time    const INVALID_TIME = {-1, -1, -1, -1};
Date    const INVALID_DATE = {-1, -1, -1};
RmcData const INVALID_RMC  = {false, RmcSource::Unknown, NAN, NAN, NAN, NAN, NAN, INVALID_TIME, INVALID_DATE};
GgaData const INVALID_GGA  = {INVALID_TIME, NAN, NAN, -1, NAN, NAN, NAN, -1, {0}};

/**************************************************************************************
 * FUNCTION DECLARATION
 **************************************************************************************/

bool   isValid         (Date const & date);
bool   isValid         (Time const & time);
bool   isValid         (Date const & date, Time const & time);
time_t toPosixTimestamp(Date const & date, Time const & time);

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* nmea */

#endif /* ARDUINO_MTK3333_NMEA_TYPES_H_ */
