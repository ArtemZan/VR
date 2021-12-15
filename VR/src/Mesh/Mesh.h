#pragma once

namespace VR {



	class Mesh {
	protected:
		Mesh();


		std::shared_ptr<MeshContainer> m_mesh;

		MeshContainer* const Get() { return m_mesh.get(); }
		const MeshContainer* const Get() const { return m_mesh.get(); };

	public:
		inline MeshContainer* const operator->() { return Get(); }
		inline const MeshContainer* const operator->() const { return Get(); }

		inline const Mesh& Clone() { return Mesh(); }
	};


	struct Mesh2D : public Mesh {
	public:
		Mesh2D();

		Mesh2D(const Mesh2D& mesh);

		Mesh2D(const Mesh2DContainer& mesh);

		Mesh2D(const Material2D& material, const Geometry2D& geometry);

		Mesh2D(const Geometry2D& geometry);

		inline const Mesh2D& Clone() { return Mesh2D(*Get()); }


		inline Mesh2DContainer* const operator->() { return Get(); }
		inline const Mesh2DContainer* const operator->() const { return Get(); }

	protected:
		inline Mesh2DContainer* const Get() { return (Mesh2DContainer*)m_mesh.get(); }
		inline const Mesh2DContainer* const Get() const { return (Mesh2DContainer*)m_mesh.get(); }
	};


	struct Mesh3D : public Mesh {
	public:
		Mesh3D();

		Mesh3D(const Mesh3D& mesh);

		Mesh3D(const Mesh3DContainer& mesh);

		inline const Mesh3D& Clone() { return Mesh3D(*Get()); }


		inline Mesh3DContainer* const operator->() { return Get(); }
		inline const Mesh3DContainer* const operator->() const { return Get(); }

	protected:
		inline Mesh3DContainer* const Get() { return (Mesh3DContainer*)m_mesh.get(); }
		inline const Mesh3DContainer* const Get() const { return (Mesh3DContainer*)m_mesh.get(); }
	};


	struct Mesh3DLambert final : public Mesh3D
	{
		Mesh3DLambert()
			:Mesh3D(Mesh3DContainer(Material3DLambert()))
		{

		}
	};

	struct Mesh3DColor final : public Mesh3D
	{
		Mesh3DColor()
			:Mesh3D(Mesh3DContainer(Material3DColor()))
		{

		}
	};
}