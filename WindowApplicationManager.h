#pragma once

#include "Window.h"

class SwapChain;


class WindowApplicationManager : public Window
{
public:

	WindowApplicationManager( void );
	virtual ~WindowApplicationManager( void );

	virtual	void		onCreate( void ) noexcept override;
	virtual void		onUpdate( void ) noexcept override;
	virtual void		onDestroy( void ) noexcept override;

private:
	SwapChain*			_swapChain;
};