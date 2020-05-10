#include "pch.h"

#include "WindowApplicationManager.h"
#include "GraphicsManager.h"
#include "SwapChain.h"
#include "DeviceContext.h"
#include "VertexBuffer.h"

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
	if ( nullptr == _swapChain )
	{
		return;
	}

	RECT rect = getWindowRect();

	_swapChain->initialize( _hwnd, rect.right - rect.left, rect.bottom - rect.top );

	Vertex list[] =
	{
		{ -0.5f,-0.5f,0.0f },
		{ 0.0f,0.5f,0.0f },
		{ 0.5f,-0.5f,0.0f }
	};

	_vertexBuffer	= GraphicsManager::getInstance()->createVertexBuffer();
	if ( nullptr == _vertexBuffer )
	{
		return;
	}

	const UINT listSize = _ARRAYSIZE( list );

	GraphicsManager::getInstance()->createShaders();

	void* shaderByteCode = nullptr;
	UINT shaderSize = 0;
	GraphicsManager::getInstance()->getShaderBufferAndSize( &shaderByteCode, &shaderSize );

	_vertexBuffer->load( list, sizeof (Vertex), listSize, shaderByteCode, shaderSize );
}

void WindowApplicationManager::onUpdate( void ) noexcept
{
	Window::onUpdate();
	GraphicsManager::getInstance()->getDeviceContext()->clearRenderTargetColor( _swapChain, 0, 0.3f,0.4f, 1);
	
	const RECT rc = getWindowRect();
	GraphicsManager::getInstance()->getDeviceContext()->setViewportSize( rc.right - rc.left, rc.bottom - rc.top );
	GraphicsManager::getInstance()->setShaders();
	GraphicsManager::getInstance()->getDeviceContext()->setVertexBuffer( _vertexBuffer );

	GraphicsManager::getInstance()->getDeviceContext()->drawTriangleList( _vertexBuffer->getSizeVertexList(), 0);
	_swapChain->present( true );
}

void WindowApplicationManager::onDestroy( void ) noexcept
{
	Window::onDestroy();

	_vertexBuffer->release();
	_swapChain->release();

	GraphicsManager::getInstance()->release();
}