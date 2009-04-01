//
// TextIterator.cpp
//
// $Id: //poco/1.3/Foundation/src/TextIterator.cpp#1 $
//
// Library: Foundation
// Package: Text
// Module:  TextIterator
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


#include "Poco/TextIterator.h"
#include "Poco/TextEncoding.h"
#include <algorithm>


namespace Poco {


TextIterator::TextIterator():
	_pEncoding(0)
{
}


TextIterator::TextIterator(const std::string& str, const TextEncoding& encoding):
	_pEncoding(&encoding),
	_it(str.begin()),
	_end(str.end())
{
}

TextIterator::TextIterator(const std::string::const_iterator& begin, const std::string::const_iterator& end, const TextEncoding& encoding):
	_pEncoding(&encoding),
	_it(begin),
	_end(end)
{
}


TextIterator::TextIterator(const std::string& str):
	_pEncoding(0),
	_it(str.end()),
	_end(str.end())
{
}


TextIterator::TextIterator(const std::string::const_iterator& end):
	_pEncoding(0),
	_it(end),
	_end(end)
{
}


TextIterator::~TextIterator()
{
}


TextIterator::TextIterator(const TextIterator& it):
	_pEncoding(it._pEncoding),
	_it(it._it),
	_end(it._end)
{
}


TextIterator& TextIterator::operator = (const TextIterator& it)
{
	if (&it != this)
	{
		_pEncoding = it._pEncoding;
		_it        = it._it;
		_end       = it._end;
	}
	return *this;
}


void TextIterator::swap(TextIterator& it)
{
	std::swap(_pEncoding, it._pEncoding);
	std::swap(_it, it._it);
	std::swap(_end, it._end);
}


int TextIterator::operator * () const
{
	poco_check_ptr (_pEncoding);
	poco_assert (_it != _end);
	
	unsigned char c = (unsigned char) *_it;
	int n = _pEncoding->characterMap()[c];
	if (n >= -1) return n;
	else
	{
		poco_assert_dbg (n >= -TextEncoding::MAX_SEQUENCE_LENGTH);
		unsigned char buffer[TextEncoding::MAX_SEQUENCE_LENGTH];
		unsigned char* p = buffer;
		std::string::const_iterator it = _it;
		while (n < 0 && it != _end) { *p++ = *it++; ++n; }
		if (n == 0)
			return _pEncoding->convert(buffer);
		else
			return -1;
	}
}

	
TextIterator& TextIterator::operator ++ ()
{
	poco_check_ptr (_pEncoding);
	poco_assert (_it != _end);
	
	unsigned char c = (unsigned char) *_it;
	int n = _pEncoding->characterMap()[c];
	if (n >= -1)
		++_it;
	else
		while (n < 0 && _it != _end) { ++_it; ++n; }

	return *this;
}


TextIterator TextIterator::operator ++ (int)
{
	TextIterator prev(*this);
	operator ++ ();
	return prev;
}


} // namespace Poco
