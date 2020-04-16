#pragma once


class SwapChain;
class DeviceContext;


class GraphicsManager
{
public:

	~GraphicsManager( void );

	bool					initialize( void ) noexcept;
	bool					release( void ) noexcept;

	static GraphicsManager* getInstance( void )  noexcept;

	SwapChain*				createSwapChain( void ) const noexcept;
	DeviceContext*			getDeviceContext( void ) const noexcept;

private:
	GraphicsManager( void );

	friend class SwapChain;

private:
	ID3D11Device*			_device;
	DeviceContext*			_deviceContext;

	IDXGIDevice*			_dxgiDevice;
	IDXGIAdapter*			_dxgiAdapter;
	IDXGIFactory*			_dxgiFactory;
	
	D3D_FEATURE_LEVEL		_featureLevel;
	
};
