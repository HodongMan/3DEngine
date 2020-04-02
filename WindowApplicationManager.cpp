#include "WindowApplicationManager.h"

WindowApplicationManager::WindowApplicationManager( void )
{

}

WindowApplicationManager::~WindowApplicationManager( void )
{

}

void WindowApplicationManager::onCreate( void ) noexcept
{
	Window::onCreate();
}

void WindowApplicationManager::onUpdate( void ) noexcept
{
	Window::onUpdate();
}

void WindowApplicationManager::onDestroy( void ) noexcept
{
	Window::onDestroy();
}