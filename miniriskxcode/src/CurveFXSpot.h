#pragma once
#include "ICurve.h"

namespace minirisk {

struct CurveFXSpot : ICurveFXSpot
{
	virtual string name() const { return m_name; }

	CurveFXSpot(Market* mkt, const Date& today, const string& curve_name);

	// compute the discount factor

	virtual Date today() const { return m_today; }
	
	// return the FX spot price of currency ccy1 deniminated in ccy2 for delivery at time t
	// ignore the fact that the FX spot is a t+2 forward price itself, and assume it is the istantaneous exchange rate
	double spot() const;

private:
	Date   m_today;
	string m_name;
	double m_rate;
};

} // namespace minirisk
