#pragma once
#include <string>
class Base
{
public:
	bool			b_startMenu;
	std::string*	b_path;

	Base();

	void			StartMenu();

private:

	void			GetPath(int num);
};

