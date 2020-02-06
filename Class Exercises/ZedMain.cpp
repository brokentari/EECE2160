#include "ZedBoard.h"
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <iostream>

using namespace std;

/**
 * Operates the Zedboard LEDs and switches
 */
int main()
{
	// Initialize
	ZedBoard *zed = new ZedBoard();	
	
	int value = 0;
	cout << "Enter a value less than 256: ";
	cin >> value;
	cout << "value entered = " << value << endl;

	// Show the value on the Zedboard LEDs
	zed->SetLedNumber(value);
	delete zed;
	// Done
}
