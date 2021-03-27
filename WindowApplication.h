#pragma once

#include "Window.h"


class WindowApplication : public Window
{
public:
	WindowApplication( void );
	virtual ~WindowApplication( void );

	virtual void onCreate( void ) noexcept override;
	virtual void onUpdate( void ) noexcept override;
	virtual void onDestroy( void ) noexcept override;
};