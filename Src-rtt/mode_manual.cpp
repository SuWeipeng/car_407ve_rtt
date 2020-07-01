#include <rtt_interface.h>
#include <AC_Base.h>
#include "mode.h"

extern vel_target  vel;
extern Mecanum_4wd *base;

void
ModeManual::run()
{
    float vel_x = vel.vel_x;
    float vel_y = vel.vel_y;
    float rad_z = vel.rad_z;
    
    base->pct2rpm(vel_x, vel_y, rad_z);
}