#include <iostream>
#include "VanillaOption.h"
#include "Option.h"


VanillaOption::VanillaOption(double _expiry, double _strike) : Option(_expiry) , _strike{_strike}
{
	if (_expiry >= 0 && _strike >= 0)
		_strike = _strike;
}

