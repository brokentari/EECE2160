#include <iostream>
#include <cstdlib>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include "Zedboard.h"

using namespace std;

ZedBoard::ZedBoard()
{
	  cout << "\n Starting...." << endl;
	  // Open device memory
	  fd = open( "/dev/mem", O_RDWR);
	  pBase = (char *) mmap(NULL,gpio_size,PROT_READ | PROT_WRITE,
	        MAP_SHARED,fd,gpio_address);
	  // Check error 
	  if (pBase == MAP_FAILED)
	  {
		  cerr << "Mapping I/O memory failed - Did you run with 'sudo'?\n";
	  	  exit(1); // Returns 1 to the operating system;
	  }
}

/**
 * Destructor to close general-purpose I/O.
 * - Uses virtual address where I/O was mapped.
 * - Uses file descriptor previously returned by 'open'.
 *
 * @param  None	Destructor does not need arguments.
 * @return	None Destructor does not return anything.
 */
ZedBoard::~ZedBoard()
{
	  munmap(pBase, gpio_size);
	  close(fd);
	  cout << "\n Terminating...." << endl;
}


/**
 * Write a 4-byte value at the specified general-purpose I/O location.
 *
 * - Uses base address returned by 'mmap'.
 *
 * @parem offset	Offset where device is mapped.
 * @param value		Value to be written.
 */
void ZedBoard::RegisterWrite(int offset, int value)
{
	  * (int *) (pBase + offset) = value;
}

/**
 * Read a 4-byte value from the specified general-purpose I/O location.
 *
 * - Uses base address returned by 'mmap'.
 *
 * @param offset	Offset where device is mapped.
 * @return		    Value read
 */
int ZedBoard::RegisterRead(int offset)
{
	  return * (int *) (pBase + offset);
}

/** Changes the state of an LED (ON or OFF)
 * - Uses base address returned by 'mmap'
 *
 * @param ledNum   LED number (0 to 7)
 * @param state    State to change to (ON or OFF)
 */ 
void ZedBoard::Write1Led (int ledNum, int state)
{
    RegisterWrite(gpio_led1_offset+ledNum*4, state);
}

/** Set the state of LEDs to the lower 8 bits of a given value.
 * - Calls Write1Led() to set all LEDs 
 * - Uses base address returned by 'mmap'
 *
 *@param value    Value between 0 and 255 shown on LEDs
 */
void ZedBoard::WriteAllLeds(int value)
{
    for (int i=0; i<8 ; ++i)
    {
        Write1Led (i, (value >> i) & 1); //(value >> i) & 1 -> extract i bit of value
        //Write1Led (i, (value >> i) % 2);  // equivalent option
        //Write1Led (i, (value/(1 << i) % 2);  // equivalent option
    }
}