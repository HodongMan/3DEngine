#include "Window.h"


LRESULT CALLBACK WndProc( HWND hwnd, UINT msg,  WPARAM wParam, LPARAM lParam )
{
	switch ( msg )
	{
	case WM_CREATE:
		{
			auto* const params = reinterpret_cast< LPCREATESTRUCT >( lParam );
			auto* const window = reinterpret_cast< Window* const >( params->lpCreateParams );

			SetWindowLongPtr( hwnd, GWLP_USERDATA, reinterpret_cast< LONG_PTR >( window ) );
			
			window->setHWND( hwnd );
			window->onCreate();	
		}
		break;
	case WM_DESTROY:
		{
			auto* const window = reinterpret_cast< Window* const >( GetWindowLongPtr( hwnd, GWLP_USERDATA ) );
			window->onDestroy();
			PostQuitMessage( 0 );
		}
		break;
	default:
		{
			return DefWindowProc( hwnd, msg, wParam, lParam );
		}
		break;
	}

	return NULL;
}

Window::Window( void )
	: _isValid { false }
{

}

Window::~Window( void )
{
	DestroyWindow( _hwnd ); 
}

bool Window::init( void ) noexcept
{
	WNDCLASSEX wc{};

	wc.cbSize			= sizeof( WNDCLASSEX );
	wc.hbrBackground	= ( HBRUSH )COLOR_WINDOW;
	wc.hCursor			= LoadCursor( NULL, IDC_ARROW );
	wc.hIcon			= LoadIcon( NULL, IDI_APPLICATION );
	wc.hIconSm			= LoadIcon( NULL, IDI_APPLICATION );
	wc.hInstance		= GetModuleHandle( nullptr );
	wc.lpszClassName	= L"3d Games";
	wc.lpfnWndProc		= &WndProc;

	wc.lpszMenuName		= L"";
	wc.style			= NULL;

	if ( false == RegisterClassEx( &wc ) )
	{
		return false;
	}

	RECT rect = { 0,0,1024,768 };
	AdjustWindowRectEx( &rect, WS_OVERLAPPEDWINDOW, FALSE, WS_EX_OVERLAPPEDWINDOW );

	const auto width	= rect.right - rect.left;
	const auto height	= rect.bottom - rect.top;

	_hwnd = CreateWindowEx( WS_EX_OVERLAPPEDWINDOW,
							L"3d Games", 
							L"3d Application", 
							WS_OVERLAPPEDWINDOW, 
							CW_USEDEFAULT, 
							CW_USEDEFAULT,
							width,
							height, 
							nullptr, 
							nullptr, 
							nullptr,
							this );

	if ( FAILED( _hwnd ) )
	{
		return false;
	}

	ShowWindow( _hwnd, SW_SHOW );
	
	_isValid = true;

	return true;
}

bool Window::release( void ) noexcept
{
	if ( _hwnd )
	{
		return DestroyWindow( _hwnd );
	}

	return true;
}

void Window::broadcast( void ) noexcept
{
	MSG message;

	onUpdate();

	while ( PeekMessage( &message, NULL, 0, 0, PM_REMOVE ) )
	{
		TranslateMessage( &message );
		DispatchMessage( &message );
	}
}

bool Window::isValid( void ) const noexcept
{
	return _isValid;
}

void Window::onCreate( void ) noexcept
{

}

void Window::onUpdate( void ) noexcept
{

}

void Window::onDestroy( void ) noexcept
{
	_isValid = false;
}

RECT Window::getWindowRect( void ) const noexcept
{
	RECT rect;
	GetClientRect( _hwnd, &rect );

	return rect;
}

void Window::setHWND( HWND hwnd ) noexcept
{
	_hwnd = hwnd;
}
