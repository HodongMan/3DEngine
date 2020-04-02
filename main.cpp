#include "WindowApplicationManager.h"


int main()
{
	WindowApplicationManager manager;

	if ( false == manager.init() )
	{
		MessageBox( nullptr, L"An error has occured", L"An error has occured", MB_OK );
		return false;
	}

	while ( true == manager.isValid() )
	{
		manager.broadcast();
	}

	return 0;
}