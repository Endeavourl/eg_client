/* 	cistring.h -- case insensitive STL string.

	Written from this, http://www.gotw.ca/gotw/029.htm.

	Copyright (C) 2001-2003 Mark Weaver
	Written by Mark Weaver <mark@npsl.co.uk>

	Part of the mailparse library.
	This library is free software; you can redistribute it and/or
	modify it under the terms of the GNU Library General Public
	License as published by the Free Software Foundation; either
	version 2 of the License, or (at your option) any later version.

	This library is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
	Library General Public License for more details.

	You should have received a copy of the GNU Library General Public
	License along with this library; if not, write to the
	Free Software Foundation, Inc., 59 Temple Place - Suite 330,
	Boston, MA  02111-1307, USA.
*/

#ifndef cistring_h
#define cistring_h

//////////////////////////////////////////////////////////////////////
// CASE INSENSITIVE STRING
//////////////////////////////////////////////////////////////////////

#include <string>

_STD_BEGIN

struct ci_char_traits : public char_traits<char>
            // just inherit all the other functions
            // that we don't need to override
{
static bool eq( char c1, char c2 )
  { return toupper(c1) == toupper(c2); }

static bool ne( char c1, char c2 )
  { return toupper(c1) != toupper(c2); }

static bool lt( char c1, char c2 )
  { return toupper(c1) <  toupper(c2); }

static int compare( const char* s1,
                    const char* s2,
                    size_t n ) {
	return strnicmp( s1, s2, n );
         // if available on your compiler,
         // otherwise you can roll your own
}

static const char*
find( const char* s, size_t n, char a ) {
	a = toupper(a);
	for ( ; n > 0 ; --n, ++s) {
		if ( toupper(*s) == a )
			return s;
	}
	return 0;
}
};

typedef basic_string<char, ci_char_traits> ci_string;

struct ci_wchar_traits : public char_traits<wchar_t>
            // just inherit all the other functions
            //  that we don't need to override
{
static bool eq( wchar_t c1, wchar_t c2 )
  { return towupper(c1) == towupper(c2); }

static bool ne( wchar_t c1, wchar_t c2 )
  { return towupper(c1) != towupper(c2); }

static bool lt( wchar_t c1, wchar_t c2 )
  { return towupper(c1) <  towupper(c2); }

static int compare( const wchar_t* s1,
                    const wchar_t* s2,
                    size_t n ) {
  return wcsnicmp( s1, s2, n );
         // if available on your compiler,
         //  otherwise you can roll your own
}

static const wchar_t*
find( const wchar_t* s, size_t n, wchar_t a ) {
	a = towupper(a);
	for ( ; n > 0 ; --n, ++s ) {
		if ( towupper(*s) == a )
			return s;
	}
	return 0;
}
};

typedef basic_string<wchar_t, ci_wchar_traits> ci_wstring;

#ifdef _UNICODE
typedef ci_wstring ci_tstring;
#else
typedef ci_string ci_tstring;
#endif

_STD_END

#endif // cistring_h
