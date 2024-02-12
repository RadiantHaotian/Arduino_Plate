#ifndef _Plate_H_
#define _Plate_H_
#include <Arduino.h>
#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_TFTLCD.h> // Hardware-specific library
#include <TouchScreen.h>
#include <Servo.h>

#include <EEPROM.h>

#define D0 6
#define D1 7
#define D2 8
#define D3 49
#define D4 48
#define D5 47
#define D6 46
#define D7 45


extern void run_gamepad_mecanum();
extern void Plate_Setup();
extern void move(int s1,int s2,int t);
extern void motor(char pin ,int Speed);
extern void set_servo_position(char pin, int val);
extern void msleep(unsigned int time);
extern int analog(int s);
extern bool digital(int s);
extern double seconds();
extern void print_int(int y,int tp_value);
extern void print_string(int y,String tp_name);
extern void run_gamepad(int speed,int pts);
extern void end();
extern bool button(int s);
extern void ROM_Setup();
extern void Screen_Calibration();

#endif