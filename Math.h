#pragma once

#include "pch.h"

#define MATRIX_SIZE 4

namespace Math

{
	inline float abs( float value ) noexcept
	{
		return fabs( value );
	}

	inline float cos( float angle ) noexcept
	{
		return cosf( angle );
	}

	inline float sin( float angle ) noexcept
	{
		return sinf( angle );
	}

	inline float tan( float angle ) noexcept
	{
		return tanf( angle );
	}

	inline float acos( float value ) noexcept
	{
		return acosf( value );
	}

	inline float ttan2( float x, float y ) noexcept
	{
		return atan2f( x, y );
	}

	inline float cot( float angle ) noexcept
	{
		return 1.0f / Math::tan( angle );
	}
}