#ifndef WIIMOTEBTN_H
#define WIIMOTEBTN_H

using namespace std;

class Wiimote {
	private:
		int fd;
	public:
		Wiimote() {
			fd = open("/dev/input/event2", O_RDONLY);
			if (fd == -1) {
 				cerr << "Error: Could not open event file -forgot sudo?\n";
				exit(1);
			}
		}

		~Wiimote() {
			close(fd);
		}
		void Listen();
		void ButtonEvent(int code, int value);
};

#endif
