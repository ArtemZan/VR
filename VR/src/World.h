#pragma once
class Renderer;

namespace VR
{
	class World
	{
	protected:
		World(Renderer* renderer);

		Scene scene;
		Renderer* renderer;
	};
}
