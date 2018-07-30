#ifndef LIFE_HPP_
#define LIFE_HPP_

class Life
{
	std::string _filename;
	bool** _grid1;
	bool** _grid2;
	int _width;
	int _height;
	bool _gridToggle;
	void printToFile(std::string filename);
public:
	Life() :_filename(""), _grid1(nullptr), _grid2(nullptr), _width(0), _height(0), _gridToggle(false) {};
	~Life();
	explicit Life(std::string filename);
	void initialize(std::string filename);
	void execute(int iterations);
};

#endif