#include "Header.hpp"

// Exit codes: 1 wrong CLI usage, 2 file not found, 3 incorrect data in file, 4 negative number of loops

int main(int argc, char* args[])
{
	if (argc != 3)
	{
		std::cout << "Usage: " << args[0] << " filename iterations" << std::endl;
		exit(1);
	}
	try
	{
		if (std::stoi(args[2]) < 0)
		{
			std::cout << "Please provide positive number of iterations." << std::endl;
			exit(4);
		}
	}
	catch (...)
	{
		std::cout << "Usage: " << args[0] << " filename iterations" << std::endl;
		exit(5);
	}
	Life gameOfLife;
	gameOfLife.initialize(args[1]);
	gameOfLife.execute(std::stoi(args[2]));
	return 0;
}
