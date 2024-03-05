#include <math.h>
#include <stdint.h>

float quick_rsqrt(float number)
{
  union {
    float    f;
    uint32_t i;
  } conv = { .f = number };
  conv.i  = 0x5f3759df - (conv.i >> 1);
  conv.f *= 1.5F - (number * 0.5F * conv.f * conv.f);
  return conv.f;
}

float simple_rsqrt(float number)
{
  return 1.0f / sqrtf(number);
}
