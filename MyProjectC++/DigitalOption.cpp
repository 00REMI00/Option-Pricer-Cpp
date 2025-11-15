#include "DigitalOption.h"
#include "Option.h"


DigitalOption::DigitalOption(double _expiry, double _strike) : Option(_expiry), _strike{ _strike }
{
	if (_expiry >= 0 && _strike >= 0)
		_strike = _strike;
}

