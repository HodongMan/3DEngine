#include "pch.h"

#include "IndexBuffer.h"
#include "GraphicsManager.h"

IndexBuffer::IndexBuffer( void )
	: _buffer{ nullptr }
	, _listSize{ 0 }
{

}

IndexBuffer::~IndexBuffer( void )
{

}

bool IndexBuffer::load( void* indicies, const UINT listSize ) noexcept
{
	D3D11_BUFFER_DESC buffDesc		= {};
	buffDesc.Usage					= D3D11_USAGE_DEFAULT;
	buffDesc.ByteWidth				= 4 * listSize;
	buffDesc.BindFlags				= D3D11_BIND_INDEX_BUFFER;
	buffDesc.CPUAccessFlags			= 0;
	buffDesc.MiscFlags				= 0;

	D3D11_SUBRESOURCE_DATA initData = {};
	initData.pSysMem				= indicies;

	_listSize						= listSize;

	if ( FAILED( GraphicsManager::getInstance()->_device->CreateBuffer( &buffDesc, &initData, &_buffer ) ) )
	{
		return false;
	}

	return true;
}

UINT IndexBuffer::getlistSize( void ) const noexcept
{
	return _listSize;
}

bool IndexBuffer::release( void ) noexcept
{
	_buffer->Release();

	return true;
}
