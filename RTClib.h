// Library for RTC 3231 Word Clock Project ET 370 Spring 2017 - Reed Danielson, Emily Shimada, Jinuoo Suh

#ifndef _RTCLIB_H_
#define _RTCLIB_H_

#include <Arduino.h>
class TimeSpan;

#define DS3231_ADDRESS  0x68
#define DS3231_CONTROL  0x0E
#define DS3231_STATUS 0x0F

#define SECONDS_PER_DAY 86400L

#define SECONDS_FROM_1970_TO_2000 946684800

// Simple Date and Time without timezone / leap year / or daylight savings time)
class DateTime {
public:
    DateTime (uint32_t t =0);
    DateTime (uint16_t year, uint8_t month, uint8_t day,
                uint8_t hour =0, uint8_t min =0, uint8_t sec =0);
    DateTime (const DateTime& copy);
    DateTime (const char* date, const char* time);
    DateTime (const __FlashStringHelper* date, const __FlashStringHelper* time);
    uint16_t year() const       { return 2000 + yOff; }
    uint8_t month() const       { return m; }
    uint8_t day() const         { return d; }
    uint8_t hour() const        { return hh; }
    uint8_t minute() const      { return mm; }
    uint8_t second() const      { return ss; }
    uint8_t dayOfTheWeek() const;

protected:
    uint8_t yOff, m, d, hh, mm, ss;
};

// Timespan which can represent changes in time with seconds accuracy.
class TimeSpan {
public:
    TimeSpan (int32_t seconds = 0);
    TimeSpan (int16_t days, int8_t hours, int8_t minutes, int8_t seconds);
    TimeSpan (const TimeSpan& copy);
    int16_t days() const         { return _seconds / 86400L; }
    int8_t  hours() const        { return _seconds / 3600 % 24; }
    int8_t  minutes() const      { return _seconds / 60 % 60; }
    int8_t  seconds() const      { return _seconds % 60; }
    int32_t totalseconds() const { return _seconds; }

    TimeSpan operator+(const TimeSpan& right);
    TimeSpan operator-(const TimeSpan& right);

protected:
    int32_t _seconds;
};

// RTC based on the DS3231 chip connected via SDA and SLC ports and the Wire library

enum Ds3231SqwPinMode { DS3231_OFF = 0x01, DS3231_SquareWave1Hz = 0x00, DS3231_SquareWave1kHz = 0x08, DS3231_SquareWave4kHz = 0x10, DS3231_SquareWave8kHz = 0x18 };

class RTC_DS3231 {
public:
    boolean begin(void);
    static void adjust(const DateTime& dt);
    bool lostPower(void);
    static DateTime now();
    static Ds3231SqwPinMode readSqwPinMode();
    static void writeSqwPinMode(Ds3231SqwPinMode mode);
};
