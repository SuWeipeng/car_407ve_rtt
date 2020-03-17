/*
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
#pragma once

#include <stdint.h>
#include <vectorN.h>
#include <sparse-endian.h>

typedef VectorN<float,3> Vector3f;

#define RANGEFINDER_GROUND_CLEARANCE_CM_DEFAULT 10
#define RANGEFINDER_PREARM_ALT_MAX_CM           200

#define ARRAY_SIZE(_arr) (sizeof(_arr) / sizeof(_arr[0]))

class AP_RangeFinder_Backend;

class RangeFinder
{
    friend class AP_RangeFinder_Backend;
public:
    RangeFinder();

    /* Do not allow copies */
    RangeFinder(const RangeFinder &other) = delete;
    RangeFinder &operator=(const RangeFinder&) = delete;

    // RangeFinder driver types
    enum class Type {
        NONE   = 0,
        ANALOG = 1,
        MBI2C  = 2,
        PLI2C  = 3,
//        PX4    = 4, // no longer used, but may be in some user's parameters
        PX4_PWM= 5,
        BBB_PRU= 6,
        LWI2C  = 7,
        LWSER  = 8,
        BEBOP  = 9,
        MAVLink = 10,
        ULANDING= 11,
        LEDDARONE = 12,
        MBSER  = 13,
        TRI2C  = 14,
        PLI2CV3= 15,
        VL53L0X = 16,
        NMEA = 17,
        WASP = 18,
        BenewakeTF02 = 19,
        BenewakeTFmini = 20,
        PLI2CV3HP = 21,
        PWM = 22,
        BLPing = 23,
        UAVCAN = 24,
        BenewakeTFminiPlus = 25,
        Lanbao = 26,
        BenewakeTF03 = 27,
        VL53L1X_Short = 28,
        LeddarVu8_Serial = 29,
    };

    enum class Function {
        LINEAR    = 0,
        INVERTED  = 1,
        HYPERBOLA = 2
    };

    enum class Status {
        NotConnected = 0,
        NoData,
        OutOfRangeLow,
        OutOfRangeHigh,
        Good
    };

    // The RangeFinder_State structure is filled in by the backend driver
    struct RangeFinder_State {
        uint16_t distance_cm;           // distance: in cm
        uint16_t voltage_mv;            // voltage in millivolts, if applicable, otherwise 0
        enum RangeFinder::Status status; // sensor status
        uint8_t  range_valid_count;     // number of consecutive valid readings (maxes out at 10)
        uint32_t last_reading_ms;       // system time of last successful update from sensor
    };

    // detect and initialise any available rangefinders
    void init(Type type);

    // update state of all rangefinders. Should be called at around
    // 10Hz from main loop
    void update(void);
    
    uint16_t distance_cm(void) const;

    static RangeFinder *get_singleton(void) { return _singleton; }

private:
    static RangeFinder *_singleton;

    RangeFinder_State state;
    AP_RangeFinder_Backend *drivers;

    bool _add_backend(AP_RangeFinder_Backend *driver);
};
