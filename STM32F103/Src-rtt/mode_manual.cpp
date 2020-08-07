#include <rtt_interface.h>
#include <AC_Base.h>
#include "mode.h"

extern vel_target  vel;
extern AC_Base     *base;

void
ModeManual::run()
{
    float vel_x = vel.vel_x;
    float rad_z = vel.rad_z;
    
    base->pct2rpm(vel_x, rad_z);
}