#include "pch.h"

#include "WindowApplicationManager.h"
#include "GraphicsManager.h"
#include "SwapChain.h"
#include "DeviceContext.h"


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

	RECT rect = getWindowRect();

	_swapChain->initialize( _hwnd, rect.right - rect.left, rect.bottom - rect.top );

}

void WindowApplicationManager::onUpdate( void ) noexcept
{
	Window::onUpdate();
	GraphicsManager::getInstance()->getDeviceContext()->clearRenderTargetColor( _swapChain, 1, 0, 1, 1 );

	_swapChain->present( false );
}

void WindowApplicationManager::onDestroy( void ) noexcept
{
	Window::onDestroy();

	GraphicsManager::getInstance()->release();
}