#pragma once
#include <string>

class Map
{
private:

	int				m_sizeX;
	int				m_sizeY;
	int				m_num;
	const	char*	m_error;
public:

	char			**m_map;
	char			*m_config;
	Map();

	void			ParseMap();
	void			CheckMap();
	int				GetWidth();
	int				GetHeight();

private:

	void			GetSize();
	bool			IsLineFormated(char *line);
	bool			IsMapFormated();
	bool			IsConfigFormated(char *line);
	bool			IsHeightFormated();
};

