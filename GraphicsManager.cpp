#include "pch.h"

#include "GraphicsManager.h"
#include "SwapChain.h"
#include "DeviceContext.h"
#include "VertexBuffer.h"


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
	HRESULT hr						= 0;

	for ( UINT ii = 0; ii < driverCount; ++ii )
	{
		 hr = D3D11CreateDevice( NULL, driverTypes[ii], NULL, NULL, featureLevels, featureLevelCount, D3D11_SDK_VERSION, &_device, &_featureLevel, &_d3d11DeviceContext );

		if ( true == SUCCEEDED( hr ) )
		{
			break;
		}
	}

	if ( true == FAILED ( hr ) )
	{
		return false;
	}

	_deviceContext = new DeviceContext( _d3d11DeviceContext );

	_device->QueryInterface( __uuidof( IDXGIDevice ), (void**)&_dxgiDevice );
	_dxgiDevice->GetParent( __uuidof( IDXGIAdapter ),  (void**)&_dxgiAdapter );
	_dxgiAdapter->GetParent( __uuidof( IDXGIFactory ), (void**)&_dxgiFactory );

	return true;
}

bool GraphicsManager::release( void ) noexcept
{
	if ( nullptr != _vertexShader )
	{
		_vertexShader->Release();
	}

	if ( nullptr != _pixelShader )
	{
		_pixelShader->Release();
	}

	if ( nullptr != _vsblob )
	{
		_vsblob->Release();
	}

	if ( nullptr != _psblob )
	{
		_psblob->Release();
	}

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

VertexBuffer * GraphicsManager::createVertexBuffer( void ) const noexcept
{
	return new VertexBuffer();
}

bool GraphicsManager::createShaders( void ) noexcept
{
	ID3DBlob* errblob = nullptr;

	D3DCompileFromFile( L"shader.fx", nullptr, nullptr, "vsmain", "vs_5_0", NULL, NULL, &_vsblob, &errblob );
	D3DCompileFromFile( L"shader.fx", nullptr, nullptr, "psmain", "ps_5_0", NULL, NULL, &_psblob, &errblob );
	
	_device->CreateVertexShader( _vsblob->GetBufferPointer(), _vsblob->GetBufferSize(), nullptr, &_vertexShader );
	_device->CreatePixelShader( _psblob->GetBufferPointer(), _psblob->GetBufferSize(), nullptr, &_pixelShader );
	
	return true;
}

bool GraphicsManager::setShaders( void ) noexcept
{
	_d3d11DeviceContext->VSSetShader( _vertexShader, nullptr, 0 );
	_d3d11DeviceContext->PSSetShader( _pixelShader, nullptr, 0 );
	return true;
}

void GraphicsManager::getShaderBufferAndSize( void ** bytecode, UINT * size ) const noexcept
{
	*bytecode		= _vsblob->GetBufferPointer();
	*size			= static_cast<UINT>( _vsblob->GetBufferSize() ); 
}

GraphicsManager::GraphicsManager( void )
	: _device{ nullptr }
	, _deviceContext{ nullptr }
	, _dxgiDevice{ nullptr }
	, _dxgiAdapter{ nullptr }
{

}
