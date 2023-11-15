#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "Map.h"

using namespace std;

/*
---------------------------------------------------------------------------------
|						 Here is the constructor								|
---------------------------------------------------------------------------------
*/

Map::Map() {
	m_sizeX = 0;
	m_sizeY = 0;
	m_num = 0;
	m_error = \
"Map is not correctly formated. Expected format would be : \n\n\
\
0000\n \
0000\n \
0000\n \
0000\n \
WidthxHeight\n\n \
\
You can change 0 by bricks health capped at 9\n \
Width max is 13\n \
Height max is 7\n";
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
	int		lenLine = strlen(m_config);

	y = new char[2];
	if (m_config[1] >= 48 and m_config[1] <= 57) {
		x = new char[3];
		x[0] = m_config[0];
		x[1] = m_config[1];
		x[2] = '\0';
		y[0] = m_config[3];
		y[1] = '\0';
	}
	else {
		x = new char[2];
		x[0] = m_config[0];
		x[1] = '\0';
		y[0] = m_config[2];
		y[1] = '\0';
	}
	m_sizeX = stoi(x);
	m_sizeY = stoi(y);
	delete[] x;
	delete[] y;
	m_num = m_sizeX * m_sizeY;
}

/*
---------------------------------------------------------------------------------
|						 Here are the Check Methods								|
---------------------------------------------------------------------------------
*/

bool		Map::IsConfigFormated(char *line){
	int		lenLine = strlen(line);
	bool	first = false;
	bool	second = false;

	if (lenLine == 0 || lenLine > 4)
		return false;
	for (int i = 0; i < lenLine; ++i) {
		if (second and (line[i] < 48 || line[i] > 57))
			return false;
		else if (first and line[i] != 120 and second)
			return false;
		else if (first and line[i] != 120)
			second = true;
		if (line[i] == 120)
			first = true;
		if (line[i] == 120 and !line[i + 1])
			return false;
	}
	return true;
}

bool		Map::IsLineFormated(char* line) {
	if (strlen(line) != m_sizeX) 
		return false;
		
	for (int i = 0; i < m_sizeX; ++i) {
		if (line[i] < 48 || line[i] > 57)
			return false;
	}
	return true;
}

bool		Map::IsHeightFormated() {
	int	i = 0;
	//std::cout << "Expected == " << m_sizeY << std::endl;
	//std::cout << "Actual == " << sizeof(m_map) / sizeof(*m_map[0]) - 1 << std::endl;
	for (int j = 0; m_str[j]; ++j)
		i++;
	//std::cout << "I == " << i - 2 << std::endl;
	if (i - 2 != m_sizeY)
		return false;
	return true;
}

bool		Map::IsMapFormated() {
	if (!IsHeightFormated())
		return false;
	for (int i = 0; i < m_sizeY; ++i) {
		if (!IsLineFormated(m_str[i])) {
			return false;
		}
	}
	return true;
}

void		Map::CheckMap() {
	if (!IsConfigFormated(m_config)) {
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

void Map::ParseMap() {
	string filepath = "rsrc/map.txt";
	ifstream input(filepath);

	if (!input.is_open()) {
		cout << "Error loading map" << endl;
		exit(1);
	}

	vector<string> temp;
	string line;

	while (getline(input, line)) {
		if (!line.empty()) {
			temp.push_back(line);
		}
	}

	input.close();

	m_str = new char* [temp.size()];

	for (size_t i = 0; i < temp.size() - 1; ++i) {
		m_str[i] = new char[temp[i].size()];
		strcpy_s(m_str[i], temp[i].size() + 1, temp[i].c_str());
	}
	m_config = new char[temp[temp.size() - 1].size() + 1];
	strcpy_s(m_config, temp[temp.size() - 1].size() + 1, temp[temp.size() - 1].c_str());
}