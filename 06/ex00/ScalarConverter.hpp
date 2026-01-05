/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScalarConverter.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jpaulis <Jpaulis@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 14:11:07 by Jpaulis           #+#    #+#             */
/*   Updated: 2026/01/05 14:42:04 by Jpaulis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCALARCONVERTER_HPP
#define SCALARCONVERTER_HPP

#include <iostream>
#include <string>
#include <cmath>
#include <iomanip>
#include <cstdlib>
#include <cerrno>
#include <cctype>
#include <climits>

class ScalarConverter {
	private:
		ScalarConverter();
		ScalarConverter(const ScalarConverter& other);
		ScalarConverter& operator=(const ScalarConverter& other);
		~ScalarConverter();

		static bool isPseudoLiteral(const std::string& literal);
		static bool isChar(const std::string& literal);
		static bool isValidNumber(const std::string& literal);
		static double parseValue(const std::string& literal);
		
		static void printChar(double value);
		static void printInt(double value);
		static void printFloat(double value);
		static void printDouble(double value);
		static void handlePseudoLiteral(const std::string& literal);

	public:
		static void convert(const std::string& literal);
};

#endif
