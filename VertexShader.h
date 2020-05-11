#pragma once


class GraphicsManager;
class DeviceContext;


class VertexShader
{
public:
	VertexShader( void );
	~VertexShader( void );

	void			release( void ) noexcept;

private:

	bool			initialize( const void* shaderByteCode, const size_t shaderByteCodeSize ) noexcept;

	ID3D11VertexShader* _vertexShader;

	friend class GraphicsManager;
	friend class DeviceContext;
};