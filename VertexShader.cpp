#include "pch.h"

#include "VertexShader.h"
#include "GraphicsManager.h"


VertexShader::VertexShader( void )
	: _vertexShader{ nullptr }
{

}

VertexShader::~VertexShader( void )
{

}

void VertexShader::release( void ) noexcept
{
	_vertexShader->Release();
}

bool VertexShader::initialize( const void * shaderByteCode, const size_t shaderByteCodeSize ) noexcept
{
	if( FAILED( GraphicsManager::getInstance()->_device->CreateVertexShader( shaderByteCode, shaderByteCodeSize, nullptr, &_vertexShader ) ) )
	{
		return false;
	}

	return true;
}
