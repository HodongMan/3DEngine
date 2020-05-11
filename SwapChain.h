#pragma once


class DeviceContext;


class SwapChain
{
public:

	SwapChain( void );
	~SwapChain( void );

	bool					initialize( HWND hwnd, const UINT width, const UINT height ) noexcept;
	bool					release( void ) noexcept;

	bool					present( const bool async ) noexcept;

private:
	IDXGISwapChain*			_swapChain;
	ID3D11RenderTargetView* _renderTargetView;
	ID3D11DepthStencilView* _depthStancilView;

	friend class DeviceContext;
};