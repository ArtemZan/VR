#include "VR.h"
#include "Worlds/SolarSystem.h"
#include "Worlds/TestWorld1.h"
#include "Worlds/Pendulum.h"
#include "Worlds/Labyrinth.h"
#include "Worlds/Navigation.h"

using namespace VR;

int main()
{
	Context::Create(960, 540, "Hello world");	


	{
		Navigation nav;
		SolarSystem solarSystem;
		TestWorld1 testWorld1;
		Pendulum pendulum;
		Labyrinth labyrinth;
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
				solarSystem.Run();
				break;
			case 1:
				testWorld1.Run();
				break;
			case 2:
				pendulum.Run();
				break;
			case 3:
				labyrinth.Run();
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