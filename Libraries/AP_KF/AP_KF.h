#ifndef __AP_KF_H__
#define __AP_KF_H__
#include <matrixN.h>

typedef MatrixN<float,4> _Matrix4f;

class AP_KF
{
public:
  AP_KF();
  ~AP_KF();
  
  void set_dt(const float dt) { _dt = dt; }
  void var_init(const float var_acc, const float var_gyro);

private:  
  float _dt;
  float _var_acc_init;
  float _var_gyro_init;
  
  _Matrix4f A;
};
#endif /* __AP_KF_H__ */