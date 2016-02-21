#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string>
#include <iostream>
#include <linux/stat.h>

#define FIFO_FILE       "/home/pi/HackISU2016/cursor_fifo"

struct location {
	  int x;
		int y;

		std::string toString();
};

class Cursor
{
	//The cursor fifo will hold the most recent value in this format: (float x, float y)
	public:
			Cursor();
			~Cursor();

			void initSender();

			location previousLocation = { -1, -1};
			void sendCursor(location loc);
			location receiveCursor();

	private:
		FILE *fp;
};
