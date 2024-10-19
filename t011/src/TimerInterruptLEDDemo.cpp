/****************************************************************************************************************************
  TimerInterruptLEDDemo.ino
  For Teensy boards
  Written by Khoi Hoang

  Built by Khoi Hoang https://github.com/khoih-prog/Teensy_TimerInterrupt
  Licensed under MIT license

  Now even you use all these new 16 ISR-based timers,with their maximum interval practically unlimited (limited only by
  unsigned long miliseconds), you just consume only one Teensy timer and avoid conflicting with other cores' tasks.
  The accuracy is nearly perfect compared to software timers. The most important feature is they're ISR-based timers
  Therefore, their executions are not blocked by bad-behaving functions / tasks.
  This important feature is absolutely necessary for mission-critical tasks.
*****************************************************************************************************************************/

#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

#if !( defined(CORE_TEENSY) || defined(TEENSYDUINO) )
  #error This code is designed to run on Teensy platform! Please check your Tools->Board setting.
#endif

// These define's must be placed at the beginning before #include "TeensyTimerInterrupt.h"
// _TIMERINTERRUPT_LOGLEVEL_ from 0 to 4
// Don't define _TIMERINTERRUPT_LOGLEVEL_ > 0. Only for special ISR debugging only. Can hang the system.
// Don't define TIMER_INTERRUPT_DEBUG > 2. Only for special ISR debugging only. Can hang the system.
#define TIMER_INTERRUPT_DEBUG         0
#define _TIMERINTERRUPT_LOGLEVEL_     0

#define LED_BLUE          2
#define LED_RED           3
#define LED_YELLOW        4

// To be included only in main(), .ino with setup() to avoid `Multiple Definitions` Linker Error
#include "TeensyTimerInterrupt.h"

// To be included only in main(), .ino with setup() to avoid `Multiple Definitions` Linker Error
#include "Teensy_ISR_Timer.h"

#define HW_TIMER_INTERVAL_MS      1L

// You can select Teensy Hardware Timer  from TEENSY_TIMER_1 or TEENSY_TIMER_3

// Init Teensy timer TEENSY_TIMER_1
TeensyTimer ITimer(TEENSY_TIMER_1);

// Init Teensy_ISR_Timer
// Each Teensy_ISR_Timer can service 16 different ISR-based timers
Teensy_ISR_Timer ISR_Timer;

#define TIMER_INTERVAL_0_01S          1L
#define TIMER_INTERVAL_0_5S           500L
#define TIMER_INTERVAL_1S             1000L
#define TIMER_INTERVAL_1_5S           1500L
#define TIMER_INTERVAL_2S             2000L
#define TIMER_INTERVAL_3S             3000L

extern void lcd_setup(void);
extern LiquidCrystal_I2C lcd(int,int,int);

void TimerHandler()
{
  ISR_Timer.run();
}

volatile int x;

// In Teensy, avoid doing something fancy in ISR, for example complex Serial.print with String() argument
// The pure simple Serial.prints here are just for demonstration and testing. Must be eliminate in working environment
// Or you can get this run-time error / crash
void doingSomething1()
{
  digitalWrite(LED_YELLOW, !digitalRead(LED_YELLOW));
}
void doingSomething2()
{
  digitalWrite(LED_BLUE, !digitalRead(LED_BLUE));
}
void doingSomething3()
{
  digitalWrite(LED_RED, !digitalRead(LED_RED));
}
void cyclic() {
  digitalWrite(24+x,LOW);
  x++;
  if (x>7) x=0;
  digitalWrite(24+x,HIGH);

}
void setup() {
  x = 0;
  Serial.begin(115200);
  //while (!Serial);

  delay(100);
  
  Serial.print(F("\nStarting TimerInterruptLEDDemo on ")); Serial.println(BOARD_NAME);
  Serial.println(TEENSY_TIMER_INTERRUPT_VERSION);
  Serial.print(F("CPU Frequency = ")); Serial.print(F_CPU / 1000000); Serial.println(F(" MHz"));

  // Instantiate HardwareTimer object. Thanks to 'new' instanciation, HardwareTimer is not destructed when setup() function is finished.
  //HardwareTimer *MyTim = new HardwareTimer(Instance);

  // configure pin in output mode
  pinMode(LED_BUILTIN,  OUTPUT);
  pinMode(LED_BLUE,     OUTPUT);
  pinMode(LED_RED,      OUTPUT);
  pinMode(24, OUTPUT);
  pinMode(25, OUTPUT);
  pinMode(26, OUTPUT);
  pinMode(27, OUTPUT);
  pinMode(28, OUTPUT);
  pinMode(29, OUTPUT);
  pinMode(30, OUTPUT);
  pinMode(31, OUTPUT);
  digitalWrite(25,HIGH);
  // Interval in microsecs
  if (ITimer.attachInterruptInterval(HW_TIMER_INTERVAL_MS * 1000, TimerHandler))
  {
    Serial.print(F("Starting ITimer OK, millis() = ")); Serial.println(millis());
  }
  else
    Serial.println(F("Can't set ITimer. Select another freq. or timer"));

  // Just to demonstrate, don't use too many ISR Timers if not absolutely necessary
  // You can use up to 16 timer for each ISR_Timer
  ISR_Timer.setInterval(TIMER_INTERVAL_1S,  doingSomething1);
  ISR_Timer.setInterval(TIMER_INTERVAL_2S,  doingSomething2);
  ISR_Timer.setInterval(TIMER_INTERVAL_3S,  doingSomething3);
  ISR_Timer.setInterval(TIMER_INTERVAL_0_01S,cyclic);
  lcd_setup();
}


void loop()
{
  /* Nothing to do all is done by hardware. Even no interrupt required. */
}
