#include <string>
#include <iostream>
#include <cstdio>
#include <unistd.h>

#include "serial/serial.h"

int main(int argc, char *argv[])
{
	std::string port = "/dev/" + std::string(argv[1]);
	
	unsigned long baud = 0;
	sscanf(argv[2], "%lu", &baud);

	serial::Serial my_serial(port, baud, serial::Timeout::simpleTimeout(1000));

	std::cout << "serial port " + port + " (baud=" + std::to_string(baud) + "): ";
	if(my_serial.isOpen()) std::cout << "open";
	else std::cout << "closed";
	std::cout << "\n\n";

	my_serial.write("s");

	//my_serial.write('\2', 1);
	//my_serial.write('\3', 1);
	//my_serial.write('\0', 1);

	std::string buffer;
	my_serial.readline(buffer);

	std::cout << buffer << "\n\n";

	my_serial.close();
}