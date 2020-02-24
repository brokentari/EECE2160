#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <iostream> 
#include "WiimoteBtns.h"

int main() {
	Wiimote wiimote;
	wiimote.Listen();
}
