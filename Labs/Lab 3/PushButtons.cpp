#include <iostream>
#include <cstdlib>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <bitset>
#include <string>
#include <stdlib.h>

using namespace std;

// Physical base address of GPIO
const unsigned gpio_address = 0x400d0000;

// Length of memory-mapped IO window
const unsigned gpio_size = 0xfff;

const int gpio_led1_offset = 0x12C;  // Offset for LED1
const int gpio_led2_offset = 0x130;  // Offset for LED2
const int gpio_led3_offset = 0x134;  // Offset for LED3
const int gpio_led4_offset = 0x138;  // Offset for LED4
const int gpio_led5_offset = 0x13C;  // Offset for LED5
const int gpio_led6_offset = 0x140;  // Offset for LED6
const int gpio_led7_offset = 0x144;  // Offset for LED7
const int gpio_led8_offset = 0x148;  // Offset for LED8

const int gpio_sw1_offset = 0x14C;  // Offset for Switch 1
const int gpio_sw2_offset = 0x150;  // Offset for Switch 2
const int gpio_sw3_offset = 0x154;  // Offset for Switch 3
const int gpio_sw4_offset = 0x158;  // Offset for Switch 4
const int gpio_sw5_offset = 0x15C;  // Offset for Switch 5
const int gpio_sw6_offset = 0x160;  // Offset for Switch 6
const int gpio_sw7_offset = 0x164;  // Offset for Switch 7
const int gpio_sw8_offset = 0x168;  // Offset for Switch 8

const int gpio_pbtnl_offset = 0x16C;  // Offset for left push button
const int gpio_pbtnr_offset = 0x170;  // Offset for right push button
const int gpio_pbtnu_offset = 0x174;  // Offset for up push button
const int gpio_pbtnd_offset = 0x178;  // Offset for down push button
const int gpio_pbtnc_offset = 0x17C;  // Offset for center push button

/**
 * Write a 4-byte value at the specified general-purpose I/O location.
 *
 * @param pBase		Base address returned by 'mmap'.
 * @parem offset	Offset where device is mapped.
* @ return Switch value read

* @param value		Value to be written.
*
* @param switchNum Switch number (0 to 7)
*/
void RegisterWrite(char *pBase, int offset, int value)
{
	* (int *) (pBase + offset) = value;
}/** Reads the value of a switch
* - Users base address of I/O
* @param pBase base address of I/O


/**
 * Read a 4-byte value from the specified general-purpose I/O location.
 *
 * @param pBase		Base address returned by 'mmap'.
 * @param offset	Offset where device is mapped.
 * @return		Value read.
 */
int RegisterRead(char *pBase, int offset)
{
	return * (int *) (pBase + offset);
}

/**
 * Initialize general-purpose I/O
 *  - Opens access to physical memory /dev/mem
 *  - Maps memory at offset 'gpio_address' into virtual address space
 *
 * @param  fd	File descriptor passed by reference, where the result
 *		of function 'open' will be stored.
 * @return	Address to virtual memory which is mapped to physical,
 *          	or MAP_FAILED on error.
 */
char *Initialize(int *fd)
{
	*fd = open( "/dev/mem", O_RDWR);
	return (char *) mmap(NULL, gpio_size, PROT_READ | PROT_WRITE, MAP_SHARED,
		*fd, gpio_address);
}

/**
 * Close general-purpose I/O.
 *
 * @param pBase	Virtual address where I/O was mapped.
 * @param fd	File descriptor previously returned by 'open'.
 */
void Finalize(char *pBase, int fd)
{
	munmap(pBase, gpio_size);
	close(fd);
}

/** Changes the state of an LED (ON or OFF)
* @param pBase base address of I/O
* @param ledNum LED number (0 to 7)
* @param state State to change to (ON or OFF)
*/
void Write1Led(char *pBase, int ledNum, int state) {
	if (0 >= ledNum > 7) {
		cerr << "Trying to write to a non-existing LED" << endl;
	}
	int ledOffset = 0x12C + (ledNum * 4);
	RegisterWrite(pBase, ledOffset, state);
}

/** Reads the value of a switch
* - Users base address of I/O
* @param pBase base address of I/O
* @param switchNum Switch number (0 to 7)
* @ return Switch value read
*/
int Read1Switch(char *pBase, int switchNum) {
	if (0 > switchNum && switchNum > 7)
	{
		cerr << "Trying to read a non-existing switch" << endl;
	}
	int switchOffset = 0x14C + (switchNum * 4);
	RegisterRead(pBase, switchOffset);
}

void WriteAllLeds(char *pBase, int value) {	
	Write1Led(pBase, 0, value % 2);
	Write1Led(pBase, 1, (value / 2) % 2);
	Write1Led(pBase, 2, (value / 4) % 2);
        Write1Led(pBase, 3, (value / 8) % 2);
 	Write1Led(pBase, 4, (value / 16) % 2);
        Write1Led(pBase, 5, (value / 32) % 2);
        Write1Led(pBase, 6, (value / 64) % 2);
        Write1Led(pBase, 7, (value / 128) % 2);

}

int ReadAllSwitch(char *pBase) {
	bitset<8> switches;
  	for (int i = 0; i < 8; i++) {
		switches.set(i, Read1Switch(pBase, i));
	}

	int switch_list= (int)(switches.to_ulong());
	return switch_list;
}

int ReadButton(char *pBase, int value) {
	bitset<8> buttons(value);	
		cout << "Previous value: " << value << endl;
		if(RegisterRead(pBase, 0x16C) == 1) {
			sleep(1); 
			buttons <<= 1;
       			 cout << "New bitset: " << buttons << endl;
		} 
		else if(RegisterRead(pBase, 0x170) == 1) {	
			sleep(1);
			buttons >>= 1;	
	        	cout << "New bitset: " << buttons << endl;
		}
		else if(RegisterRead(pBase, 0x174) == 1) {
			sleep(1);
			cout << "New value: " << value + 1 << endl;
			return value + 1;
		}
		else if(RegisterRead(pBase, 0x178) == 1) {
			sleep(1);
			cout << "New value: " << value - 1 << endl;
			return value - 1;

		}		
		else if(RegisterRead(pBase, 0x17C) == 1) {
			sleep(1);
			buttons = ReadAllSwitch(pBase);
	        	cout << "New bitset: " << buttons << endl;

		}
		int button_list = (int)(buttons.to_ulong());
		return button_list;
}

int main()
{
	// Initialize
	int fd;
	char *pBase = Initialize(&fd);

	// Check error
	if (pBase == MAP_FAILED)
	{
		cerr << "Mapping I/O memory failed - Did you run with 'sudo'?\n";
		exit(1);
	}	
	
// ************** Put your code here **********************
	int value = 0;
	while (true) {
		if (value == ReadButton(pBase, value)) {
			value = value;
		}
		else {
			value = ReadButton(pBase, value);
		}
		WriteAllLeds(pBase, value);
	}
	Finalize(pBase, fd);
	return 0;
}
