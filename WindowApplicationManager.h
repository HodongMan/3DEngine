#pragma once

#include "Window.h"


class WindowApplicationManager : public Window
{
public:

	WindowApplicationManager( void );
	virtual ~WindowApplicationManager( void );

	virtual	void		onCreate( void ) noexcept override;
	virtual void		onUpdate( void ) noexcept override;
	virtual void		onDestroy( void ) noexcept override;
};