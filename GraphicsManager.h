#pragma once


class SwapChain;
class DeviceContext;
class VertexBuffer;
class ConstantBuffer;
class VertexShader;
class PixelShader;


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
	ConstantBuffer*			createConstantBuffer( void ) const noexcept;
	VertexShader*			createVertexShader( const void* shaderByteCode, const size_t shaderByteCodeSize ) noexcept;
	PixelShader*			createPixelShader( const void* shaderByteCode, const size_t shaderByteCodeSize ) noexcept;

	bool					compileVertexShader( const wchar_t* fileName, const char* entryPointName, _Out_ void** shaderByteCode, _Out_ size_t* shaderByteCodeSize ) noexcept;
	bool					compilePixelShader( const wchar_t* fileName, const char* entryPointName, _Out_ void** shaderByteCode, _Out_ size_t* shaderByteCodeSize ) noexcept;
	
	void					releaseCompiledShader( void ) noexcept;

private:
	GraphicsManager( void );

private:
	ID3D11Device*			_device;
	DeviceContext*			_deviceContext;
	D3D_FEATURE_LEVEL		_featureLevel;

	IDXGIDevice*			_dxgiDevice;
	IDXGIAdapter*			_dxgiAdapter;
	IDXGIFactory*			_dxgiFactory;
	ID3D11DeviceContext*	_d3d11DeviceContext;

	ID3DBlob*				_blob;
	ID3DBlob*				_vsblob;
	ID3DBlob*				_psblob;


	friend class SwapChain;
	friend class VertexBuffer;
	friend class ConstantBuffer;
	friend class VertexShader;
	friend class PixelShader;
};
