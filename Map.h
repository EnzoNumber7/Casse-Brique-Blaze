#pragma once
#include <string>

class Map
{
private:

	int				m_sizeX;
	int				m_sizeY;
	std::string		**m_map;
	const	char*	m_error;
public:
	Map();

	void			ParseMap();
	void			CheckMap();

private:

	void			GetSize();
	bool			IsLineFormated(std::string *line);
	bool			IsMapFormated();
	bool			IsConfigFormated(std::string *line);
	bool			IsHeightFormated();
};

