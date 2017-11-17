#ifndef SDPTYPES_H
#define SDPTYPES_H

// SDPTypes Library
// Copyright © 1995-2004, Timothy M. Shead
//
// Contact: tshead@k-3d.com
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public
// License as published by the Free Software Foundation; either
// version 2 of the License, or (at your option) any later version.
//
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// General Public License for more details.
//
// You should have received a copy of the GNU General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

/** \file
		\brief Public API for the entire SDPTypes library
		\author Tim Shead (tshead@k-3d.com)
*/

/////////////////////////////////////////////////////////////////////////////
// First stage - identify compiler & platform

/////////////////////////////////////////////////////////////////////////////
// Compiler vendors

#if defined _MSC_VER		// Microsoft compiler
/// Compiler is Microsoft Visual C++
#define SDPMICROSOFT
#elif defined __BCPLUSPLUS__	// Borland compiler
/// Compiler is Borland
#define SDPBORLAND
#elif defined __MINGW32__	// GNU C MinGW 32 compiler
// Compiler GNU C MinGW 32
#define SDPMINGW32
#else				// Unknown compiler
#endif

/////////////////////////////////////////////////////////////////////////////
// Operating systems

#if defined WIN32
/// target platform is Win32
#define SDPWIN32
#else // SDPWIN32
/// Target platform is Unix
#define SDPUNIX
#endif // !SDPWIN32

#ifdef SDPWIN32
#include <windows.h>
#else // SDPWIN32
#include <dirent.h>
#include <unistd.h>
#endif // !SDPWIN32

/////////////////////////////////////////////////////////////////////////////
// Second Stage - now we can get down to the good stuff!

extern "C"
{
#include <glib.h>
}

#include <sstream>
#include <string>
#include <vector>

#include <math.h>

/// A pointer to a string
typedef gchar* SDPSTRING;

/// Pointer to a constant string
typedef const gchar* const SDPCSTRING;

/// Asserts on null or empty strings
#ifndef g_assert_string
#define g_assert_string(String) g_assert(String); g_assert(strlen(String));
#endif // !g_assert_string

/// Fails on null and empty strings
#ifndef g_return_if_string_fail
#define g_return_if_string_fail(String) g_return_if_fail(String); g_return_if_fail(strlen(String));
#endif // !g_return_if_string_fail

/// Fails on null and empty strings
#ifndef g_return_val_if_string_fail
#define g_return_val_if_string_fail(String, Result) g_return_val_if_fail(String, Result); g_return_val_if_fail(strlen(String), Result);
#endif // !g_return_val_if_string_fail

// Stop the unicode madness!
#if defined (_UNICODE) || defined (UNICODE)
	#error "sdpString does not support UNICODE builds!"
#endif

/// The sdpString base class
typedef std::string sdpStringBase;

/////////////////////////////////////////////////////////////////////////////
// sdpString

