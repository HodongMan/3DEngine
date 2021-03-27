#include "pch.h"

#include "WindowApplication.h"


#include "GraphicsManager.h"


WindowApplication::WindowApplication( void )
{

}

WindowApplication::~WindowApplication( void )
{

}

void WindowApplication::onCreate( void ) noexcept
{
	GraphicsManager::getInstance().initialize();
}

void WindowApplication::onUpdate( void ) noexcept
{
	//Window::onUpdate();
}

void WindowApplication::onDestroy( void ) noexcept
{
	GraphicsManager::getInstance().release();

	_isValid = false;
}
