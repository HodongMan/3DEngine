#include "WindowApplicationManager.h"


int main( void )
{
	WindowApplicationManager manager;

	if ( false == manager.init() )
	{
		MessageBox( nullptr, "An error has occured", "An error has occured", MB_OK );
		return false;
	}

	while ( true == manager.isValid() )
	{
		manager.broadcast();
	}

	return 0;
}