/// An extended string class, derived from std::string
class sdpString :
	public sdpStringBase
{
public:
	// Constructors ...
	sdpString() :
		sdpStringBase()
	{
	}

	sdpString(SDPCSTRING String) :
		sdpStringBase(String ? String : "")
	{
	}

	sdpString(SDPCSTRING String, gulong Length) :
		sdpStringBase(String, Length)
	{
	}

	sdpString(const sdpString& String) :
		sdpStringBase(String)
	{
	}

	sdpString(const sdpStringBase& String) :
		sdpStringBase(String)
	{
	}

	sdpString(size_type Size, value_type Character) :
		sdpStringBase(Size, Character)
	{
	}

	sdpString(const_iterator First, const_iterator Last) :
		sdpStringBase(First, Last)
	{
	}

	// Assignment operators ...
	sdpString& sdpString::operator=(const sdpString& String)
	{
		erase();
		assign(String.c_str());
		return *this;
	};

	sdpString& sdpString::operator=(const sdpStringBase& String)
	{
		erase();
		assign(String.c_str());
		return *this;
	};

	sdpString& sdpString::operator=(SDPCSTRING String)
	{
		erase();
		if(String != 0)
			assign(String);
		return *this;
	};

	sdpString& sdpString::operator=(gchar Character)
	{
		erase();
		assign(1, Character);

		return *this;
	};

	// comparison (equality)
	bool sdpString::operator==(const sdpString& String) const
	{
		return compare(String.c_str()) == 0;
	}

	bool sdpString::operator==(const sdpStringBase& String) const
	{
		return compare(String.data()) == 0;
	}

	bool sdpString::operator==(SDPCSTRING String) const
	{
		return compare(String) == 0;
	}

	bool sdpString::operator==(gchar* String) const
	{
		return compare(String) == 0;
	}

	bool sdpString::operator==(gchar Character) const
	{
		return operator==(sdpStringBase(1, Character));
	}

	// comparison operators
	bool sdpString::operator!=(const sdpString& String) const
	{
		return compare(String.c_str()) != 0;
	}

	bool sdpString::operator!=(const sdpStringBase& String) const
	{
		return compare(String.data()) != 0;
	}

	bool sdpString::operator!=(SDPCSTRING String) const
	{
		return compare(String) != 0;
	}

	bool sdpString::operator!=(gchar* String) const
	{
		return compare(String) != 0;
	}

	bool sdpString::operator!=(gchar Character) const
	{
		return operator!=(sdpStringBase(1, Character));
	}

	bool operator < (const sdpString& String) const
	{
		return compare(String) < 0;
	}

	bool operator < (SDPCSTRING String) const
	{
		return compare(String) < 0;
	}

	// sdpString concatenation.
	const sdpString& sdpString::operator+=(const sdpString& String)
	{
		append(String);
		return *this;
	}

	const sdpString& sdpString::operator+=(const sdpStringBase& String)
	{
		append(String);
		return *this;
	}

	const sdpString& sdpString::operator+=(SDPCSTRING String)
	{
		if(String != 0)
			append(String);

		return *this;
	}

	const sdpString& sdpString::operator+=(gchar Character)
	{
		append(1, Character);
		return *this;
	}

	// sdpString addition functions
	friend sdpString operator+(const sdpString& String1, const sdpString& String2)
	{
		sdpString result(String1);
		return result.append(String2);
	}

	friend sdpString operator+(const sdpString& String, gchar Character)
	{
		sdpString result(String);
		return result.append(1, Character);
	}

	friend sdpString operator+(gchar Character, const sdpString& String)
	{
		sdpString result(1, Character);
		return result.append(String);
	}

	friend sdpString operator+(const sdpString& String1, SDPCSTRING String2)
	{
		sdpString result(String1);
		return result.append(String2);
	}

	friend sdpString operator+(SDPCSTRING String1, const sdpString& String2)
	{
		sdpString result(String1);
		return result.append(String2);
	}

	/// Returns the leftmost N characters of the string
	sdpString left(size_type Count) const;
	/// Returns a substring with the given starting index and size
	sdpString mid(size_type Start, size_type Count) const;
	/// Returns the rightmost N characters of the string
	sdpString right(size_type Count) const;

	/// Trims whitespace from both ends of the string
	sdpString& trim();
	/// Trims beginning whitespace from the string
	sdpString& trimleft();
	/// Trims trailing whitespace from the string
	sdpString& trimright();

	/// Casts to a C style string ...
	inline operator const gchar*() const { return c_str(); }

	/// Substitutes text into printf() style format specifiers
	void formattedreplace(const char Delimiter, SDPCSTRING Specifier, SDPCSTRING Replacement);

	/// Replaces every instance of Target with Replacement
	void replaceall(SDPCSTRING Target, SDPCSTRING Replacement);
	/// Replaces every instance of Target with Replacement
	void replaceall(const char Target, const char Replacement);

	// Test the string contents ...
	const bool isalphanumeric() const;
	const bool isalphabetic() const;
	const bool isnumeric() const;
	const bool islowercase() const;
	const bool isprintable() const;
	const bool ispunctuation() const;
	const bool iswhitespace() const;
	const bool isuppercase() const;

	/// Clears the string contents
	sdpString& clear();
};

/// Converts any stream-serializeable type into an sdpString
template<class Type>
const sdpString sdpToString(const Type& Value)
{
	std::ostringstream stream;
	stream << Value;

	const sdpString result(stream.str());

	return result;
}

/// Specialization for converting bool to sdpString
inline const sdpString sdpToString(const bool Value)
{
	std::ostringstream stream;

	stream << (Value ? "true" : "false");

	const sdpString result(stream.str());

	return result;
}

/// Converts an sdpString into any stream-serializeable type
template<class Type>
const Type sdpFromString(const sdpString Value, const Type& DefaultValue)
{
	Type result = DefaultValue;
	std::istringstream stream(Value.c_str());
	stream >> result;

	return result;
}

