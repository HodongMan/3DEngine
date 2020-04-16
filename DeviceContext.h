#pragma once

class SwapChain;


class DeviceContext
{
public:

	DeviceContext( ID3D11DeviceContext* deviceContext );
	~DeviceContext( void );


	bool						clearRenderTargetColor( SwapChain* swapChain, const float red, const float green, const float blue, const float alpha ) noexcept;
	bool						release( void ) noexcept;

private:

	ID3D11DeviceContext*		_deviceContext;
};