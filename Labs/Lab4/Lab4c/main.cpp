#include <iostream>
#include <cstdlib>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include "Zedboard.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "WiimoteAccel.h"

using namespace std;

class WiimoteToLed : public WiimoteAccel {
      private:
              ZedBoard* zb;
      public:
             WiimoteToLed(ZedBoard* zedboard) {
                                zb = zedboard;
             }
             
             void AccelerationEvent(int code, int acceleration) {
                  if (code == 3) {
                     if (abs(acceleration) > 100) {
                        zb->WriteAllLeds(255);
                     } 
                     else {
                          int lights = floor(abs(acceleration) / 12.5);
                          for (int i = 0; i < 8; i++) {
                              if (i < lights) {
                                 zb->Write1Led(i, 1);
                              }
                              else {
                                   zb->Write1Led(i, 0);
                              }
                          }
                     }
                  }
             }
};
                     

int main()
{
 // Instantiate ZedBoard object statically
 ZedBoard zed_board;

 // Instantiate WiimoteToLed object statically, passing a pointer to the
 // recently created ZedBoard object.
 WiimoteToLed wiimote_to_led(&zed_board);

 // Enter infinite loop listening to events. The overridden function
 // WiimoteToLed::AccelerationEvent() will be invoked when the user moves
 // the Wiimote.
 wiimote_to_led.Listen();

 // Unreachable code, previous function has an infinite loop
 return 0;
}