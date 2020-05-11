#pragma once

class GraphicsManager;
class DeviceContext;


class PixelShader
{
public:
	PixelShader( void );
	~PixelShader( void );

	bool				initialize( const void* shaderByteCode, const size_t shaderByteCodeSize ) noexcept;
	void				release( void ) noexcept;

private:
	ID3D11PixelShader* _pixelShader;

	friend class GraphicsManager;
	friend class DeviceContext;
};