/// Specialization for converting sdpString to bool
inline const bool sdpFromString(const sdpString Value, const bool DefaultValue)
{
	bool result = DefaultValue;

	if(0 == Value.find("true"))
		result = true;
	else if(0 == Value.find("false"))
		result = false;

	return result;
}

typedef std::vector<sdpString> sdpStringArray;

/// Returns the linear interpolation of two values
template<class Type> Type sdpLerp(const Type& A, const Type& B, const gdouble Mix)
{	return A + ((B - A) * Mix); }

/// Returns the sign of an argument: -1 if negative, 0 if zero, +1 if positive
template<class Type> gdouble sdpSign(const Type& Arg)
{
	if(Arg > 0.0) return 1.0;
	if(Arg < 0.0) return -1.0;

	return 0.0;
}

/// Converts degrees to radians
template<class Type> Type sdpRadians(const Type& Degrees)
{	return Degrees * 0.01745329252; }

/// Converts radians to degrees
template<class Type> Type sdpDegrees(const Type& Radians)
{	return Radians * 57.2957795131; }

/****************************************************************
*
* C++ Vector and Matrix Algebra routines
* Author: Jean-Francois DOUE
* Version 3.1 --- October 1993
*
****************************************************************/

//
//	From "Graphics Gems IV / Edited by Paul S. Heckbert
//	Academic Press, 1994, ISBN 0-12-336156-9
//	"You are free to use and modify this code in any way
//	you like." (p. xv)
//
//	Modified by J. Nagle, March 1997
//	-	All functions are inline.
//	-	All functions are const-correct.
//	-	All checking is via the standard "g_assert" macro.
//

// Modified by Tim Shead for use with K-3D, January 1998

// Forward class declarations ...
class sdpVector2;
class sdpVector3;

/// Axes array indices
enum {VX, VY, VZ, VW};

/////////////////////////////////////////////////////////////////////////////
// sdpVector2

/// A two-dimensional vector
class sdpVector2
{
public:
	/// Stores the vector values
	gdouble n[2];

	// Constructors
	sdpVector2();
	sdpVector2(const gdouble x, const gdouble y);
	sdpVector2(const gdouble d);
	sdpVector2(const gdouble[2]);
	/// Copy constructor
	sdpVector2(const sdpVector2& v);
	/// Casts an sdpVector3 to an sdpVector2, dropping the third dimension
	sdpVector2(const sdpVector3& v);
	/// Assigns an sdpVector2
	sdpVector2& operator	= (const sdpVector2& v);
	/// Assigns a C/C++ style array
	sdpVector2& operator = (const gdouble[2]);
	/// Adds an sdpVector2
	sdpVector2& operator += (const sdpVector2& v);
	/// Subtracts an sdpVector2
	sdpVector2& operator -= (const sdpVector2& v);
	/// Multiplication by a constant
	sdpVector2& operator *= (const gdouble d);
	/// Division by a constant
	sdpVector2& operator /= (const gdouble d);
	/// Returns an indexed dimension by reference
	gdouble& operator [] (gint i);
	/// Returns an indexed dimension by value
	gdouble sdpVector2::operator [] (gint i) const;
	/// Returns the vector length
	gdouble Length() const;
	/// Returns the square of the vector length
	gdouble Length2() const;
	/// Normalizes the vector in place
	sdpVector2& Normalize();
	/// Casting to a C/C++ style array pointer
	operator gdouble*() { return &n[0]; }

	friend std::ostream& operator<<(std::ostream& Stream, const sdpVector2& RHS)
	{
		Stream << RHS.n[0] << " " << RHS.n[1];
		return Stream;
	}

	friend std::istream& operator>>(std::istream& Stream, sdpVector2& RHS)
	{
		Stream >> RHS.n[0];
		RHS.n[1] = RHS.n[0];
		Stream >> RHS.n[1];

		return Stream;
	}

};

