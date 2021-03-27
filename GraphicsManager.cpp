#include "pch.h"


#include "GraphicsManager.h"


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

	const D3D_FEATURE_LEVEL featureLevels[] =
	{
		D3D_FEATURE_LEVEL_11_0
	};

	const UINT driverTypesCount		= ARRAYSIZE( driverTypes );
	const UINT featureLevelsCount	= ARRAYSIZE( featureLevels );

	HRESULT hResult					= NULL;
	UINT deviceFlags				= 0;
	deviceFlags						|= D3D11_CREATE_DEVICE_DEBUG;

	for ( UINT driverTypeIndex = 0; driverTypeIndex < driverTypesCount; ++driverTypeIndex )
	{
		hResult = D3D11CreateDevice( NULL, driverTypes[driverTypeIndex], NULL, deviceFlags, featureLevels, featureLevelsCount, D3D11_SDK_VERSION, &_d3dDevice, &_featureLevel, &_deviceContext );
		if ( true == SUCCEEDED( hResult ) )
		{
			break;
		}
	}

	if ( true == FAILED( hResult ) )
	{
		return false;
	}
		
	return true;
}

bool GraphicsManager::release( void ) noexcept
{
	if ( nullptr != _d3dDevice )
	{
		_d3dDevice->Release();
	}

	if ( nullptr != _deviceContext )
	{
		_deviceContext->Release();
	}

	return true;
}

GraphicsManager& GraphicsManager::getInstance( void ) noexcept
{
	static GraphicsManager graphicsManager;

	return graphicsManager;
}

GraphicsManager::GraphicsManager( void )
	: _d3dDevice( nullptr )
	, _featureLevel()
	, _deviceContext( nullptr )
{

}
