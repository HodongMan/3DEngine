#include "pch.h"

#include "GraphicsManager.h"
#include "SwapChain.h"
#include "DeviceContext.h"


GraphicsManager::~GraphicsManager( void )
{

}

bool GraphicsManager::initialize( void ) noexcept
{
	const D3D_DRIVER_TYPE driverTypes[] =
	{
		D3D_DRIVER_TYPE_HARDWARE,
		D3D_DRIVER_TYPE_WARP,
		D3D_DRIVER_TYPE_REFERENCE
	};

	const D3D_FEATURE_LEVEL featureLevels[]=
	{
		D3D_FEATURE_LEVEL_11_0
	};

	const UINT driverCount			= _ARRAYSIZE( driverTypes );
	const UINT featureLevelCount	= _ARRAYSIZE( featureLevels );
	HRESULT hr;

	ID3D11DeviceContext* deviceContext = nullptr;

	for ( UINT ii = 0; ii < driverCount; ++ii )
	{
		 hr = D3D11CreateDevice( NULL, driverTypes[ii], NULL, NULL, featureLevels, featureLevelCount, D3D11_SDK_VERSION, &_device, &_featureLevel, &deviceContext );

		if ( true == SUCCEEDED( hr ) )
		{
			break;
		}
	}

	if ( true == FAILED ( hr ) )
	{
		return false;
	}

	_deviceContext = new DeviceContext( deviceContext );

	_device->QueryInterface( __uuidof( IDXGIDevice ), (void**)&_dxgiDevice );
	_dxgiDevice->GetParent( __uuidof( IDXGIAdapter ),  (void**)&_dxgiAdapter );
	_dxgiAdapter->GetParent( __uuidof( IDXGIFactory ), (void**)&_dxgiFactory );

	return true;
}

bool GraphicsManager::release( void ) noexcept
{
	_dxgiFactory->Release();
	_dxgiAdapter->Release();
	_dxgiDevice->Release();

	_deviceContext->release();
	_device->Release();
	

	return true;
}

GraphicsManager* GraphicsManager::getInstance( void ) noexcept
{
	static GraphicsManager graphicsManager;

	return &graphicsManager;
}

SwapChain* GraphicsManager::createSwapChain( void ) const noexcept
{
	return new SwapChain();
}

DeviceContext * GraphicsManager::getDeviceContext( void ) const noexcept
{
	return _deviceContext;
}

GraphicsManager::GraphicsManager( void )
	: _device{ nullptr }
	, _deviceContext{ nullptr }
	, _dxgiDevice{ nullptr }
	, _dxgiAdapter{ nullptr }
{

}
