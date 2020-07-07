#pragma once

#include <array>
#include "Math.h"
#include "Vector.h"

class Matrix4
{
public:
	Matrix4( void )
	{
		for ( int ii = 0; ii < MATRIX_SIZE; ++ii )
		{
			_matrix[ii].fill( 0 );
		}
	}

	void setIdentity( void ) noexcept
	{
		for ( int ii = 0; ii < MATRIX_SIZE; ++ii )
		{
			_matrix[ii].fill( 0 );
		}

		_matrix[0][0] = 1;
		_matrix[1][1] = 1;
		_matrix[2][2] = 1;
		_matrix[3][3] = 1;
	}

	void setTranslation( const Vector3& translation ) noexcept
	{
		setIdentity();
		_matrix[3][0] = translation.getX();
		_matrix[3][1] = translation.getY();
		_matrix[3][2] = translation.getZ();
	}

	void setScale( const Vector3& scale ) noexcept
	{
		setIdentity();
		_matrix[0][0] = scale.getX();
		_matrix[1][1] = scale.getY();
		_matrix[2][2] = scale.getZ();
	}

	void setRotationX( const float x ) noexcept
	{
		_matrix[1][1] = Math::cos( x );
		_matrix[1][2] = Math::sin( x );
		_matrix[2][1] = -Math::sin( x );
		_matrix[2][2] = Math::cos( x );
	}

	void setRotationY( const float y ) noexcept
	{
		_matrix[0][0] = Math::cos( y );
		_matrix[0][2] = -Math::sin( y );
		_matrix[2][0] = Math::sin( y );
		_matrix[2][2] = Math::cos( y );
	}

	void setRotationZ( const float z ) noexcept
	{
		_matrix[0][0] = Math::cos( z );
		_matrix[0][1] = Math::sin( z );
		_matrix[1][0] = -Math::sin( z );
		_matrix[1][1] = Math::cos( z );
	}

private:

	std::array<std::array<int, MATRIX_SIZE>, MATRIX_SIZE> _matrix;
};

static float m4Identity[4][4] =
{
	{ 1.0f, 0.0f, 0.0f, 0.0f },
	{ 0.0f, 1.0f, 0.0f, 0.0f },
	{ 0.0f, 0.0f, 1.0f, 0.0f },
	{ 0.0f, 0.0f, 0.0f, 1.0f }
};