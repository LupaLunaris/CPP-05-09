#ifndef BITCOINEXCHANGE_HPP
# define BITCOINEXCHANGE_HPP

# include <map>
# include <string>

class BitcoinExchange {
	private:
		std::map<std::string, double> exchangeRates;

	public :
		BitcoinExchange();
		BitcoinExchange(const BitcoinExchange& other);
		BitcoinExchange& operator=(const BitcoinExchange& other);
		~BitcoinExchange();

		void loadData(const std::string& filename);
		void processInput(const std::string& filename) const;
};

#endif
