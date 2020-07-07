#pragma once

#include "Window.h"

class SwapChain;
class VertexBuffer;
class ConstantBuffer;
class IndexBuffer;
class VertexShader;
class PixelShader;


class WindowApplicationManager : public Window
{
public:

	WindowApplicationManager( void );
	virtual ~WindowApplicationManager( void );

	void				updateQuadPosition( void ) noexcept;

	virtual	void		onCreate( void ) noexcept override;
	virtual void		onUpdate( void ) noexcept override;
	virtual void		onDestroy( void ) noexcept override;

private:
	SwapChain*			_swapChain;
	VertexBuffer*		_vertexBuffer;
	VertexShader*		_vertexShader;
	PixelShader*		_pixelShader;
	ConstantBuffer*		_constantBuffer;
	IndexBuffer*		_indexBuffer;

	long				_oldDelta;
	long				_newDelta;
	
	float				_deltaTime;
	float				_deltaPos;
	float				_deltaScale;
	float				_deltaRotation;
};