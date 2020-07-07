#pragma once

class DeviceContext;


class IndexBuffer
{
public:
	IndexBuffer( void );
	~IndexBuffer( void );

	bool			load( void* indicies, const UINT listSize ) noexcept;
	UINT			getlistSize( void ) const noexcept;
	bool			release( void ) noexcept;

private:

	ID3D11Buffer*	_buffer;
	UINT			_listSize;

	friend class DeviceContext;
};