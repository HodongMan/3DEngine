#include "pch.h"

#include "GraphicsManager.h"
#include "SwapChain.h"
#include "DeviceContext.h"
#include "VertexBuffer.h"
#include "ConstantBuffer.h"
#include "VertexShader.h"
#include "PixelShader.h"


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

ConstantBuffer * GraphicsManager::createConstantBuffer(void) const noexcept
{
	return new ConstantBuffer();
}

VertexShader* GraphicsManager::createVertexShader( const void * shaderByteCode, const size_t shaderByteCodeSize ) noexcept
{
	VertexShader* vertexShader = new VertexShader();

	if ( false == vertexShader->initialize( shaderByteCode, shaderByteCodeSize ) )
	{
		vertexShader->release();
		return nullptr;
	}

	return vertexShader;
}

PixelShader* GraphicsManager::createPixelShader( const void * shaderByteCode, const size_t shaderByteCodeSize ) noexcept
{
	PixelShader* pixelShader = new PixelShader();

	if ( false == pixelShader->initialize( shaderByteCode, shaderByteCodeSize ) )
	{
		pixelShader->release();
		return nullptr;
	}

	return pixelShader;
}

bool GraphicsManager::compileVertexShader( const wchar_t * fileName, const char * entryPointName, void ** shaderByteCode, size_t * shaderByteCodeSize ) noexcept
{
	ID3DBlob* errorBlob = nullptr;
	if ( FAILED( ::D3DCompileFromFile( fileName, nullptr, nullptr, entryPointName, "vs_5_0", 0, 0, &_blob, &errorBlob) ) )
	{
		OutputDebugStringA( reinterpret_cast<const char*>( errorBlob->GetBufferPointer() ) );

		if ( nullptr != errorBlob ) 
		{
			errorBlob->Release();
		}
		
		return false;
	}

	*shaderByteCode			= _blob->GetBufferPointer();
	*shaderByteCodeSize		= _blob->GetBufferSize();

	return true;
}

bool GraphicsManager::compilePixelShader(const wchar_t * fileName, const char * entryPointName, void ** shaderByteCode, size_t * shaderByteCodeSize) noexcept
{
	ID3DBlob* errorBlob = nullptr;
	if ( FAILED( ::D3DCompileFromFile( fileName, nullptr, nullptr, entryPointName, "ps_5_0", 0, 0, &_blob, &errorBlob) ) )
	{
		OutputDebugStringA( reinterpret_cast<const char*>( errorBlob->GetBufferPointer() ) );

		if ( nullptr != errorBlob ) 
		{
			errorBlob->Release();
		}
		
		return false;
	}

	*shaderByteCode			= _blob->GetBufferPointer();
	*shaderByteCodeSize		= _blob->GetBufferSize();

	return true;
}

void GraphicsManager::releaseCompiledShader( void ) noexcept
{
	_blob->Release();
}

GraphicsManager::GraphicsManager( void )
	: _device{ nullptr }
	, _deviceContext{ nullptr }
	, _dxgiDevice{ nullptr }
	, _dxgiAdapter{ nullptr }
{

}
