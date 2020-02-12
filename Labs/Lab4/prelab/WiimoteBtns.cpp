#include <iostream>
#include <cstdlib>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <bitset>
#include <string>
#include <stdlib.h>

using namespace std;


class Wiimote {
    private:
        int fd;

    public:
        Wiimote() {
            fd = open("/dev/input/event0", O_RDONLY); 
            if (fd == -1) {
                cerr << "Error: Could not open event file -forgot sudo?\n";
                exit(1);
            }
            while (true) {
                // Read a packet of 16 bytes from Wiimote
                char buffer[16];
                read(fd, buffer, 16);

                // Extract code (byte 10) and value (byte 12) from packet
                int code = buffer[10];
                short acceleration = * (short *) (buffer + 12);

                // Print item
                cout << "Code: " << code << ", acceleration, " << acceleration << endl;
            }
        }

       ~Wiimote() {
           close(fd);
       } 
};

int main() {
    Wiimote wiimote;
}