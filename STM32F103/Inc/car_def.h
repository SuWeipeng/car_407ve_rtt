/*  0 - Mecanum small base, TT motor
 *  1 - Mecanum middle base, 520 motor
 *  2 -
 *  3 -
 *  4 -
 *  5 -
 */
#define CAR_TYPE               5

#if CAR_TYPE == 0
#define BASE_TYPE              0 // 0-Small, 1-Middle, 2-Test
#define MOTOR_TYPE             0 // 0-TT, 1-520, 2-DC130
#endif

#if CAR_TYPE == 1
#define BASE_TYPE              1
#define MOTOR_TYPE             1
#endif

#if CAR_TYPE == 5
#define BASE_TYPE              3
#define MOTOR_TYPE             0
#endif
