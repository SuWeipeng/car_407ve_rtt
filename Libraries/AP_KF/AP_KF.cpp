
#include "AP_KF.h"

typedef VectorN<float,4> _Vector4f;

AP_KF::AP_KF()
: _dt(0)
, _var_acc_init(0)
, _var_gyro_init(0)
{
  float d[4] = {1.0f, 1.0f, 1.0f, 1.0f};
  _Matrix4f eye4(d),temp;
  
  float v1[4] = {1,   0,   0,   0};
  float v2[4] = {0, _dt,   0,   0};
  _Vector4f vector_1(v1), vector_2(v2);
  temp.mult(vector_1, vector_2);
  A +=  temp;
  
  float v3[4] = {0,   0,   1,   0};
  float v4[4] = {0,   0,   0, _dt};
  _Vector4f vector_3(v3), vector_4(v4);
  temp.mult(vector_3, vector_4);
  A +=  temp;  
}

AP_KF::~AP_KF()
{}

void 
AP_KF::var_init(const float var_acc, const float var_gyro)
{
  _var_acc_init  = var_acc;
  _var_gyro_init = var_gyro;
}