#pragma once

class DeviceContext;


class VertexBuffer
{
public:
	VertexBuffer( void );
	~VertexBuffer( void );

	bool				load( void* vertices, const UINT vertexSize , const UINT listSize, void* shaderByteCode, const size_t byteShaderSize ) noexcept;
	bool				release( void ) noexcept;

	UINT				getSizeVertexList( void ) const noexcept;

private:

	UINT				_vertexSize;
	UINT				_listSize;

	ID3D11Buffer*		_buffer;
	ID3D11InputLayout*	_layout;

	friend class DeviceContext;
};