#pragma once

class DeviceContext;


class ConstantBuffer
{
public:

	ConstantBuffer( void );
	~ConstantBuffer( void );

	bool					load( void* buffer, UINT bufferSize ) noexcept;
	void					update( DeviceContext* deviceContext, void* buffer ) noexcept;
	bool					release( void ) noexcept;

private:

	ID3D11Buffer*		_buffer;

	friend class DeviceContext;
};