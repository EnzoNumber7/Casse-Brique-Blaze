#pragma once
#include <string>

class Map
{
private:

	// Main Attributes

	int				m_sizeX;
	int				m_sizeY;
	int				m_num;
	const	char*	m_error;

public:

	char			**m_str;
	char			*m_config;

	Map();

private:

	// Check Methods

	bool			IsConfigFormated(char* line);
	bool			IsLineFormated(char *line);
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

