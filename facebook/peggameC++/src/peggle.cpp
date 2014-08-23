#include "main.h"

class Peggle {
	int _x;
	int _y;
	int _state;
	Peggle *left;
	Peggle *right;
	double _probability;

	Peggle() {
		_x = _y = _state = _probability = 0;
	}

};
