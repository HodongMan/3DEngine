#include "pch.h"

#include "SwapChain.h"
#include "GraphicsManager.h"

SwapChain::SwapChain( void )
	: _swapChain{ nullptr }
{

}

SwapChain::~SwapChain( void )
{

}

bool SwapChain::initialize( HWND hwnd, const UINT width, const UINT height ) noexcept
{
	ID3D11Device* device = GraphicsManager::getInstance()->_device;

	DXGI_SWAP_CHAIN_DESC desc;
	ZeroMemory( &desc, sizeof( desc) );

	desc.BufferCount						= 1;
	desc.BufferDesc.Format					= DXGI_FORMAT_R8G8B8A8_UNORM;
	desc.BufferDesc.Width					= width;
	desc.BufferDesc.Height					= height;
	desc.BufferDesc.RefreshRate.Numerator	= 60;
	desc.BufferDesc.RefreshRate.Denominator = 1;
	desc.BufferUsage						= DXGI_USAGE_RENDER_TARGET_OUTPUT;
	desc.OutputWindow						= hwnd;
	desc.SampleDesc.Count					= 1;
	desc.SampleDesc.Quality					= 0;
	desc.Windowed							= TRUE;

	HRESULT hr = GraphicsManager::getInstance()->_dxgiFactory->CreateSwapChain( device, &desc, &_swapChain );
	if ( true == FAILED( hr ) )
	{
		return false;
	}

	ID3D11Texture2D* textureBuffer = nullptr;
	_swapChain->GetBuffer( 0, __uuidof( ID3D11Texture2D ), (void**)&textureBuffer );

	hr = device->CreateRenderTargetView( textureBuffer, NULL, &_renderTargetView );
	if ( true == FAILED( hr ) )
	{
		return false;
	}

	textureBuffer->Release();

	return true;
}

bool SwapChain::release( void ) noexcept
{
	if ( nullptr != _swapChain )
	{
		_swapChain->Release();
		_swapChain = nullptr;
	}

	return true;
}

bool SwapChain::present( const bool async ) noexcept
{
	_swapChain->Present( async, NULL );

	return true;
}
