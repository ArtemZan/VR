#include "VR.h"
#include "Worlds/TestWorld.h"
#include "Worlds/TestWorld1.h"
#include "Worlds/Navigation.h"

using namespace VR;

int main()
{
	Context::Create(960, 540, "Hello world");	
	

	{
		Navigation nav;
		TestWorld testWorld;
		TestWorld1 testWorld1;
		nav.Run();

		int& link = nav.link;

		while (link != -1)
		{
			int l = link;
			link = -1;
			bool world_found = true;
			switch (l)
			{
			case 0:
				testWorld.Run();
				break;
			case 1:
				testWorld1.Run();
				break;
			default: world_found = false;
			}
			if (world_found && !glfwWindowShouldClose(Context::Get()->window))
			{
				nav.Run();
			}
		}
	}

	Context::Destroy();
}