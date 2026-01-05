/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScalarConverter.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jpaulis <Jpaulis@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 14:11:06 by Jpaulis           #+#    #+#             */
/*   Updated: 2026/01/05 16:28:42 by Jpaulis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "ScalarConverter.hpp"

ScalarConverter::ScalarConverter() {}
ScalarConverter::ScalarConverter(const ScalarConverter& other) { (void)other; }
ScalarConverter::~ScalarConverter() {}
ScalarConverter& ScalarConverter::operator=(const ScalarConverter& other) {
	(void)other;
	return *this;
}

bool ScalarConverter::isPseudoLiteral(const std::string& literal) {
	return (literal == "nan" || literal == "nanf" ||
			literal == "+inf" || literal == "-inf" ||
			literal == "+inff" || literal == "-inff");
}

bool ScalarConverter::isChar(const std::string& literal) {
	return (literal.length() == 1 && 
			std::isprint(literal[0]) && 
			!std::isdigit(literal[0]));
}

bool ScalarConverter::isValidNumber(const std::string& literal) {
	if (literal.empty()) return false;
	
	size_t i = 0;
	if (literal[i] == '+' || literal[i] == '-')
		i++;
	
	bool hasDigit = false;
	bool hasDot = false;
	
	while (i < literal.length()) {
		if (literal[i] == '.') {
			if (hasDot) return false;
			hasDot = true;
		}
		else if (std::isdigit(literal[i]))
			hasDigit = true;
		else if (literal[i] == 'f' && i == literal.length() - 1)
			break;
		else
			return false;
		i++;
	}
	return hasDigit;
}

double ScalarConverter::parseValue(const std::string& literal) {
	if (isChar(literal))
		return static_cast<double>(literal[0]);
	
	if (!isValidNumber(literal))
		throw std::invalid_argument("Invalid format");
	
	std::string str = literal;
	if (!str.empty() && str[str.length() - 1] == 'f')
		str = str.substr(0, str.length() - 1);
	
	char* end = NULL;
	errno = 0;
	double result = strtod(str.c_str(), &end);
	
	if (errno == ERANGE || *end != '\0')
		throw std::invalid_argument("Invalid number");
	
	return result;
}

void ScalarConverter::printChar(double value) {
	std::cout << "char: ";
	
	if (std::isnan(value) || std::isinf(value) || 
		value != static_cast<int>(value))
		throw std::invalid_argument("impossible");
	
	int intValue = static_cast<int>(value);
	if (intValue < -128 || intValue > 127)
		throw std::invalid_argument("impossible");
	
	char c = static_cast<char>(intValue);
	if (c < 32 || c == 127)
		throw std::invalid_argument("Non displayable");
	
	std::cout << "'" << c << "'" << std::endl;
}

void ScalarConverter::printInt(double value) {
	std::cout << "int: ";
	
	if (std::isnan(value) || std::isinf(value) || 
		value < INT_MIN || value > INT_MAX)
		throw std::invalid_argument("impossible");
	
	std::cout << static_cast<int>(value) << std::endl;
}

void ScalarConverter::printFloat(double value) {
	std::cout << "float: ";
	
	if (std::isnan(value)) {
		std::cout << "nanf" << std::endl;
		return;
	}
	if (std::isinf(value)) {
		std::cout << (value > 0 ? "+inff" : "-inff") << std::endl;
		return;
	}
	
	std::cout << std::fixed << std::setprecision(1) 
			<< static_cast<float>(value) << "f" << std::endl;
}

void ScalarConverter::printDouble(double value) {
	std::cout << "double: ";
	
	if (std::isnan(value)) {
		std::cout << "nan" << std::endl;
		return;
	}
	if (std::isinf(value)) {
		std::cout << (value > 0 ? "+inf" : "-inf") << std::endl;
		return;
	}
	
	std::cout << std::fixed << std::setprecision(1) 
			<< value << std::endl;
}

void ScalarConverter::handlePseudoLiteral(const std::string& literal) {
	std::cout << "char: impossible" << std::endl;
	std::cout << "int: impossible" << std::endl;
	
	bool isNan = (literal == "nan" || literal == "nanf");
	bool isPosInf = (literal == "+inf" || literal == "+inff");
	
	std::cout << "float: ";
	if (isNan) std::cout << "nanf";
	else std::cout << (isPosInf ? "+inff" : "-inff");
	std::cout << std::endl;
	
	std::cout << "double: ";
	if (isNan) std::cout << "nan";
	else std::cout << (isPosInf ? "+inf" : "-inf");
	std::cout << std::endl;
}

void ScalarConverter::convert(const std::string& literal) {
	if (isPseudoLiteral(literal)) {
		handlePseudoLiteral(literal);
		return;
	}
	
	double value;
	try {
		value = parseValue(literal);
	} catch (const std::exception&) {
		std::cout << "char: impossible" << std::endl;
		std::cout << "int: impossible" << std::endl;
		std::cout << "float: impossible" << std::endl;
		std::cout << "double: impossible" << std::endl;
		return;
	}
	
	try { printChar(value); } 
	catch (const std::exception& e) { std::cout << e.what() << std::endl; }
	
	try { printInt(value); } 
	catch (const std::exception& e) { std::cout << e.what() << std::endl; }
	
	printFloat(value);
	printDouble(value);
}
