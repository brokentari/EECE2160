#ifndef WIIMOTEACCEL_H
#define WIIMOTEACCEL_H

using namespace std;

class WiimoteAccel {
	private:
		int fd;
	public:
		WiimoteAccel() {
			fd = open("/dev/input/event0", O_RDONLY);
			if (fd == -1) {
 				cerr << "Error: Could not open event file -forgot sudo?\n";
				exit(1);
			}
		}

		~WiimoteAccel() {
			close(fd);
		}
		void Listen();
		virtual void AccelerationEvent(int code, int acceleration);
};

#endif