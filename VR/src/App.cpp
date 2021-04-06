#include "VR.h"
#include "Worlds/TestWorld.h"

using namespace VR;


int main()
{
	Context::Create(960, 540, "Hello world");

	{
		TestWorld testWorld;
		testWorld.Run();
	}

	Context::Destroy();
}