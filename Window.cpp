#include "pch.h"

#include "Window.h"


Window::Window( void )
	: _hwnd( NULL )
	, _isValid( false )
{

}

Window::~Window( void )
{

}

LRESULT CALLBACK WndProc( HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam )
{
	switch ( message )
	{
	case WM_CREATE:
		{
			Window* window = reinterpret_cast<Window*>( ( ( LPCREATESTRUCT ) lparam )->lpCreateParams );
			SetWindowLongPtr( hwnd, GWLP_USERDATA, (LONG_PTR)window );

			window->onCreate();
		}
		break;

	case WM_DESTROY:
		{
			Window* window = reinterpret_cast<Window*>( GetWindowLongPtr( hwnd, GWLP_USERDATA ) );
			window->onDestroy();

			::PostQuitMessage( 0 );
		}
		break;
	default:
		return ::DefWindowProc( hwnd, message, wparam, lparam );
	}

	return NULL;
}

bool Window::initialize( void ) noexcept
{
	WNDCLASSEX wc;

	wc.cbClsExtra			= NULL;
	wc.cbSize				= sizeof( WNDCLASSEX );
	wc.cbWndExtra			= NULL;
	wc.hbrBackground		= reinterpret_cast<HBRUSH>( COLOR_WINDOW );
	wc.hCursor				= LoadCursor( NULL, IDC_ARROW );
	wc.hIcon				= LoadIcon( NULL, IDI_APPLICATION );
	wc.hIconSm				= LoadIcon( NULL, IDI_APPLICATION );
	wc.hInstance			= NULL;
	wc.lpszClassName		= "MyWindowClass";
	wc.lpszMenuName			= "";
	wc.style				= NULL;
	wc.lpfnWndProc			= &WndProc;

	if ( false == ::RegisterClassEx( &wc ) )
	{
		return false;
	}

	_hwnd = ::CreateWindowEx( WS_EX_OVERLAPPEDWINDOW, "MyWindowClass", "HodongApplication", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 1024, 768, NULL, NULL, NULL, this );
	if ( NULL == _hwnd )
	{
		return false;
	}

	::ShowWindow( _hwnd, SW_SHOW );
	::UpdateWindow( _hwnd );


	_isValid = true;

	return true;
}

bool Window::broadcast( void ) noexcept
{
	MSG msg;


	while ( 0 < ::PeekMessage( &msg, NULL, 0, 0, PM_REMOVE ) )
	{
		::TranslateMessage( &msg );
		::DispatchMessage( &msg );
	}

	onUpdate();
	Sleep( 1 );

	return true;
}

bool Window::release( void ) noexcept
{
	if ( false == ::DestroyWindow( _hwnd ) )
	{
		return false;
	}

	return true;
}

bool Window::isValid( void ) const noexcept
{
	return _isValid;
}
