#include "Cursor.hpp"


std::string::size_type sz;     // alias of size_t

std::string location::toString()
{
		std::string locString = "";
		locString.append("(" + std::to_string(x) + "," + std::to_string(y) + ")");
		return locString;
};

Cursor::Cursor()
{}
void Cursor::initSender()
{
    /* Create the FIFO if it does not exist */
    umask(0);
		//std::cout << "Done unmasking." << std::endl;
    std::remove(FIFO_FILE);
		int err = mknod(FIFO_FILE, S_IRWXU, 0);
		std::cout << err << std::endl;
		//std::cout << "done making " << FIFO_FILE << std::endl;

	return;
}

void Cursor::sendCursor(location loc)
{
		//std::cout << "entered curser.sendcursor()" << std::endl;
		if(previousLocation.x == -1 && previousLocation.y == -1)
			previousLocation = loc;
		//std::cout << "saved previouslocation" << std::endl;
		
		fp = fopen(FIFO_FILE, "w");
		if (!fp)
			perror("fopen");
		//std::cout << "opened file" << std::endl;

		std::string locString = loc.toString();
		const char * c = locString.c_str();
		fputs(c, fp);
		//std::cout << "Sent " << locString << " to FIFO" << std::endl;
		fclose(fp);
		return;
}



location Cursor::receiveCursor()
{
		//std::cout << "in receiveCursor" << std::endl;
		char readbuf[15];
		
		//std::cout << "created buffer" << std::endl;
		fp = fopen(FIFO_FILE, "r");

		fgets(readbuf, 15, fp);
		
		fclose(fp);

		std::string s = std::string(readbuf);

		//std::cout << s << std::endl;
		
		
		
		size_t start = s.find(",");
		size_t end = s.find(")", start);
		std::string sub = "";
		if(end - start -1 >=0 && start + 1 <= s.size())
		{
			sub = s.substr(start + 1, end - start -1);
			//std::cout << sub << std::endl ;
		}
		int  yValue = -1;
		if (sub != "")
		{
			yValue = std::stoi(sub, &sz);
		}

		start = s.find("(");
		end = s.find(",",start);
		sub = "";
		if(start +1 >= 0 && end - start -1 <= s.size())
		{
			sub = s.substr(start+1, end - start -1);
			//std::cout << sub << std::endl;
		}
		int xValue = -1;
		if(sub != "")
		{
			xValue = std::stoi(sub, &sz);
		}
		location l = {xValue, yValue};		
		//std::cout << "Received location at: " << readbuf << std::endl;
		return l; 

}

Cursor::~Cursor()
{
}
