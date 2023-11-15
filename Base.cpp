#include <iostream>

#include "Base.h"

Base::Base() {
	b_path = NULL;
}

void Base::StartMenu() {
	while (b_startMenu)
	{
		
	}
}

void Base::GetPath(int num){
	switch (num) {
	case 1:
		*b_path = "rsrc/Level1";
		break;
	case 2:
		*b_path = "rsrc/Level2";
		break;
	case 3:
		*b_path = "rsrc/Level3";
		break;
	case 4:
		*b_path = "rsrc/Level4";
		break;
	case 5:
		*b_path = "rsrc/Level5";
		break;
	case 6:
		*b_path = "rsrc/Level6";
		break;
	}
}