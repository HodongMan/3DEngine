#include "pch.h"

#include "VertexBuffer.h"
#include "GraphicsManager.h"

VertexBuffer::VertexBuffer( void )
	: _buffer{ nullptr }
	, _layout{ nullptr }
{

}

VertexBuffer::~VertexBuffer( void )
{
	
}

bool VertexBuffer::load( void* vertices, const UINT vertexSize , const UINT listSize, void* shaderByteCode, const size_t byteShaderSize ) noexcept
{
	D3D11_BUFFER_DESC bufferDesc	= {};

	bufferDesc.Usage				= D3D11_USAGE_DEFAULT;
	bufferDesc.ByteWidth			= vertexSize * listSize;
	bufferDesc.BindFlags			= D3D11_BIND_VERTEX_BUFFER;
	bufferDesc.CPUAccessFlags		= 0;
	bufferDesc.MiscFlags			= 0;

	D3D11_SUBRESOURCE_DATA	initData = {};

	initData.pSysMem = vertices;

	_vertexSize						= vertexSize;
	_listSize						= listSize;

	if ( FAILED( GraphicsManager::getInstance()->_device->CreateBuffer( &bufferDesc, &initData, &_buffer ) ) )
	{
		return false;
	}

	const D3D11_INPUT_ELEMENT_DESC layout[] = 
	{ 
		"POSITION", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 
	};
	
	const UINT layoutSize = _ARRAYSIZE( layout );

	if ( FAILED( GraphicsManager::getInstance()->_device->CreateInputLayout( layout, layoutSize, shaderByteCode, byteShaderSize, &_layout ) ) )
	{
		return false;
	}

	return true;
}

bool VertexBuffer::release( void ) noexcept
{
	if ( nullptr != _layout )
	{
		_layout->Release();
	}

	if ( nullptr != _buffer )
	{
		_buffer->Release();
	}
	
	return true;
}

UINT VertexBuffer::getSizeVertexList( void ) const noexcept
{
	return _listSize;
}
