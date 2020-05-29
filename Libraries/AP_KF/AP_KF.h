#ifndef __AP_KF_H__
#define __AP_KF_H__
#include <matrixN.h>
#include <LowPassFilter.h>

typedef VectorN<float,4> _Vector4f;
typedef MatrixN<float,4> _Matrix4f;

class AP_KF
{
public:
  AP_KF();
  ~AP_KF();
  
  void      set_dt(const float &dt) { _dt = dt; }
  void      set_var(const float &var_acc, const float &var_gyro);
  _Vector4f run(const Vector2f &att, const Vector2f &gyro);

private:  
  float _dt;
  float _var_acc_init[2];  // 0-roll, 1-pitch
  float _var_gyro_init[2]; // 0-roll, 1-pitch
  float _d[4] = {1.0f, 1.0f, 1.0f, 1.0f};
  
  _Matrix4f A{_d};
  _Matrix4f C{_d};
  _Matrix4f P{_d};
  _Matrix4f Q{_d};
  _Matrix4f R{_d};
  _Matrix4f K{_d};
  _Vector4f _state_estimate;
  
  LowPassFilterVector2f  _att_flt_1{5.0f},  _att_flt_2{3.0f};
  LowPassFilterVector2f _gyro_flt_1{2.0f}, _gyro_flt_2{2.0f};
};
#endif /* __AP_KF_H__ */