#pragma once


class SwapChain;
class DeviceContext;
class VertexBuffer;


class GraphicsManager
{
public:

	~GraphicsManager( void );

	bool					initialize( void ) noexcept;
	bool					release( void ) noexcept;

	static GraphicsManager* getInstance( void )  noexcept;

	SwapChain*				createSwapChain( void ) const noexcept;
	DeviceContext*			getDeviceContext( void ) const noexcept;
	VertexBuffer*			createVertexBuffer( void ) const noexcept;

	bool					createShaders( void ) noexcept;
	bool					setShaders( void ) noexcept;
	void					getShaderBufferAndSize( _Out_ void **bytecode, _Out_ UINT* size ) const noexcept;
private:
	GraphicsManager( void );

	friend class SwapChain;
	friend class VertexBuffer;

private:
	ID3D11Device*			_device;
	DeviceContext*			_deviceContext;

	IDXGIDevice*			_dxgiDevice;
	IDXGIAdapter*			_dxgiAdapter;
	IDXGIFactory*			_dxgiFactory;
	
	D3D_FEATURE_LEVEL		_featureLevel;

	ID3D11DeviceContext*	_d3d11DeviceContext;
	ID3DBlob*				_vsblob;
	ID3DBlob*				_psblob;
	ID3D11VertexShader*		_vertexShader;
	ID3D11PixelShader*		_pixelShader;
	
};
