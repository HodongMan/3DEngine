#include "pch.h"

#include "PixelShader.h"
#include "GraphicsManager.h"

PixelShader::PixelShader( void )
	: _pixelShader{ nullptr }
{

}

PixelShader::~PixelShader(void)
{

}

bool PixelShader::initialize( const void * shaderByteCode, const size_t shaderByteCodeSize ) noexcept
{
	if( FAILED( GraphicsManager::getInstance()->_device->CreatePixelShader( shaderByteCode, shaderByteCodeSize, nullptr, &_pixelShader ) ) )
	{
		return false;
	}

	return true;
}

void PixelShader::release( void ) noexcept
{
	_pixelShader->Release();
}
