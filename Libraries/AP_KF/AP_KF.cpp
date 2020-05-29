
#include "AP_KF.h"

AP_KF::AP_KF()
: _dt(0)
{
  _Matrix4f temp;
  
  memset(_var_acc_init  , 0, sizeof(_var_acc_init));
  memset(_var_gyro_init , 0, sizeof(_var_gyro_init));
  
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
AP_KF::set_var(const float &var_acc, const float &var_gyro)
{
  memcpy(_var_acc_init, &var_acc, sizeof(_var_acc_init));
  memcpy(_var_gyro_init, &var_gyro, sizeof(_var_acc_init));
    
  float var_init[4] = {_var_acc_init[0], _var_gyro_init[0], _var_acc_init[1], _var_gyro_init[1]};
  Q.eye_mult(var_init);
  R.eye_mult(var_init);
}

void 
AP_KF::run(const Vector2f &att, const Vector2f &gyro)
{
  float     measure[4] = {att.x, gyro.x, att.y, gyro.y};
  _Vector4f measurement(measure);
  
  Vector2f att_filt = _att_flt_1.apply(att, _dt);
  Vector2f att_diff = (att - att_filt);
  att_diff.x *= att_diff.x;
  att_diff.y *= att_diff.y;
  Vector2f att_var = _att_flt_2.apply(att_diff, _dt);
 
  Vector2f gyro_filt = _gyro_flt_1.apply(gyro, _dt);
  Vector2f gyro_diff = (gyro - gyro_filt);
  gyro_diff.x *= gyro_diff.x;
  gyro_diff.y *= gyro_diff.y;
  Vector2f gyro_var = _gyro_flt_2.apply(gyro_diff, _dt);
  
  float var[4] = {att_var.x, gyro_var.x, att_var.y, gyro_var.y};
  R.eye();
  R.eye_mult(var);
  
  _state_estimate = A * _state_estimate;
}