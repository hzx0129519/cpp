#include "Global.h"
#include "PortfolioUtils.h"
#include "TradePayment.h"
#include "Market.h"

#include <map>
#include <numeric>

namespace minirisk {

void print_portfolio(const portfolio_t& portfolio)
{
    std::for_each(portfolio.begin(), portfolio.end(), [](auto& pt){ pt->print(std::cout); });
}

std::vector<ppricer_t> get_pricers(const portfolio_t& portfolio)
{
    std::vector<ppricer_t> pricers(portfolio.size());
    std::transform( portfolio.begin(), portfolio.end(), pricers.begin()
                  , [](auto &pt) -> ppricer_t { return pt->pricer(); } );
    return pricers;
}

portfolio_values_t compute_prices(const std::vector<ppricer_t>& pricers, Market& mkt)
{
    portfolio_values_t prices(pricers.size());
    std::transform(pricers.begin(), pricers.end(), prices.begin()
        , [&mkt](auto &pp) -> std::pair<double, string> { 
			try {
				return std::make_pair(pp->price(mkt), "");
			}
			catch (const std::exception& e){
				return std::make_pair(std::numeric_limits<double>::quiet_NaN(), e.what());
			}
		});
    return prices;
}

portfolio_total_t portfolio_total(const portfolio_values_t& values)
{
	portfolio_total_t total;
	total.first = 0.0; 
	for (size_t i = 0; i < values.size(); i++) {
		if (std::isnan(values[i].first))
			total.second.push_back(std::make_pair(i, values[i].second));
		else
			total.first += values[i].first;
	}
	return total;
}

std::vector<std::pair<string, portfolio_values_t>> compute_pv01_bucketed(const std::vector<ppricer_t>& pricers, const Market& mkt)
{
    std::vector<std::pair<string, portfolio_values_t>> pv01;  // PV01 per trade

    const double bump_size = 0.01 / 100;

    // filter risk factors related to IR
    auto base = mkt.get_risk_factors(ir_rate_prefix + "\\d+[DWMY].[A-Z]{3}");

    // Make a local copy of the Market object, because we will modify it applying bumps
    // Note that the actual market objects are shared, as they are referred to via pointers
    Market tmpmkt(mkt);

    // compute prices for perturbated markets and aggregate results
    pv01.reserve(base.size());
    for (const auto& d : base) {
		portfolio_values_t pv_up, pv_dn;
        std::vector<std::pair<string, double>> bumped(1, d);
        pv01.push_back(std::make_pair(d.first, portfolio_values_t(pricers.size())));

        // bump down and price
        bumped[0].second = d.second - bump_size;
        tmpmkt.set_risk_factors(bumped);
        pv_dn = compute_prices(pricers, tmpmkt);

        // bump up and price
        bumped[0].second = d.second + bump_size; // bump up
        tmpmkt.set_risk_factors(bumped);
        pv_up = compute_prices(pricers, tmpmkt);


        // restore original market state for next iteration
        // (more efficient than creating a new copy of the market at every iteration)
        bumped[0].second = d.second;
        tmpmkt.set_risk_factors(bumped);

        // compute estimator of the derivative via central finite differences
        double dr = 2.0 * bump_size;
        std::transform(pv_up.begin(), pv_up.end(), pv_dn.begin(), pv01.back().second.begin()
            , [dr](auto hi, auto lo) -> std::pair<double, string> {
				if (std::isnan(hi.first))
					return std::make_pair(std::numeric_limits<double>::quiet_NaN(), hi.second);
				else if (std::isnan(lo.first))
					return std::make_pair(std::numeric_limits<double>::quiet_NaN(), lo.second);
				else
					return std::make_pair((hi.first - lo.first) / dr, "");
			});
    }

    return pv01;
}


std::vector<std::pair<string, portfolio_values_t>> compute_pv01_parallel(const std::vector<ppricer_t>& pricers, const Market& mkt)
{
	std::vector<std::pair<string, portfolio_values_t>> pv01;  // PV01 per trade
	std::map<string, Market::vec_risk_factor_t> base_map;

	const double bump_size = 0.01 / 100;

	// filter risk factors related to IR
	auto base = mkt.get_risk_factors(ir_rate_prefix + "\\d+[DWMY].[A-Z]{3}");

	for (auto& b : base) {
		base_map[ir_rate_prefix + b.first.substr(b.first.length() - 3, 3)].push_back(b);
	}

	// Make a local copy of the Market object, because we will modify it applying bumps
	// Note that the actual market objects are shared, as they are referred to via pointers
	Market tmpmkt(mkt);

	// compute prices for perturbated markets and aggregate results
	pv01.reserve(base.size());
	for (const auto& bm : base_map) {
		portfolio_values_t pv_up, pv_dn;
		std::vector<std::pair<string, double>> bumped;
		pv01.push_back(std::make_pair(bm.first, portfolio_values_t(pricers.size())));
		// bump down and price
		for (int i = 0; i < bm.second.size(); i++) {
			bumped.push_back(bm.second[i]);
			bumped[i].second = bm.second[i].second - bump_size;
		}
		tmpmkt.set_risk_factors(bumped);
		pv_dn = compute_prices(pricers, tmpmkt);

		// bump up and price
		for (int i = 0; i < bm.second.size(); i++) {
			bumped[i].second = bm.second[i].second + bump_size;
		}
		tmpmkt.set_risk_factors(bumped);
		pv_up = compute_prices(pricers, tmpmkt);

		// restore original market state for next iteration
		// (more efficient than creating a new copy of the market at every iteration)
		for (int i = 0; i < bm.second.size(); i++) {
			bumped[i].second = bm.second[i].second;
		}
		tmpmkt.set_risk_factors(bumped);

		// compute estimator of the derivative via central finite differences
		double dr = 2.0 * bump_size;
		std::transform(pv_up.begin(), pv_up.end(), pv_dn.begin(), pv01.back().second.begin()
			, [dr](auto hi, auto lo) -> std::pair<double, string> {
				if (std::isnan(hi.first))
					return std::make_pair(std::numeric_limits<double>::quiet_NaN(), hi.second);
				else if (std::isnan(lo.first))
					return std::make_pair(std::numeric_limits<double>::quiet_NaN(), lo.second);
				else
					return std::make_pair((hi.first - lo.first) / dr, "");
			});
	}

	return pv01;
}



ptrade_t load_trade(my_ifstream& is)
{
    string name;
    ptrade_t p;

    // read trade identifier
    guid_t id;
    is >> id;

    if (id == TradePayment::m_id)
        p.reset(new TradePayment);
    else
        THROW("Unknown trade type:" << id);

    p->load(is);

    return p;
}

void save_portfolio(const string& filename, const std::vector<ptrade_t>& portfolio)
{
    // test saving to file
    my_ofstream of(filename);
    for( const auto& pt : portfolio) {
        pt->save(of);
        of.endl();
    }
    of.close();
}

std::vector<ptrade_t> load_portfolio(const string& filename)
{
    std::vector<ptrade_t> portfolio;

    // test reloading the portfolio
    my_ifstream is(filename);
    while (is.read_line())
        portfolio.push_back(load_trade(is));

    return portfolio;
}

void print_price_vector(const string& name, const portfolio_values_t& values)
{
    std::cout
        << "========================\n"
        << name << ":\n"
        << "========================\n"
        << "Total: " << portfolio_total(values).first
        << "\n========================\n";

	for (size_t i = 0, n = values.size(); i < n; ++i) {
		if (std::isnan(values[i].first))
			std::cout << std::setw(5) << i << ": " << values[i].second << "\n";
		else
			std::cout << std::setw(5) << i << ": " << values[i].first << "\n";
	}
        

    std::cout << "========================\n\n";
}

} // namespace minirisk
