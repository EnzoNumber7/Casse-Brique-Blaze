#pragma once
#include <string>
#include <vector>

class Map
{
private:

	// Main Attributes

	int				m_sizeX;
	int				m_sizeY;
	int				m_num;
	const	char*	m_error;

public:

	std::vector<std::string>	*m_vstr;
	std::string						*m_config;

	Map();

private:

	// Check Methods

	bool			IsConfigFormated(std::string *line);
	bool			IsLineFormated(std::string *line);
	bool			IsHeightFormated();
	bool			IsMapFormated();

	void			GetSize();

public:
	
	// Main Methods

	void			ParseMap(std::string* filePath);
	void			CheckMap();

	// Get Methods

	int				GetWidth();
	int				GetHeight();
};