/// Negation
sdpVector2 operator - (const sdpVector2& v);
/// Addition
sdpVector2 operator + (const sdpVector2& a, const sdpVector2& b);
/// Subtraction
sdpVector2 operator - (const sdpVector2& a, const sdpVector2& b);
/// Multiplication by a constant
sdpVector2 operator * (const sdpVector2& a, const gdouble d);
/// Multiplication by a constant
sdpVector2 operator * (const gdouble d, const sdpVector2& a);
/// Returns the dot product of two vectors
gdouble operator * (const sdpVector2& a, const sdpVector2& b);
/// Division by a constant
sdpVector2 operator / (const sdpVector2& a, const gdouble d);
/// Returns the cross product of two vectors
sdpVector3 operator ^ (const sdpVector2& a, const sdpVector2& b);
/// Tests for equality
gint operator == (const sdpVector2& a, const sdpVector2& b);
/// Tests for non-equality
gint operator != (const sdpVector2& a, const sdpVector2& b);

/////////////////////////////////////////////////////////////////////////////
// sdpVector3

// We have an unfortunate clash with <windows.h> ... go figure
#ifdef SDPWIN32
#ifdef RGB
#undef RGB
#endif // RGB
#endif // SDPWIN32

/// A three-dimensional vector
class sdpVector3
{
public:
	/// Stores the vector values
	gdouble n[3];

	// Constructors
	sdpVector3();
	sdpVector3(const gdouble x, const gdouble y, const gdouble z);
	sdpVector3(const gdouble d);
	sdpVector3(const gdouble d[3]);
	/// Copy constructor
	sdpVector3(const sdpVector3& v);
	/// Casts an sdpVector2 to an sdpVector3 (with zero third dimension)
	sdpVector3(const sdpVector2& v);
	/// Casts an sdpVector2 to an sdpVector3 with the given third dimension
	sdpVector3(const sdpVector2& v, gdouble d);
	/// Assignment of an sdpVector3
	sdpVector3& operator	= (const sdpVector3& v);
	/// Assignment of a C/C++ style array
	sdpVector3& operator = (const gdouble d[3]);
	/// Addition
	sdpVector3& operator += (const sdpVector3& v);
	/// Subtraction
	sdpVector3& operator -= (const sdpVector3& v);
	/// Multiplication by a constant
	sdpVector3& operator *= (const gdouble d);
	/// Division by a constant
	sdpVector3& operator /= (const gdouble d);
	/// Returns the given dimension by reference
	gdouble& operator [] (gint i);
	/// Returns the given dimension by value
	gdouble operator[] (gint i) const;
	/// Returns the vector length
	gdouble Length() const;
	/// Returns the squared vector length
	gdouble Length2() const;
	/// Normalizes the vector in place
	sdpVector3& Normalize();
	/// Converts an RGB color to HSV
	sdpVector3 HSV() const;
	/// Converts an HSV color to RGB
	sdpVector3 RGB() const;
	/// Casting to a C/C++ style array pointer
	operator gdouble*() { return &n[0]; }

	friend std::ostream& operator<<(std::ostream& Stream, const sdpVector3& RHS)
	{
		Stream << RHS.n[0] << " " << RHS.n[1] << " " << RHS.n[2];
		return Stream;
	}

	friend std::istream& operator>>(std::istream& Stream, sdpVector3& RHS)
	{
		Stream >> RHS.n[0];
		RHS.n[1] = RHS.n[2] = RHS.n[0];
		Stream >> RHS.n[1] >> RHS.n[2];

		return Stream;
	}

};

/// Negation
sdpVector3 operator - (const sdpVector3& v);
/// Addition
sdpVector3 operator + (const sdpVector3& a, const sdpVector3& b);
/// Subtraction
sdpVector3 operator - (const sdpVector3& a, const sdpVector3& b);
/// Multiplication by a constant
sdpVector3 operator * (const sdpVector3& a, const gdouble d);
/// Multiplication by a constant
sdpVector3 operator * (const gdouble d, const sdpVector3& a);
/// Returns the dot product of two vectors
gdouble operator * (const sdpVector3& a, const sdpVector3& b);
/// Division by a constant
sdpVector3 operator / (const sdpVector3& a, const gdouble d);
/// Returns the cross product of two vectors
sdpVector3 operator ^ (const sdpVector3& a, const sdpVector3& b);
/// Equality
gint operator == (const sdpVector3& a, const sdpVector3& b);
/// Non-equality
gint operator != (const sdpVector3& a, const sdpVector3& b);

/////////////////////////////////////////////////////////////////////////////
// sdpVector2 implementation

inline sdpVector2::sdpVector2()
{ n[VX] = n[VY] = 0.0; }

inline sdpVector2::sdpVector2(const gdouble x, const gdouble y)
{ n[VX] = x; n[VY] = y; }

