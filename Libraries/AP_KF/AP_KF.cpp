#include "AP_KF.h"

static float d[4] = {1.0f, 1.0f, 1.0f, 1.0f};
static _Matrix4f A(d);
static _Matrix4f C(d);
static _Matrix4f P(d);
static _Matrix4f Q(d);
static _Matrix4f R(d);
static _Matrix4f K(d);
  
AP_KF::AP_KF()
: _dt(0)
{  
  memset(_var_att_init  , 0, sizeof(_var_att_init));
  memset(_var_gyro_init , 0, sizeof(_var_gyro_init));
  
  float a[4][4] = { 1, _dt,   0,   0,
                    0,   1,   0,   0,
                    0,   0,   1, _dt,
                    0,   0,   0,   1 };
  A.set(a);  
}

AP_KF::~AP_KF()
{}

void 
AP_KF::set_var(const float &var_acc, const float &var_gyro)
{
  memcpy(_var_att_init, &var_acc, sizeof(_var_att_init));
  memcpy(_var_gyro_init, &var_gyro, sizeof(_var_gyro_init));
    
  float var_init[4] = {_var_att_init[0], _var_gyro_init[0], _var_att_init[1], _var_gyro_init[1]};
  Q.eye_mult(var_init);
  R.eye_mult(var_init);
}

_Vector4f 
AP_KF::run(const Vector2f &att, const Vector2f &gyro)
{
  float     measure[4] = {att.x, gyro.x, att.y, gyro.y};
  _Vector4f measurement(measure);
  
  Vector2f att_filt = _att_flt_1.apply(att, _dt);
  Vector2f att_diff = (att - att_filt);
  att_diff.x *= att_diff.x;
  att_diff.y *= att_diff.y;
  _att_var = _att_flt_2.apply(att_diff, _dt);
 
  Vector2f gyro_filt = _gyro_flt_1.apply(gyro, _dt);
  Vector2f gyro_diff = (gyro - gyro_filt);
  gyro_diff.x *= gyro_diff.x;
  gyro_diff.y *= gyro_diff.y;
  _gyro_var = _gyro_flt_2.apply(gyro_diff, _dt);
  
  float var[4] = {_att_var.x, _gyro_var.x, _att_var.y, _gyro_var.y};
  R.eye();
  R.eye_mult(var);
  
  _state_estimate = A * _state_estimate;
  
  float A_transposed[4][4] = {A.get(0,0), A.get(1,0), A.get(2,0), A.get(3,0),
                              A.get(0,1), A.get(1,1), A.get(2,1), A.get(3,1),
                              A.get(0,2), A.get(1,2), A.get(2,2), A.get(3,2),
                              A.get(0,3), A.get(1,3), A.get(2,3), A.get(3,3)};
  _Matrix4f A_trans(A_transposed);
  
  P = A*P*A_trans + Q;
  
  float C_transposed[4][4] = {C.get(0,0), C.get(1,0), C.get(2,0), C.get(3,0),
                              C.get(0,1), C.get(1,1), C.get(2,1), C.get(3,1),
                              C.get(0,2), C.get(1,2), C.get(2,2), C.get(3,2),
                              C.get(0,3), C.get(1,3), C.get(2,3), C.get(3,3)};
  _Matrix4f C_trans(C_transposed);
  
  _Matrix4f temp = R + C * P * C_trans;
  temp.diagonal_array_inv();
  
  K = P * C_trans * temp;
  _state_estimate += K * (measurement - C * _state_estimate);
  
  _Matrix4f eye(d);
  P = (eye - K * C) * P;
  
  return _state_estimate;
}