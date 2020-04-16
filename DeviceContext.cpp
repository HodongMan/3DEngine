#include "pch.h"

#include "DeviceContext.h"
#include "SwapChain.h"

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

	return false;
}

bool DeviceContext::release( void ) noexcept
{
	if ( nullptr != _deviceContext )
	{
		delete _deviceContext;
	}

	return true;
}
