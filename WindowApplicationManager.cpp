#include "pch.h"

#include "WindowApplicationManager.h"
#include "GraphicsManager.h"
#include "SwapChain.h"
#include "DeviceContext.h"
#include "VertexBuffer.h"
#include "VertexShader.h"
#include "PixelShader.h"


struct Vector3
{
	float x;
	float y;
	float z;
};

struct Vertex
{
	Vector3 position;
};


WindowApplicationManager::WindowApplicationManager( void )
	: _swapChain{ nullptr }
	, _vertexBuffer{ nullptr }
{

}

WindowApplicationManager::~WindowApplicationManager( void )
{

}

void WindowApplicationManager::onCreate( void ) noexcept
{
	Window::onCreate();
	
	GraphicsManager::getInstance()->initialize();
	
	_swapChain = GraphicsManager::getInstance()->createSwapChain();

	RECT rect = getWindowRect();
	if ( false == _swapChain->initialize( _hwnd, rect.right - rect.left, rect.bottom - rect.top ) )
	{
		return;
	}

	Vertex list[] =
	{
		{ -0.5f, -0.5f, 0.0f},
		{ -0.5f, 0.5f, 0.0f},
		{ 0.5f, -0.5f, 0.0f },
		{ 0.5f, 0.5f, 0.0f}
	};

	_vertexBuffer	= GraphicsManager::getInstance()->createVertexBuffer();
	if ( nullptr == _vertexBuffer )
	{
		return;
	}

	const UINT listSize		= _ARRAYSIZE( list );

	void* shaderByteCode	= nullptr;
	size_t shaderSize		= 0;
	GraphicsManager::getInstance()->compileVertexShader( L"VertexShader.hlsl", "vsmain", &shaderByteCode, &shaderSize );
	_vertexShader = GraphicsManager::getInstance()->createVertexShader( shaderByteCode, shaderSize );
	_vertexBuffer->load( list, sizeof( Vertex ), listSize, shaderByteCode, shaderSize );

	GraphicsManager::getInstance()->releaseCompiledShader();

	bool isOk = GraphicsManager::getInstance()->compilePixelShader( L"PixelShader.hlsl", "psmain", &shaderByteCode, &shaderSize );
	
	_pixelShader = GraphicsManager::getInstance()->createPixelShader( shaderByteCode, shaderSize );
	_vertexBuffer->load( list, sizeof( Vertex ), listSize, shaderByteCode, shaderSize );

	GraphicsManager::getInstance()->releaseCompiledShader();
}

void WindowApplicationManager::onUpdate( void ) noexcept
{
	Window::onUpdate();
	GraphicsManager::getInstance()->getDeviceContext()->clearRenderTargetColor( _swapChain, 0, 0.3f, 0.4f, 1 );
	
	const RECT rc = getWindowRect();
	GraphicsManager::getInstance()->getDeviceContext()->setViewportSize( rc.right - rc.left, rc.bottom - rc.top );

	GraphicsManager::getInstance()->getDeviceContext()->setVertexShader( _vertexShader );
	GraphicsManager::getInstance()->getDeviceContext()->setPixelShader( _pixelShader );
	GraphicsManager::getInstance()->getDeviceContext()->setVertexBuffer( _vertexBuffer );

	GraphicsManager::getInstance()->getDeviceContext()->drawTriangleStrip( _vertexBuffer->getSizeVertexList(), 0);
	_swapChain->present( true );
}

void WindowApplicationManager::onDestroy( void ) noexcept
{
	Window::onDestroy();

	_vertexBuffer->release();
	_swapChain->release();

	_vertexShader->release();
	_pixelShader->release();

	GraphicsManager::getInstance()->release();
}