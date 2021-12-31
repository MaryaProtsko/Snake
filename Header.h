#include<vector>

enum Direction { UP = 1, RIGHT, DOWN, LEFT };

struct snake
{
	std::vector<short> X = { 9,8,7,6 };
	std::vector<short> Y = { 9,9,9,9 };
	void move(Direction);
	bool check();
};

struct apple
{
	short X;
    short Y;
	void set(snake&);
};

