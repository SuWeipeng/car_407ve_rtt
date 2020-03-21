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

#include "AP_RangeFinder.h"
#include "AP_RangeFinder_VL53L0X.h"
#include "AP_RangeFinder_VL53L1X.h"

RangeFinder::RangeFinder()
: drivers(nullptr)
{
    _singleton = this;
}

/*
  initialise the RangeFinder class. We do detection of attached range
  finders here. For now we won't allow for hot-plugging of
  rangefinders.
 */
void RangeFinder::init(Type type)
{
    switch (type) {
    case Type::VL53L0X:
    case Type::VL53L1X_Short:
      if(_add_backend(AP_RangeFinder_VL53L0X::detect(state)))
      {
        break;
      }
      if(_add_backend(AP_RangeFinder_VL53L1X::detect(state,
                                                     type == Type::VL53L1X_Short ?  AP_RangeFinder_VL53L1X::DistanceMode::Short :
                                                     AP_RangeFinder_VL53L1X::DistanceMode::Long)))
      {
        break;
      }
    default:
        break;
    }
}

/*
  update RangeFinder state for all instances. This should be called at
  around 10Hz by main loop
 */
void RangeFinder::update(void)
{
  if (drivers != nullptr) {
    drivers->update();
  }
}

bool RangeFinder::_add_backend(AP_RangeFinder_Backend *backend)
{
    if (!backend) {
        return false;
    }

    drivers = backend;
    return true;
}

uint16_t RangeFinder::distance_cm(void) const
{
  if (drivers != nullptr) 
  {
    return drivers->distance_cm();
  } else {
    return 0;
  }
}

RangeFinder *RangeFinder::_singleton;
