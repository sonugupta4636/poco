//
// NumberParser.h
//
// $Id: //poco/1.4/Foundation/include/Poco/NumberParser.h#1 $
//
// Library: Foundation
// Package: Core
// Module:  NumberParser
//
// Definition of the NumberParser class.
//
// Copyright (c) 2004-2006, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// Permission is hereby granted, free of charge, to any person or organization
// obtaining a copy of the software and accompanying documentation covered by
// this license (the "Software") to use, reproduce, display, distribute,
// execute, and transmit the Software, and to prepare derivative works of the
// Software, and to permit third-parties to whom the Software is furnished to
// do so, all subject to the following:
// 
// The copyright notices in the Software and this entire statement, including
// the above license grant, this restriction and the following disclaimer,
// must be included in all copies of the Software, in whole or in part, and
// all derivative works of the Software, unless such copies or derivative
// works are solely in the form of machine-executable object code generated by
// a source language processor.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
// SHALL THE COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE
// FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE,
// ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
// DEALINGS IN THE SOFTWARE.
//


#ifndef Foundation_NumberParser_INCLUDED
#define Foundation_NumberParser_INCLUDED


#include "Poco/Foundation.h"
#include <string>
#undef min
#undef max
#include <limits>


namespace Poco {


class Foundation_API NumberParser
	/// The NumberParser class provides static methods
	/// for parsing numbers out of strings.
{
public:
	static int parse(const std::string& s);
		/// Parses an integer value in decimal notation from the given string.
		/// Throws a SyntaxException if the string does not hold a number in decimal notation.
	
	static bool tryParse(const std::string& s, int& value);
		/// Parses an integer value in decimal notation from the given string.
		/// Returns true if a valid integer has been found, false otherwise. 
	
	static unsigned parseUnsigned(const std::string& s);
		/// Parses an unsigned integer value in decimal notation from the given string.
		/// Throws a SyntaxException if the string does not hold a number in decimal notation.

	static bool tryParseUnsigned(const std::string& s, unsigned& value);
		/// Parses an unsigned integer value in decimal notation from the given string.
		/// Returns true if a valid integer has been found, false otherwise. 

	static unsigned parseHex(const std::string& s);
		/// Parses an integer value in hexadecimal notation from the given string.
		/// Throws a SyntaxException if the string does not hold a number in
		/// hexadecimal notation.

	static bool tryParseHex(const std::string& s, unsigned& value);
		/// Parses an unsigned integer value in hexadecimal notation from the given string.
		/// Returns true if a valid integer has been found, false otherwise. 

	static unsigned parseOct(const std::string& s);
		/// Parses an integer value in octal notation from the given string.
		/// Throws a SyntaxException if the string does not hold a number in
		/// hexadecimal notation.

	static bool tryParseOct(const std::string& s, unsigned& value);
		/// Parses an unsigned integer value in octal notation from the given string.
		/// Returns true if a valid integer has been found, false otherwise. 

#if defined(POCO_HAVE_INT64)

	static Int64 parse64(const std::string& s);
		/// Parses a 64-bit integer value in decimal notation from the given string.
		/// Throws a SyntaxException if the string does not hold a number in decimal notation.

	static bool tryParse64(const std::string& s, Int64& value);
		/// Parses a 64-bit integer value in decimal notation from the given string.
		/// Returns true if a valid integer has been found, false otherwise. 

	static UInt64 parseUnsigned64(const std::string& s);
		/// Parses an unsigned 64-bit integer value in decimal notation from the given string.
		/// Throws a SyntaxException if the string does not hold a number in decimal notation.

	static bool tryParseUnsigned64(const std::string& s, UInt64& value);
		/// Parses an unsigned 64-bit integer value in decimal notation from the given string.
		/// Returns true if a valid integer has been found, false otherwise. 

	static UInt64 parseHex64(const std::string& s);
		/// Parses a 64 bit-integer value in hexadecimal notation from the given string.
		/// Throws a SyntaxException if the string does not hold a number in hexadecimal notation.

	static bool tryParseHex64(const std::string& s, UInt64& value);
		/// Parses an unsigned 64-bit integer value in hexadecimal notation from the given string.
		/// Returns true if a valid integer has been found, false otherwise. 

	static UInt64 parseOct64(const std::string& s);
		/// Parses a 64 bit-integer value in octal notation from the given string.
		/// Throws a SyntaxException if the string does not hold a number in hexadecimal notation.

	static bool tryParseOct64(const std::string& s, UInt64& value);
		/// Parses an unsigned 64-bit integer value in octal notation from the given string.
		/// Returns true if a valid integer has been found, false otherwise. 

#endif // defined(POCO_HAVE_INT64)

	static double parseFloat(const std::string& s);
		/// Parses a double value in decimal floating point notation
		/// from the given string. 
		/// Throws a SyntaxException if the string does not hold a floating-point 
		/// number in decimal notation.
		
	static bool tryParseFloat(const std::string& s, double& value);
		/// Parses a double value in decimal floating point notation
		/// from the given string.
		/// Returns true if a valid floating point number has been found,
		/// false otherwise.

	static bool parseBool(const std::string& s);
		/// Parses a bool value in decimal or string notation
		/// from the given string.
		/// Valid forms are: "0", "1", "true", "on", false", "yes", "no", "off".
		/// String forms are NOT case sensitive.
		/// Throws a SyntaxException if the string does not hold a valid bool number

	static bool tryParseBool(const std::string& s, bool& value);
		/// Parses a bool value in decimal or string notation
		/// from the given string.
		/// Valid forms are: "0", "1", "true", "on", false", "yes", "no", "off".
		/// String forms are NOT case sensitive.
		/// Returns true if a valid bool number has been found,
		/// false otherwise.

private:

	template <typename T>
	static bool strToIntOct(const std::string &s, T& result) 
	{
		if (s.empty()) return false;
		if (std::numeric_limits<T>::is_signed) return false;
		std::string::const_iterator it = s.begin();
		std::string::const_iterator end = s.end();
		while (it != end && std::isspace(*it)) ++it;
		if (it == end) return false;
		while (it != end && *it == '0') ++it;
		if (it == end)
		{
			result = 0;
			return true;
		}

		unsigned base = 010;
		T n = 0;
		for (; it != end; ++it)
		{
			if (*it >= '0' && *it <= '7')
			{
				if (n > (std::numeric_limits<T>::max() / base))
					return false;
				n = n * base + *it - '0';
			}
			else break;
		}
		
		while (it != end && std::isspace(*it)) ++it;
		if (it != end) return false;

		result = n;
		return true;
	}

	template <typename T>
	static bool strToIntDec(const std::string &s, T& result) 
	{
		if (s.empty()) return false;
		int sign = 1;
		std::string::const_iterator it = s.begin();
		std::string::const_iterator end = s.end();
		while (it != end && std::isspace(*it)) ++it;
		if (it == end) return false;
		if (std::numeric_limits<T>::is_signed)
		{
			if (*it == '-') 
			{ 
				sign = -1; 
				++it; 
			}
			else if (*it == '+') ++it;
			if (it == end) return false;
		}

		unsigned base = 10;
		T n = 0;
		for (; it != end; ++it)
		{
			if (*it >= '0' && *it <= '9')
			{
				if (n > (std::numeric_limits<T>::max() / base))
					return false;
				n = n * base + *it - '0';
			}
			else break;
		}
		
		while (it != end && std::isspace(*it)) ++it;
		if (it != end) return false;

		result = sign * n;
		return true;
	}

	template <typename T>
	static bool strToIntHex(const std::string &s, T& result) 
	{
		if (s.empty()) return false;
		if (std::numeric_limits<T>::is_signed) return false;
		std::string::const_iterator it = s.begin();
		std::string::const_iterator end = s.end();
		while (it != end && std::isspace(*it)) ++it;
		if (it == end) return false;
		
		bool beginWith0x = false;
		if (*it == '0') 
		{
			beginWith0x = true;
			while (it != end && *it == '0')
			{
				++it;
				beginWith0x = false;
			}
			if (it == end) 
			{
				result = 0;
				return true;
			}
		}
		if (beginWith0x && (*it != 'x') && (*it != 'X')) return false;
		else if ((*it == 'x') || (*it == 'X')) ++it;
		if (it == end) return false;

		unsigned base = 0x10;
		T n = 0;
		for (; it != end; ++it)
		{
			if ((*it >= '0' && *it <= '9') || (*it >= 'A' && *it <= 'F') || (*it >= 'a' && *it <= 'f'))
			{
				if (n > (std::numeric_limits<T>::max() / base))
					return false;
				
				if (*it >= '0' && *it <= '9')
					n = n * base + *it - '0';
				else if (*it >= 'A' && *it <= 'F')
					n = n * base + *it - 'A' + 10;
				else if (*it >= 'a' && *it <= 'f')
					n = n * base + *it - 'a' + 10;
			}
			else break;
		}
		if (it != end)
		{
			while (std::isspace(*it)) ++it;
			if (it != end) return false;
		}

		result = n;
		return true;
	}
};


} // namespace Poco


#endif // Foundation_NumberParser_INCLUDED
