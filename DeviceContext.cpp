#include "pch.h"

#include "DeviceContext.h"
#include "SwapChain.h"
#include "VertexBuffer.h"
#include "ConstantBuffer.h"
#include "VertexShader.h"
#include "PixelShader.h"


DeviceContext::DeviceContext( ID3D11DeviceContext* deviceContext )
	: _deviceContext{ deviceContext }
{

}

DeviceContext::~DeviceContext( void )
{

}

bool DeviceContext::clearRenderTargetColor( SwapChain* swapChain, const float red, const float green, const float blue, const float alpha ) noexcept
{
	FLOAT color[] = { red, green, blue, alpha };

	_deviceContext->ClearRenderTargetView( swapChain->_renderTargetView, color );
	_deviceContext->OMSetRenderTargets( 1, &swapChain->_renderTargetView, NULL );

	return false;
}

bool DeviceContext::release( void ) noexcept
{
	if ( nullptr != _deviceContext )
	{
		_deviceContext->Release();
	}

	return true;
}

bool DeviceContext::setVertexBuffer( const VertexBuffer* vertexBuffer ) noexcept
{
	const UINT stride = vertexBuffer->_vertexSize;
	const UINT offset = 0;

	_deviceContext->IASetVertexBuffers( 0, 1, &vertexBuffer->_buffer, &stride, &offset );
	_deviceContext->IASetInputLayout( vertexBuffer->_layout );
	return true;
}

void DeviceContext::drawTriangleList( const UINT vertexCount, const UINT vertexIndex ) noexcept
{
	_deviceContext->IASetPrimitiveTopology( D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST );
	_deviceContext->Draw( vertexCount, vertexIndex );
}

void DeviceContext::drawTriangleStrip( const UINT vertexCount, const UINT vertexIndex ) noexcept
{
	_deviceContext->IASetPrimitiveTopology( D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP );
	_deviceContext->Draw( vertexCount, vertexIndex );
}

void DeviceContext::setViewportSize( const UINT width, const UINT height ) noexcept
{
	D3D11_VIEWPORT viewPort;
	viewPort.Width			= static_cast<float>( width );
	viewPort.Height			= static_cast<float>( height );
	viewPort.MinDepth		= 0.0f;
	viewPort.MaxDepth		= 1.0f;

	_deviceContext->RSSetViewports( 1, &viewPort );
}

void DeviceContext::setVertexShader( const VertexShader* vertexShader) noexcept
{
	_deviceContext->VSSetShader( vertexShader->_vertexShader, nullptr, 0 );
}

void DeviceContext::setPixelShader( const PixelShader* pixelShader ) noexcept
{
	_deviceContext->PSSetShader( pixelShader->_pixelShader, nullptr, 0 );
}

void DeviceContext::setConstantBuffer( const VertexShader* vertexShader, const ConstantBuffer* buffer ) noexcept
{
	_deviceContext->VSSetConstantBuffers( 0, 1, &buffer->_buffer );
}

void DeviceContext::setConstantBuffer( const PixelShader* pixelShader, const ConstantBuffer* buffer ) noexcept
{
	_deviceContext->VSSetConstantBuffers( 0, 1, &buffer->_buffer );
}
