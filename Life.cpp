#include "Header.hpp"

Life::Life(std::string filename)
{
	initialize(filename);
}

Life::~Life()
{
	for (int i = 0; i < _height; i++)
	{
		delete[] _grid1[i];
		delete[] _grid2[i];
	}
	delete[] _grid1;
	delete[] _grid2;
}

void Life::initialize(std::string filename)
{
	{
		const size_t dotPosition = filename.find_last_of('.');
		_filename = filename.substr(0, dotPosition);
	}
	std::ifstream file;
	file.open(filename, std::ios::in);
	if (!file.is_open())
	{
		std::cout << "File " << filename << " not found." << std::endl;
		exit(2);
	}
	{
		std::string input;
		int rows = 0, columns, lineWidth = -1;
		std::queue<bool> contents;
		while (!file.eof())
		{
			getline(file, input);
			columns = 0;
			for (char c : input)
			{
				switch (c)
				{
				case '1':
				case '0':
					columns++;
					contents.push(c == '1' ? 1 : 0);
					break;
				default:
					break;
				}
			}
			if (lineWidth == -1) // applying the width of the first line in the file
			{
				lineWidth = columns;
			}
			else if (columns != lineWidth) // if the line width varies, we do not want to continue executing the app
			{
				std::cout << "Incorrect data in file " << filename << "." << std::endl;
				exit(3);
			}
			rows++;
		}
		if (rows > 0 && lineWidth > 0) // if we managed to read data from file, lets create the world
		{
			_grid1 = new bool*[rows];
			_grid2 = new bool*[rows];
			for (int i = 0; i < rows; i++)
			{
				_grid1[i] = new bool[lineWidth];
				_grid2[i] = new bool[lineWidth];
			}
			for (int i = 0; i < rows; i++)
			{
				for (int j = 0; j < lineWidth; j++)
				{
					_grid1[i][j] = contents.front();
					_grid2[i][j] = contents.front();
					contents.pop();
				}
			}
			_height = rows;
			_width = lineWidth;
		}
	}
	file.close();
}

void Life::execute(int iterations)
{
	std::cout << "Executing " << iterations << " iterations" << std::endl;
	for (int i = 0; i < iterations; i++)
	{
		bool** grid = _gridToggle == true ? _grid2 : _grid1;
		bool** otherGrid = _gridToggle == true ? _grid1 : _grid2;
		for (int j = 0; j < _height; j++)
		{
			for (int k = 0; k < _width; k++)
			{
				int neighbours = 0;
				for (int l = -1; l <= 1; l++)
				{
					for (int m = -1; m <= 1; m++)
					{
						if (l == 0 && m == 0) continue;
						if (j + l < 0 || j + l > _height - 1 || k + m < 0 || k + m > _width - 1) continue;
						neighbours += grid[j + l][k + m];
					}
				}
				if (grid[j][k] == true)
				{
					otherGrid[j][k] = neighbours > 1 && neighbours < 4 ? true : false;
				}
				else
				{
					otherGrid[j][k] = neighbours == 3 ? true : false;
				}
			}
		}
		std::ostringstream oss;
		int digits = 0, temp = iterations;
		while (temp != 0)
		{
			temp /= 10;
			digits++;
		}
		oss << _filename << std::setw(digits) << std::setfill('0') << i + 1 << ".csv";
		printToFile(oss.str());
		_gridToggle = !_gridToggle;
	}
}

void Life::printToFile(std::string filename)
{
	std::ofstream file;
	file.open(filename, std::ios::out);
	if (!file.is_open())
	{
		std::cout << "File " << filename << " could not be created." << std::endl;
		exit(2);
	}
	bool** print = _gridToggle == true ? _grid2 : _grid1;
	for (int i = 0; i < _height; i++)
	{
		for (int j = 0; j < _width; j++)
		{
			file << print[i][j];
			if (j < _width - 1) file << ',';
		}
		if (i < _height - 1) file << std::endl;
	}
	file.close();
}
