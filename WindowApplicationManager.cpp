#include "pch.h"

#include "WindowApplicationManager.h"
#include "GraphicsManager.h"
#include "SwapChain.h"
#include "DeviceContext.h"
#include "VertexBuffer.h"
#include "ConstantBuffer.h"
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
	Vector3 position1;
	Vector3 color;
	Vector3 color1;
};

__declspec( align( 16 ) )
struct Constant
{
	unsigned int _time;
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
	
	_swapChain		= GraphicsManager::getInstance()->createSwapChain();
	if ( nullptr == _swapChain )
	{
		return;
	}

	const RECT rect = getWindowRect();
	if ( false == _swapChain->initialize( _hwnd, rect.right - rect.left, rect.bottom - rect.top ) )
	{
		return;
	}

	Vertex list[] =
	{
		{-0.5f,-0.5f,0.0f,    -0.32f,-0.11f,0.0f,   0,0,0,  0,1,0 }, // POS1
		{-0.5f,0.5f,0.0f,     -0.11f,0.78f,0.0f,    1,1,0,  0,1,1 }, // POS2
		{ 0.5f,-0.5f,0.0f,     0.75f,-0.73f,0.0f,   0,0,1,  1,0,0 },// POS2
		{ 0.5f,0.5f,0.0f,      0.88f,0.77f,0.0f,    1,1,1,  0,0,1 }
	};

	_vertexBuffer	= GraphicsManager::getInstance()->createVertexBuffer();
	if ( nullptr == _vertexBuffer )
	{
		return;
	}

	const UINT listSize		= _ARRAYSIZE( list );

	void* shaderByteCode	= nullptr;
	size_t shaderSize		= 0;
	GraphicsManager::getInstance()->compileVertexShader( L"./VertexShader.hlsl", "vsmain", &shaderByteCode, &shaderSize );
	_vertexShader = GraphicsManager::getInstance()->createVertexShader( shaderByteCode, shaderSize );
	_vertexBuffer->load( list, sizeof( Vertex ), listSize, shaderByteCode, shaderSize );

	GraphicsManager::getInstance()->releaseCompiledShader();

	GraphicsManager::getInstance()->compilePixelShader( L"./PixelShader.hlsl", "psmain", &shaderByteCode, &shaderSize );
	
	_pixelShader = GraphicsManager::getInstance()->createPixelShader( shaderByteCode, shaderSize );
	_vertexBuffer->load( list, sizeof( Vertex ), listSize, shaderByteCode, shaderSize );

	GraphicsManager::getInstance()->releaseCompiledShader();

	Constant constant;
	constant._time = 0;

	_constantBuffer = GraphicsManager::getInstance()->createConstantBuffer();
	_constantBuffer->load( &constant, sizeof( constant ) );
}

void WindowApplicationManager::onUpdate( void ) noexcept
{
	Window::onUpdate();
	GraphicsManager::getInstance()->getDeviceContext()->clearRenderTargetColor( _swapChain, 0, 0.3f, 0.4f, 1 );
	
	const RECT rc = getWindowRect();
	GraphicsManager::getInstance()->getDeviceContext()->setViewportSize( rc.right - rc.left, rc.bottom - rc.top );

	Constant constant;
	constant._time = ::GetTickCount();

	_constantBuffer->update( GraphicsManager::getInstance()->getDeviceContext(), &constant );

	GraphicsManager::getInstance()->getDeviceContext()->setConstantBuffer( _vertexShader, _constantBuffer );
	GraphicsManager::getInstance()->getDeviceContext()->setConstantBuffer( _pixelShader, _constantBuffer );

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
	_constantBuffer->release();
	_vertexShader->release();
	_pixelShader->release();

	GraphicsManager::getInstance()->release();
}