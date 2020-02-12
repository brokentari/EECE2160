#include <iostream>
#include <cstdlib>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <bitset>
#include <string>
#include <stdlib.h>

using namespace std;

class WiimoteAccel {
    private:
        int fd;
    
    public:
        WiimoteAccel() {
            fd = open("/dev/input/event0", O_RDONLY);
            
        }

        ~WiimoteAccel() {
            close(fd);
        }

        virtual void AccelerationEvent(int code, int acceleration) {
                cout << "Code: " << code << ", acceleration, " << acceleration << endl;
        }

        void Listen() {
            while (true) {
                // Read a packet of 16 bytes from Wiimote
                char buffer[16];
                read(fd, buffer, 16);

                // Extract code (byte 10) and value (byte 12) from packet
                int code = buffer[10];
                short acceleration = * (short *) (buffer + 12);
                AccelerationEvent(code, acceleration);
            }
        }
};

int main() {
    WiimoteAccel wiimote;
    wiimote.Listen();
}