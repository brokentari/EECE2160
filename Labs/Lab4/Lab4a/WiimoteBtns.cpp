#include <iostream>
#include <cstdlib>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <bitset>
#include <string>
#include <stdlib.h>
#include "WiimoteBtns.h"


void Wiimote::ButtonEvent(int code, int value) {
	std::cout << "Code = " << code << ", value = " << value << '\n';
}

void Wiimote::Listen() {
	while(true) {
		// Read a packet of 32 bytes from Wiimote
 		char buffer[32];
 		read(fd, buffer, 32);

 		// Extract code (byte 10) and value (byte 12) from packet
		int code = buffer[10];
		int value = buffer[12];
		ButtonEvent(code, value);
	}
}
