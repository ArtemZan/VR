#include "VR.h"
#include "Worlds/TestWorld.h"

using namespace VR;


int main()
{
	Context::Create(960, 540, "Hello world");

	VR::Renderer* renderer = new TestRenderer();
	renderer->Run();

	Context::Destroy();
}