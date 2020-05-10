#pragma once

class SwapChain;
class VertexBuffer;

class DeviceContext
{
public:

	DeviceContext( ID3D11DeviceContext* deviceContext );
	~DeviceContext( void );


	bool						clearRenderTargetColor( SwapChain* swapChain, const float red, const float green, const float blue, const float alpha ) noexcept;
	bool						release( void ) noexcept;

	bool						setVertexBuffer( VertexBuffer* vertexBuffer ) noexcept;
	void						drawTriangleList( const UINT vertexCount, const UINT vertexIndex ) noexcept;
	void						setViewportSize( const UINT width, const UINT height ) noexcept;

private:

	ID3D11DeviceContext*		_deviceContext;
};