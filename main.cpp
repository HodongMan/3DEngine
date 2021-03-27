#include "WindowApplication.h"


int main()
{
	WindowApplication application;
	if ( true == application.initialize())
	{
		while ( true == application.isValid() )
		{
			application.broadcast();
		}
	}

}