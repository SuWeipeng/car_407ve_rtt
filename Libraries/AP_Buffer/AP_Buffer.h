#ifndef __AP_BUFFER_H__
#define __AP_BUFFER_H__

class AP_Buffer_Backend;

class AP_Buffer{
  friend class AP_Buffer_Backend;
  friend class AP_Buffer_Ring;
public:
  AP_Buffer();
  ~AP_Buffer(){};
  
  // get singleton
  static AP_Buffer *get_instance(void) {
    return _instance;
  }
  
private:
  static AP_Buffer*       _instance;
  AP_Buffer_Backend*      _backend;
};

#endif /* __AP_BUFFER_H__ */