inline sdpVector2::sdpVector2(const gdouble d)
{ n[VX] = n[VY] = d; }

inline sdpVector2::sdpVector2(const gdouble d[2])
{ n[VX] = d[0]; n[VY] = d[1]; }

inline sdpVector2::sdpVector2(const sdpVector2& v)
{ n[VX] = v.n[VX]; n[VY] = v.n[VY]; }

inline sdpVector2::sdpVector2(const sdpVector3& v) // it is up to caller to avoid divide-by-zero
{ n[VX] = v.n[VX]/v.n[VZ]; n[VY] = v.n[VY]/v.n[VZ]; }

inline sdpVector2& sdpVector2::operator = (const sdpVector2& v)
{ n[VX] = v.n[VX]; n[VY] = v.n[VY]; return *this; }

inline sdpVector2& sdpVector2::operator = (const gdouble d[2])
{ n[VX] = d[0]; n[VY] = d[1]; return *this; }

inline sdpVector2& sdpVector2::operator += (const sdpVector2& v)
{ n[VX] += v.n[VX]; n[VY] += v.n[VY]; return *this; }

inline sdpVector2& sdpVector2::operator -= (const sdpVector2& v)
{ n[VX] -= v.n[VX]; n[VY] -= v.n[VY]; return *this; }

inline sdpVector2& sdpVector2::operator *= (const gdouble d)
{ n[VX] *= d; n[VY] *= d; return *this; }

inline sdpVector2& sdpVector2::operator /= (const gdouble d)
{ gdouble d_inv = 1./d; n[VX] *= d_inv; n[VY] *= d_inv; return *this; }

inline gdouble& sdpVector2::operator [] (gint i)
{
 g_assert(!(i < VX || i > VY));
 return n[i];
}

inline gdouble sdpVector2::operator [] (gint i) const
{
 g_assert(!(i < VX || i > VY));
 return n[i];
}

inline gdouble sdpVector2::Length() const
{ return sqrt(Length2()); }

inline gdouble sdpVector2::Length2() const
{ return n[VX]*n[VX] + n[VY]*n[VY]; }

inline sdpVector2& sdpVector2::Normalize()
{
	if(const gdouble length = Length())
		*this /= length;

	return *this;
}

inline sdpVector2 operator - (const sdpVector2& a)
{ return sdpVector2(-a.n[VX],-a.n[VY]); }

inline sdpVector2 operator + (const sdpVector2& a, const sdpVector2& b)
{ return sdpVector2(a.n[VX]+ b.n[VX], a.n[VY] + b.n[VY]); }

inline sdpVector2 operator - (const sdpVector2& a, const sdpVector2& b)
{ return sdpVector2(a.n[VX]-b.n[VX], a.n[VY]-b.n[VY]); }

inline sdpVector2 operator * (const sdpVector2& a, const gdouble d)
{ return sdpVector2(d*a.n[VX], d*a.n[VY]); }

inline sdpVector2 operator * (const gdouble d, const sdpVector2& a)
{ return a*d; }

inline gdouble operator * (const sdpVector2& a, const sdpVector2& b)
{ return (a.n[VX]*b.n[VX] + a.n[VY]*b.n[VY]); }

inline sdpVector2 operator / (const sdpVector2& a, const gdouble d)
{ gdouble d_inv = 1./d; return sdpVector2(a.n[VX]*d_inv, a.n[VY]*d_inv); }

inline sdpVector3 operator ^ (const sdpVector2& a, const sdpVector2& b)
{ return sdpVector3(0.0, 0.0, a.n[VX] * b.n[VY] - b.n[VX] * a.n[VY]); }

inline gint operator == (const sdpVector2& a, const sdpVector2& b)
{ return (a.n[VX] == b.n[VX]) && (a.n[VY] == b.n[VY]); }

inline gint operator != (const sdpVector2& a, const sdpVector2& b)
{ return !(a == b); }

/////////////////////////////////////////////////////////////////////////////
// sdpVector3 implementation

inline sdpVector3::sdpVector3()
{ n[VX] = n[VY] = n[VZ] = 0.0; }

inline sdpVector3::sdpVector3(const gdouble x, const gdouble y, const gdouble z)
{ n[VX] = x; n[VY] = y; n[VZ] = z; }

inline sdpVector3::sdpVector3(const gdouble d)
{ n[VX] = n[VY] = n[VZ] = d; }

