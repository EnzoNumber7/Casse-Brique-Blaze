#include <iostream>
#include <fstream>
#include <vector>

#include "Map.h"

using namespace std;

/*
---------------------------------------------------------------------------------
|						 Here is the constructor								|
---------------------------------------------------------------------------------
*/

Map::Map() {
	m_ballconfig = new string;
	m_ball = 0;
	m_sizeX = 0;
	m_sizeY = 0;
	m_num = 0;
	m_vstr = new vector<string>;
	m_config = new string;
	m_error = \
		"Map is not correctly formated. Expected format would be :\n\n\
\
BallNum\n\
0000\n\
0000\n\
0000\n\
0000\n\
WidthxHeight\n\n \
\
You can change 0 by bricks health capped at 9\n \
Width max is 13\n \
Height max is 7\n \
BallNum max is 999\n";
}

/*
---------------------------------------------------------------------------------
|						 Here are the Get Methods								|
---------------------------------------------------------------------------------
*/

int		Map::GetWidth() {
	return m_sizeX;
}

int		Map::GetHeight() {
	return m_sizeY;
}

void		Map::GetSize() {
	char* x;
	char* y;
	int		lenLine = m_config->size();

	y = new char[2];
	if (m_config->at(1) >= 48 and m_config->at(1) <= 57) {
		x = new char[3];
		x[0] = m_config->at(0);
		x[1] = m_config->at(1);
		x[2] = '\0';
		y[0] = m_config->at(3);
		y[1] = '\0';
	}
	else {
		x = new char[2];
		x[0] = m_config->at(0);
		x[1] = '\0';
		y[0] = m_config->at(2);
		y[1] = '\0';
	}
	m_sizeX = stoi(x);
	m_sizeY = stoi(y);
	delete[] x;
	delete[] y;
	m_num = m_sizeX * m_sizeY;
}

int    Map::GetBall() {
	return m_ball;
}

/*
---------------------------------------------------------------------------------
|						 Here are the Check Methods								|
---------------------------------------------------------------------------------
*/

bool		Map::IsBallNumValid() {
	if (m_ball <= 0 or m_ball > 999)
		return false;
	return true;
}

bool		Map::IsBallNumFormated() {
	if (m_ballconfig->size() == 0 || m_ballconfig->size() > 3)
	{
		std::cout << m_error << std::endl;
		exit(1);
	}
	for (int i = 0; i < m_ballconfig->size(); ++i)
	{
		if (m_ballconfig->at(i) < 48 and m_ballconfig->at(i) > 57)
		{
			std::cout << m_error << std::endl;
			exit(1);
		}
	}
	return true;
}

bool		Map::IsConfigFormated(){
	int		lenLine = m_config->size();
	bool	first = false;
	bool	second = false;

	if (lenLine == 0 || lenLine > 4)
		return false;
	for (int i = 0; i < lenLine; ++i) {
		if (second and (m_config->at(i) < 48 || m_config->at(i) > 57))
			return false;
		else if (first and m_config->at(i) != 120 and second)
			return false;
		else if (first and m_config->at(i) != 120)
			second = true;
		if (m_config->at(i) == 120)
			first = true;
		if (m_config->at(i) == 120 and !m_config->at(i + 1))
			return false;
	}
	return true;
}

bool		Map::IsLineFormated(string *line) {
	if (line->size() != m_sizeX) 
		return false;
		
	for (int i = 0; i < m_sizeX; ++i) {
		if (line->at(i) < 48 || line->at(i) > 57)
			return false;
	}
	return true;
}

bool		Map::IsHeightFormated() {
	if (m_vstr->size() != m_sizeY)
		return false;
	return true;
}

bool		Map::IsMapFormated() {
	if (!IsHeightFormated())
		return false;
	for (int i = 0; i < m_sizeY; ++i) {
		if (!IsLineFormated(&m_vstr->at(i))) {
			return false;
		}
	}
	return true;
}

void		Map::CheckMap() {
	if (!IsConfigFormated() && !IsBallNumValid()) {
		cout << m_error << endl;
		exit(1);
	}
	GetSize();
	if (!IsMapFormated())
	{
		cout << m_error << endl;
		exit(1);
	}
}

/*
---------------------------------------------------------------------------------
|						 Here is the Main Method								|
---------------------------------------------------------------------------------
*/

void Map::ParseMap(string *filePath) {

	ifstream input(*filePath);

	if (!input.is_open()) {
		
		cout << "Error loading map" << endl;
		exit(1);
	}
	string line;

	getline(input, line);
	std::cout << line << std::endl;
	if (line.empty()) {
		cout << m_error << endl;
		exit(1);
	}
	*m_ballconfig = line;
	IsBallNumFormated();
	m_ball = stoi(*m_ballconfig);

	while (getline(input, line)) {
		if (!line.empty()) {
			m_vstr->push_back(line);
		}
	}

	input.close();

	*m_config = m_vstr->at(m_vstr->size() - 1);
	m_vstr->pop_back();

	std::cout << *m_config << endl;
}

Map::~Map() {
	delete m_config;
	delete m_ballconfig;
	m_vstr->clear();
}