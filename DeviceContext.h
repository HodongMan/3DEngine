#pragma once

class SwapChain;
class VertexBuffer;
class ConstantBuffer;
class VertexShader;
class PixelShader;


class DeviceContext
{
public:

	DeviceContext( ID3D11DeviceContext* deviceContext );
	~DeviceContext( void );


	bool						clearRenderTargetColor( SwapChain* swapChain, const float red, const float green, const float blue, const float alpha ) noexcept;

	bool						setVertexBuffer( const VertexBuffer* vertexBuffer ) noexcept;
	void						drawTriangleList( const UINT vertexCount, const UINT vertexIndex ) noexcept;
	void						drawTriangleStrip( const UINT vertexCount, const UINT vertexIndex ) noexcept;
	void						setViewportSize( const UINT width, const UINT height ) noexcept;

	void						setVertexShader( const VertexShader* vertexShader ) noexcept;
	void						setPixelShader( const PixelShader* pixelShader ) noexcept;

	void						setConstantBuffer( const VertexShader* vertexShader, const ConstantBuffer* buffer ) noexcept;
	void						setConstantBuffer( const PixelShader* pixelShader, const ConstantBuffer* buffer ) noexcept;

	bool						release( void ) noexcept;

private:

	ID3D11DeviceContext*		_deviceContext;

	friend class ConstantBuffer;
};