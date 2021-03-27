#pragma once

#include "pch.h"

class Window
{
public:
	Window( void );
	virtual ~Window( void );

	bool			initialize( void ) noexcept;
	bool			broadcast( void ) noexcept;
	
	bool			release( void ) noexcept;
	bool			isValid( void ) const noexcept;

	virtual void	onCreate( void ) noexcept = 0;
	virtual void	onUpdate( void ) noexcept = 0;
	virtual void	onDestroy( void ) noexcept = 0;

protected:
	HWND			_hwnd;
	bool			_isValid;
};