inline sdpVector3::sdpVector3(const gdouble d[3])
{ n[VX] = d[0]; n[VY] = d[1]; n[VZ] = d[2]; }

inline sdpVector3::sdpVector3(const sdpVector3& v)
{ n[VX] = v.n[VX]; n[VY] = v.n[VY]; n[VZ] = v.n[VZ]; }

inline sdpVector3::sdpVector3(const sdpVector2& v)
{ n[VX] = v.n[VX]; n[VY] = v.n[VY]; n[VZ] = 1.0; }

inline sdpVector3::sdpVector3(const sdpVector2& v, gdouble d)
{ n[VX] = v.n[VX]; n[VY] = v.n[VY]; n[VZ] = d; }

inline sdpVector3& sdpVector3::operator = (const sdpVector3& v)
{ n[VX] = v.n[VX]; n[VY] = v.n[VY]; n[VZ] = v.n[VZ]; return *this; }

inline sdpVector3& sdpVector3::operator = (const gdouble d[3])
{ n[VX] = d[0]; n[VY] = d[1]; n[VZ] = d[2]; return *this; }

inline sdpVector3& sdpVector3::operator += (const sdpVector3& v)
{ n[VX] += v.n[VX]; n[VY] += v.n[VY]; n[VZ] += v.n[VZ]; return *this; }

inline sdpVector3& sdpVector3::operator -= (const sdpVector3& v)
{ n[VX] -= v.n[VX]; n[VY] -= v.n[VY]; n[VZ] -= v.n[VZ]; return *this; }

inline sdpVector3& sdpVector3::operator *= (const gdouble d)
{ n[VX] *= d; n[VY] *= d; n[VZ] *= d; return *this; }

inline sdpVector3& sdpVector3::operator /= (const gdouble d)
{ gdouble d_inv = 1./d; n[VX] *= d_inv; n[VY] *= d_inv; n[VZ] *= d_inv;
 return *this; }

inline gdouble& sdpVector3::operator [] (gint i) {
 g_assert(! (i < VX || i > VZ));
 return n[i];
}

inline gdouble sdpVector3::operator [] (gint i) const {
 g_assert(! (i < VX || i > VZ));
 return n[i];
}

inline gdouble sdpVector3::Length() const
{ return sqrt(Length2()); }

inline gdouble sdpVector3::Length2() const
{ return n[VX]*n[VX] + n[VY]*n[VY] + n[VZ]*n[VZ]; }

inline sdpVector3& sdpVector3::Normalize()
{
	if(const gdouble length = Length())
		*this /= length;

	return *this;
}

inline sdpVector3 sdpVector3::HSV() const
{
	const gdouble maxcomponent = std::max(std::max(n[0], n[1]), n[2]);
	const gdouble mincomponent = std::min(std::min(n[0], n[1]), n[2]);
	const gdouble difference = maxcomponent - mincomponent;

	sdpVector3 result;

	// Set value equal to the largest RGB component
	result[2] = maxcomponent;

	// Set saturation
	result[1] = (0.0 == maxcomponent) ? 0.0 : difference / maxcomponent;

	// If saturation is zero, assign Hue a reasonable default ...
	if(0.0 == result[1])
	{
		result[0] = 0.0;
	}
	else
	{
		const gdouble reddistance = (maxcomponent - n[0]) / difference;
		const gdouble greendistance = (maxcomponent - n[1]) / difference;
		const gdouble bluedistance = (maxcomponent - n[2]) / difference;

		if(n[0] == maxcomponent)
			{
				result[0] = bluedistance - greendistance;
			}
		else if(n[1] == maxcomponent)
			{
				result[0] = 2 + reddistance - bluedistance;
			}
		else
			{
				result[0] = 4 + greendistance - reddistance;
			}

		result[0] *= 60.0;
		if(result[0] < 0.0) result[0] += 360.0;
	}

	return result;
}

