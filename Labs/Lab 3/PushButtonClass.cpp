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

const int gpio_led1_offset = 0x12C; // Offset for LED1
const int gpio_led2_offset = 0x130; // Offset for LED2
const int gpio_led3_offset = 0x134; // Offset for LED3
const int gpio_led4_offset = 0x138; // Offset for LED4
const int gpio_led5_offset = 0x13C; // Offset for LED5
const int gpio_led6_offset = 0x140; // Offset for LED6
const int gpio_led7_offset = 0x144; // Offset for LED7
const int gpio_led8_offset = 0x148; // Offset for LED8

const int gpio_sw1_offset = 0x14C; // Offset for Switch 1
const int gpio_sw2_offset = 0x150; // Offset for Switch 2
const int gpio_sw3_offset = 0x154; // Offset for Switch 3
const int gpio_sw4_offset = 0x158; // Offset for Switch 4
const int gpio_sw5_offset = 0x15C; // Offset for Switch 5
const int gpio_sw6_offset = 0x160; // Offset for Switch 6
const int gpio_sw7_offset = 0x164; // Offset for Switch 7
const int gpio_sw8_offset = 0x168; // Offset for Switch 8

const int gpio_pbtnl_offset = 0x16C; // Offset for left push button
const int gpio_pbtnr_offset = 0x170; // Offset for right push button
const int gpio_pbtnu_offset = 0x174; // Offset for up push button
const int gpio_pbtnd_offset = 0x178; // Offset for down push button
const int gpio_pbtnc_offset = 0x17C; // Offset for center push button

class ZedBoard
{
	char *pBase;
	int fd;

public:
	ZedBoard()
	{
		fd = open("/dev/mem", O_RDWR);
		pBase = (char *)mmap(NULL, gpio_size, PROT_READ | PROT_WRITE, MAP_SHARED,
							 fd, gpio_address);

		if (pBase == MAP_FAILED)
		{
			cerr << "Mapping I/O memory failed - Did you run with 'sudo'?\n";
			exit(1);
		}
	}

	~ZedBoard()
	{
		munmap(pBase, gpio_size);
		close(fd);
	}

	void RegisterWrite(int offset, int value)
	{
		*(int *)(pBase + offset) = value;
	}

	int RegisterRead(int offset)
	{
		return *(int *)(pBase + offset);
	}

	void Write1Led(int ledNum, int state)
	{
		if (0 >= ledNum > 7)
		{
			cerr << "Trying to write to a non-existing LED" << endl;
		}
		int ledOffset = 0x12C + (ledNum * 4);
		this->RegisterWrite(ledOffset, state);
	}

	int Read1Switch(int switchNum)
	{
		if (0 > switchNum && switchNum > 7)
		{
			cerr << "Trying to read a non-existing switch" << endl;
		}
		int switchOffset = 0x14C + (switchNum * 4);
		this->RegisterRead(switchOffset);
	}

	void WriteAllLeds(int value)
	{
		bitset<8> bits(value);
		for (int i = 0; i < 8; i++)
		{
			this->Write1Led(i, bits[i]);
		}
	}

	int ReadAllSwitch()
	{
		bitset<8> switches;
		for (int i = 0; i < 8; i++)
		{
			switches.set(i, this->Read1Switch(i));
		}

		int switch_list = (int)(switches.to_ulong());
		return switch_list;
	}

	int ReadButton(int value)
	{
		bitset<8> buttons(value);
		cout << "Previous value: " << value << endl;
		if (this->RegisterRead(0x16C) == 1)
		{
			sleep(1);
			buttons <<= 1;
		}
		else if (this->RegisterRead(0x170) == 1)
		{
			sleep(1);
			buttons >>= 1;
		}
		else if (this->RegisterRead(0x174) == 1)
		{
			sleep(1);
			return value + 1;
		}
		else if (this->RegisterRead(0x178) == 1)
		{
			sleep(1);
			return value - 1;
		}
		else if (this->RegisterRead(0x17C) == 1)
		{
			sleep(1);
			buttons = this->ReadAllSwitch();
		}
		int button_list = (int)(buttons.to_ulong());
		return button_list;
	}
};

int main()
{
	ZedBoard zb;
	// ************** Put your code here **********************
	int value = 0;
	while (true)
	{
		if (value == zb.ReadButton(value))
		{
			value = value;
		}
		else
		{
			value = zb.ReadButton(value);
		}
	}

	zb.~ZedBoard();
}