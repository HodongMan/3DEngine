#include "pch.h"

#include "ConstantBuffer.h"
#include "DeviceContext.h"
#include "GraphicsManager.h"

ConstantBuffer::ConstantBuffer( void )
	: _buffer{ nullptr }
{

}

ConstantBuffer::~ConstantBuffer( void )
{

}

bool ConstantBuffer::load( void * buffer, UINT bufferSize ) noexcept
{
	D3D11_BUFFER_DESC buffDesc = {};
	buffDesc.Usage				= D3D11_USAGE_DEFAULT;
	buffDesc.ByteWidth			= bufferSize;
	buffDesc.BindFlags			= D3D11_BIND_CONSTANT_BUFFER;
	buffDesc.CPUAccessFlags		= 0;
	buffDesc.MiscFlags			= 0;

	D3D11_SUBRESOURCE_DATA initData = {};
	initData.pSysMem			= buffer;

	if ( FAILED( GraphicsManager::getInstance()->_device->CreateBuffer( &buffDesc, &initData, &_buffer ) ) )
	{
		return false;
	}

	return true;
}

void ConstantBuffer::update( DeviceContext * deviceContext, void * buffer ) noexcept
{
	deviceContext->_deviceContext->UpdateSubresource( _buffer, NULL, NULL, buffer, NULL, NULL );
}

bool ConstantBuffer::release( void ) noexcept
{
	if ( nullptr != _buffer )
	{
		_buffer->Release();
	}

	return true;
}
