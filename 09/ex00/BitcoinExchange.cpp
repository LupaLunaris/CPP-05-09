#include "BitcoinExchange.hpp"

#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <stdexcept>

BitcoinExchange::BitcoinExchange() {}

BitcoinExchange::BitcoinExchange(const BitcoinExchange& other) {
	*this = other;
}

BitcoinExchange& BitcoinExchange::operator=(const BitcoinExchange& other) {
	if (this != &other) {
		this->exchangeRates = other.exchangeRates;
	}
	return *this;
}

BitcoinExchange::~BitcoinExchange() {}

static std::string trim(const std::string& s)
{
	size_t start = 0;
	while (start < s.size() && (s[start] == ' ' || s[start] == '\t'))
		++start;
	size_t end = s.size();
	while (end > start && (s[end - 1] == ' ' || s[end - 1] == '\t'))
		--end;
	return s.substr(start, end - start);
}

bool isValidDateFormat(const std::string& date)
{
	if (date.size() != 10) return false;
	if (date[4] != '-' || date[7] != '-') return false;

	for (size_t i = 0; i < date.size(); ++i)
	{
		if (i == 4 || i == 7) continue;
		if (!std::isdigit(date[i])) return false;
	}

	int month = std::atoi(date.substr(5, 2).c_str());
	int day   = std::atoi(date.substr(8, 2).c_str());

	if (month < 1 || month > 12) return false;
	if (day < 1 || day > 31) return false;

	return true;
}

static bool parseDoubleStrict(const std::string& s, double& out)
{
	char* end = 0;
	out = std::strtod(s.c_str(), &end);
	if (end == s.c_str()) return false;
	if (*end != '\0') return false;
	return true;
}

void BitcoinExchange::loadData(const std::string& filename)
{
	std::ifstream file(filename.c_str());
	if (!file.is_open())
		throw std::runtime_error("Error: could not open file.");
	std::string line;
	if (!std::getline(file, line))
		return;
	if (trim(line) != "date,exchange_rate")
	{
		file.clear();
		file.seekg(0);
	}
	while (std::getline(file, line))
	{
		if (line.empty())
			continue;
		size_t comma = line.find(',');
		if (comma == std::string::npos)
			continue;
		std::string date = trim(line.substr(0, comma));
		std::string rateStr = trim(line.substr(comma + 1));
		if (!isValidDateFormat(date))
			continue;
		double rate = 0.0;
		if (!parseDoubleStrict(rateStr, rate))
			continue;
		exchangeRates[date] = rate;
	}
}

static bool splitOnce(const std::string& line, char delim, std::string& left, std::string& right)
{
	size_t pos = line.find(delim);
	if (pos == std::string::npos)
		return false;
	left = line.substr(0, pos);
	right = line.substr(pos + 1);
	return true;
}

void BitcoinExchange::processInput(const std::string& filename) const
{
	std::ifstream file(filename.c_str());
	if (!file.is_open())
	{
		std::cout << "Error: could not open file." << std::endl;
		return;
	}

	std::string line;
	bool firstLine = true;

	while (std::getline(file, line))
	{
		if (line.empty())
			continue;
		if (firstLine)
		{
			firstLine = false;
			if (trim(line) == "date | value")
				continue;
		}
		std::string left, right;
		if (!splitOnce(line, '|', left, right))
		{
			std::cout << "Error: bad input => " << line << std::endl;
			continue;
		}
		std::string date = trim(left);
		std::string valueStr = trim(right);
		if (!isValidDateFormat(date))
		{
			std::cout << "Error: bad input => " << date << std::endl;
			continue;
		}
		double value = 0.0;
		if (!parseDoubleStrict(valueStr, value))
		{
			std::cout << "Error: bad input => " << line << std::endl;
			continue;
		}
		if (value < 0.0)
		{
			std::cout << "Error: not a positive number." << std::endl;
			continue;
		}
		if (value > 1000.0)
		{
			std::cout << "Error: too large a number." << std::endl;
			continue;
		}
		std::map<std::string, double>::const_iterator it = exchangeRates.upper_bound(date);
		if (it == exchangeRates.begin())
		{
			std::cout << "Error: bad input => " << date << std::endl;
			continue;
		}
		--it;
		double result = value * it->second;
		std::cout << date << " => " << value << " = " << result << std::endl;
	}
}
