#pragma once


class SwapChain;
class DeviceContext;


class GraphicsManager
{
public:
	~GraphicsManager( void );

	bool					initialize( void ) noexcept;
	bool					release( void ) noexcept;

	static GraphicsManager& getInstance( void ) noexcept;

private:
	GraphicsManager( void );

private:
	ID3D11Device*			_d3dDevice;
	D3D_FEATURE_LEVEL		_featureLevel;
	ID3D11DeviceContext*	_deviceContext;
};