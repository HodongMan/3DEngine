#pragma once


class Vector3
{
public:

	Vector3( void )
		: _x{ 0.0f }
		, _y{ 0.0f }
		, _z{ 0.0f }
	{
	
	}

	Vector3( const float x, const float y, const float z )
		: _x{ x }
		, _y{ y }
		, _z{ z }
	{
	
	}

	~Vector3( void )
	{
	
	}

	float		getX( void ) const noexcept
	{
		return _x;
	}

	float		getY( void ) const noexcept
	{
		return _y;
	}

	float		getZ( void ) const noexcept
	{
		return _z;
	}

private:

	float _x;
	float _y;
	float _z;
};