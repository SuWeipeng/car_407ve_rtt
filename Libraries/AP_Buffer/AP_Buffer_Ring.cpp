#include "AP_Buffer_Ring.h"

AP_Buffer_Ring::AP_Buffer_Ring(AP_Buffer &instance, const void* buffer)
: AP_Buffer_Backend(instance)
, _head(buffer)
, _tail(buffer)
{
}

void
AP_Buffer_Ring::write(const void *pBuffer, uint16_t size)
{
}

void
AP_Buffer_Ring::read(const void *pBuffer, void* to, uint16_t size)
{
}
