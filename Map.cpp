#include "Map.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

Map::Map() {
	m_sizeX = 0;
	m_sizeY = 0;
}

bool		Map::IsConfigFormated(string *line){
	int		lenLine = line->length();
	bool	first = false;
	bool	second = true;

	if (lenLine == 0 || lenLine > 4)
		return false;
	for (int i = 0; i < lenLine; ++i) {
		if (second and (line->at(i) < 48 || line->at(i) > 57))
			return false;
		else if (first and line->at(i) != 120 and !second)
			return false;
		else if (line->at(i) < 48 || line->at(i) > 57)
			return false;
		if (line->at(i) == 120)
			first = true;
		if (first and line->at(i) != 120)
			second = true;
	}
}

bool		Map::IsLineFormated(string* line) {
	if (line->length() != m_sizeX)
		return false;
	for (int i = 0; i < m_sizeX; ++i) {
		if (line[i].at(i) > 48 || line->at(i) > 57)
			return false;

	}
}

void		Map::GetSize() {
	string	line = *m_map[m_sizeY];
	string	x;
	string	y;
	int		lenLine = line.length();

	if (line[1] >= 48 || line[1] <= 57)
		y = line.substr(3, 1);
	else
		y = line.substr(2, 1);
	y = line;
	x.pop_back();
	x.pop_back();
	m_sizeX = stoi(x);
	m_sizeY = stoi(y);
}

void		Map::ParseMap() {
	string		filepath = "rsrc/map.txt";
	ifstream	input;
	int			numEndl = 0;
	int			currentChar;
	int			i = 0;

	input.open(filepath);
	if (!input.is_open()) {
		cout << "Error loading map" << endl;
	}
	while (1){
		if (input.peek() == -1)
			break;
		currentChar = input.get();
		if (currentChar == '\n')
			numEndl++;
	}
	while (input) {
		string	line;
		int		lenLine;

		getline(input, line, '\n');
		line.pop_back();
		lenLine = line.length();
		if (lenLine == 0)
			cout << "Error Parsing" << endl;
		m_map[i] = &line;
		i++;
	}
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