#pragma once

#include "pch.h"


class Window
{
public:

	Window( void );
	virtual ~Window( void );

	bool			init( void ) noexcept;
	bool			release( void ) noexcept;
	void			broadcast( void ) noexcept;

	bool			isValid( void ) const noexcept;

	virtual void	onCreate( void ) noexcept;
	virtual void	onUpdate( void ) noexcept;
	virtual void	onDestroy( void ) noexcept;

	RECT			getWindowRect( void ) const noexcept;
	void			setHWND( HWND hwnd ) noexcept;

protected:

	HWND _hwnd;
	bool _isValid;
};