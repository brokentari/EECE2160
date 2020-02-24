#include <iostream>
#include <cstdlib>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <bitset>
#include <string>
#include <stdlib.h>

using namespace std;


class WiimoteButns {
    private:
        int fd;
    
    public:
        WiimoteButns() {
            fd = open("/dev/input/event2", O_RDONLY);
            
        }

        ~WiimoteButns() {
            close(fd);
        }

        void ButtonEvent(int code, int value) {
                cout << "Code: " << code << ", value, " << value << endl;
        }

        void Listen() {
            while (true) {
                // Read a packet of 16 bytes from Wiimote
                char buffer[32];
                read(fd, buffer, 32);

                // Extract code (byte 10) and value (byte 12) from packet
                int code = buffer[10];
                int value = buffer[12];
                AccelerationEvent(code, value);
            }
        }
};

int main() {
    WiimoteButns wiimote;
    WiimoteButns.Listen();
}