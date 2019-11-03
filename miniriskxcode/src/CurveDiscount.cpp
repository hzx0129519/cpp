#include "CurveDiscount.h"
#include "Market.h"
#include "Streamer.h"

#include <cmath>


namespace minirisk {

CurveDiscount::CurveDiscount(Market *mkt, const Date& today, const string& curve_name)
    : m_today(today)
    , m_name(curve_name)
    , m_rates(mkt->get_yield(curve_name.substr(ir_curve_discount_prefix.length(),3)))
{
}

double  CurveDiscount::df(const Date& t) const
{
    MYASSERT((!(t < m_today)), "cannot get discount factor for date in the past: " << t);
    MYASSERT((!(t - m_today > m_rates.rbegin()->first)), "cannot get discount rate beyond last tenor: " << t);
    auto r = m_rates.upper_bound(t - m_today);
    double T1 = static_cast<double>(r->first)/365.0;
    double r1 = r->second;
    double T0 = static_cast<double>((--r)->first)/365.0;
    double r0 = r->second;
    double dt = time_frac(m_today, t);
    return std::exp(-r0 * T0 - (r1 * T1 - r0 * T0) / (T1 - T0) * (dt - T0));
}
} // namespace minirisk
