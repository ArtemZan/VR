#include "pch.h"
#include "VR.h"
#include "Worlds/Monkeys.h"
//#include "Worlds/Collisions.h"
//#include "Worlds/TestWorld1.h"
#include "Worlds/Pendulum.h"
//#include "Worlds/Labyrinth.h"
#include "Worlds/Navigation.h"
//#include "Worlds/Gravitation.h"

using namespace VR;

int main()
{
	Context::Create(960, 540, "Hello world");	


	{
#define DEF_WORLD(CLASS) worlds.push_back(std::make_unique<CLASS>());

		std::vector<std::unique_ptr<World>> worlds;

		DEF_WORLD(Navigation);
		DEF_WORLD(Monkeys);
		//DEF_WORLD(Collisions);
		DEF_WORLD(Pendulum);

		//Navigation nav;
		//Monkeys monkeys;
		//TestWorld1 testWorld1;
		//Pendulum pendulum;
		//Labyrinth labyrinth;
		//Gravitation gravitation;
		
		size_t current_world = 0;
		while (current_world < worlds.size())
		{
			worlds[current_world]->Run();
			current_world = worlds[current_world]->GetLink();
		}
		//int link = nav.GetLink();

		//while (link != -1)
		//{
		//	switch (link)
		//	{
		//	case 1:
		//		//monkeys.Run();
		//		//link = monkeys.GetLink();
		//		break;
		//	case 2:
		//		collisions.Run();
		//		link = collisions.GetLink();
		//		break;
		//	case 3:
		//		//pendulum.Run();
		//		break;
		//	case 4:
		//		//labyrinth.Run();
		//		break;
		//	case 5:
		//		//gravitation.Run();
		//		break;
		//	default: 
		//		nav.Run();
		//		link = nav.GetLink();
		//	}
		//}
	}

	Context::Destroy();
}