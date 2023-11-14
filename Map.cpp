#include "Map.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

Map::Map() {
	m_sizeX = 0;
	m_sizeY = 0;
	m_error = "LOL";
}

bool		Map::IsConfigFormated(char *line){
	int		lenLine = strlen(line);
	bool	first = false;
	bool	second = true;

	if (lenLine == 0 || lenLine > 4)
		return false;
	for (int i = 0; i < lenLine; ++i) {
		if (second and (line[i] < 48 || line[i] > 57))
			return false;
		else if (first and line[i] != 120 and !second)
			return false;
		else if (line[i] < 48 || line[i] > 57)
			return false;
		if (line[i] == 120)
			first = true;
		if (first and line[i] != 120)
			second = true;
	}
}

bool		Map::IsLineFormated(char* line) {
	if (strlen(line) != m_sizeX)
		return false;
	for (int i = 0; i < m_sizeX; ++i) {
		if (line[i] > 48 || line[i] > 57)
			return false;

	}
}

void		Map::GetSize() {
	char	*x;
	char	*y;
	int		lenLine = strlen(m_config);

	x = new char[2];
	if (m_config[1] >= 48 || m_config[1] <= 57) {
		y = new char[3];
		y[0] = m_config[0];
		y[1] = m_config[1];
		y[2] = '\0';
		x[0] = m_config[3];
		x[1] = '\0';
	}
	else {
		y = new char[2];
		y[0] = m_config[0];
		y[1] = '\0';
		x[0] = m_config[2];
		x[1] = '\0';
	}
	cout << y << endl;
	cout << x << endl;
	m_sizeX = stoi(x);
	m_sizeY = stoi(y);
	delete[] x;
	delete[] y;
}

void Map::ParseMap() {
	string filepath = "rsrc/map.txt";
	ifstream input(filepath);

	if (!input.is_open()) {
		cout << "Error loading map" << endl;
		return;
	}

	vector<string> temp;
	string line;

	while (getline(input, line)) {
		if (!line.empty()) {
			temp.push_back(line);
		}
	}

	input.close();

	m_map = new char* [temp.size()];

	for (size_t i = 0; i < temp.size() - 1; ++i) {
		m_map[i] = new char[temp[i].size()];
		strcpy_s(m_map[i], temp[i].size() + 1, temp[i].c_str());
		cout << "Test" << endl;
	}
	m_config = new char[temp[temp.size() - 1].size() + 1];
	strcpy_s(m_config, temp[temp.size() - 1].size() + 1, temp[temp.size() - 1].c_str());
	for (int i = 0; i < 7; ++i)
		cout << m_map[i] << endl;
}

bool		Map::IsHeightFormated() {
	if (sizeof(*m_map) / sizeof(*m_map[0]) != m_sizeY + 1)
		return false;
}

void		Map::CheckMap() {
	if (!IsConfigFormated(m_map[m_sizeY]))
		cout << m_error << endl;
	GetSize();
	if (!IsMapFormated())
		cout << m_error << endl;
}

bool		Map::IsMapFormated() {
	if (!IsHeightFormated())
		return false;
	for (int i = 0; i < m_sizeY; ++i){
		if (!IsLineFormated(m_map[i])) {
			return false;
		}
	}
}