inline sdpVector3 sdpVector3::RGB() const
{
	sdpVector3 result = *this;

	if(result[1] == 0.0)	// If saturation is zero, the result is greyscale
	{
		result = result[2];
	}
	else
	{
		if(360.0 == result[0])
			result[0] = 0.0;

		const gdouble h = result[0] / 60.0;
		const gdouble i = floor(h);
		const gdouble f = h - i;
		const gdouble p = result[2] * (1 - result[1]);
		const gdouble q = result[2] * (1 - (result[1] * f));
		const gdouble t = result[2] * (1 - (result[1] * (1 - f)));

		if(0.0 == i)
		{
			result[0] = result[2];
			result[1] = t;
			result[2] = p;
		}
		else if(1.0 == i)
		{
			result[0] = q;
			result[1] = result[2];
			result[2] = p;
		}
		else if(2.0 == i)
		{
			result[0] = p;
			result[1] = result[2];
			result[2] = t;
		}
		else if(3.0 == i)
		{
			result[0] = p;
			result[1] = q;
			result[2] = result[2];
		}
		else if(4.0 == i)
		{
			result[0] = t;
			result[1] = p;
			result[2] = result[2];
		}
		else if(5.0 == i)
		{
			result[0] = result[2];
			result[1] = p;
			result[2] = q;
		}
	}

	return result;
}

inline sdpVector3 operator - (const sdpVector3& a)
{ return sdpVector3(-a.n[VX],-a.n[VY],-a.n[VZ]); }

inline sdpVector3 operator + (const sdpVector3& a, const sdpVector3& b)
{ return sdpVector3(a.n[VX]+ b.n[VX], a.n[VY] + b.n[VY], a.n[VZ] + b.n[VZ]); }

inline sdpVector3 operator - (const sdpVector3& a, const sdpVector3& b)
{ return sdpVector3(a.n[VX]-b.n[VX], a.n[VY]-b.n[VY], a.n[VZ]-b.n[VZ]); }

inline sdpVector3 operator * (const sdpVector3& a, const gdouble d)
{ return sdpVector3(d*a.n[VX], d*a.n[VY], d*a.n[VZ]); }

inline sdpVector3 operator * (const gdouble d, const sdpVector3& a)
{ return a*d; }

inline gdouble operator * (const sdpVector3& a, const sdpVector3& b)
{ return (a.n[VX]*b.n[VX] + a.n[VY]*b.n[VY] + a.n[VZ]*b.n[VZ]); }

inline sdpVector3 operator / (const sdpVector3& a, const gdouble d)
{ gdouble d_inv = 1./d; return sdpVector3(a.n[VX]*d_inv, a.n[VY]*d_inv,
 a.n[VZ]*d_inv); }

inline sdpVector3 operator ^ (const sdpVector3& a, const sdpVector3& b) {
 return sdpVector3(a.n[VY]*b.n[VZ] - a.n[VZ]*b.n[VY],
		a.n[VZ]*b.n[VX] - a.n[VX]*b.n[VZ],
		a.n[VX]*b.n[VY] - a.n[VY]*b.n[VX]);
}

inline gint operator == (const sdpVector3& a, const sdpVector3& b)
{ return (a.n[VX] == b.n[VX]) && (a.n[VY] == b.n[VY]) && (a.n[VZ] == b.n[VZ]);
}

inline gint operator != (const sdpVector3& a, const sdpVector3& b)
{ return !(a == b); }

/// Safely returns an environment variable
sdpString sdpGetEnv(SDPCSTRING EnvironmentVariable);
/// Safely returns the current working directory
sdpString sdpGetCurrentDirectory();
/// Safely returns the user's home directory
sdpString sdpGetHomeDirectory();
/// Safely returns the user's temp directory
sdpString sdpGetTempDirectory();

/// Cross-platform method for creating a directory
bool sdpCreateDirectory(SDPCSTRING Path);
/// Tests to see if the given file exists
bool sdpFileExists(SDPCSTRING Path);
/// Returns the most recent modification time of a file
bool sdpFileModificationTime(SDPCSTRING Path, GTime& ModificationTime);

/// Forces a filepath to the native filesystem's format (converts slashes, etc.)
sdpString sdpMakeNativeFilePath(SDPCSTRING FilePath);
/// Forces a filepath to the Posix format (forward slashes)
sdpString sdpMakePosixFilePath(SDPCSTRING FilePath);

/// Returns the directory components of a filepath
sdpString sdpDirectory(SDPCSTRING FilePath);
/// Returns the file component of a filepath
sdpString sdpFile(SDPCSTRING FilePath);

/// Appends three paths (handles trailing slashes, if present)
sdpString sdpAppendPath(SDPCSTRING Path1, SDPCSTRING Path2, SDPCSTRING Path3);
/// Appends two paths (handles a trailing slash on the first path, if present)
sdpString sdpAppendPath(SDPCSTRING Path1, SDPCSTRING Path2);

#endif // SDPTYPES_H

