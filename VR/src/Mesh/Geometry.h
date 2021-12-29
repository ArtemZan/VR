#pragma once
#include "GeometryData.h"

namespace VR
{
	struct Geometry : Object {
		struct AttribsPos
		{
			int8_t color = -1;
			int8_t pos = -1;
			int8_t normal = -1;
		};

		struct AttribsOffsets
		{
			int8_t color = -1;
			int8_t pos = -1;
			int8_t normal = -1;
		};

		struct Props
		{
			uint8_t textureId;
			AttribsPos attribsPos;
			AttribsOffsets attribsOffsets;
			int vertexSize;
			bool _3d;
		};


	private:
		static std::vector<gl::AttribLayout> layouts;

		size_t m_layoutId = 0;

		Props m_props;
	protected:

	public:
		std::unique_ptr<GeometryData> m_data;

		Geometry(const gl::AttribLayout& layout = {});

		Geometry(const Geometry& geo);

		~Geometry();

		Geometry& operator=(const Geometry& geometry);

	private:
		int FindLayout(const gl::AttribLayout& path);

	public:

		void SetLayout(const gl::AttribLayout& layout);

		inline const gl::AttribLayout& GetLayout() const { return layouts[m_layoutId]; }

		template<typename ValueT>
		inline void PushAttrib(size_t count) {
			layouts[m_layoutId].Push<ValueT>(count);
			m_props.vertexSize += sizeof(ValueT) * count;
		} //To do: check for repeating layouts

		inline size_t GetVertexSize() const { return m_props.vertexSize; }//layouts[m_layoutId].GetStride(); }


		bool SetColorOffset(size_t pos);

		bool SetPosOffset(size_t pos);

		bool SetNormalOffset(size_t pos);

#ifdef DEBUG
#define TRY_TO_GET_OFFSET(data) 										   \
	if (m_props.attribsOffsets.data == -1)								   \
	{																	   \
		std::cout << "Error: " << #data << " offset hasn't been set\n";	   \
		return -1;														   \
	}																	   \
	return m_props.attribsOffsets.data;
#else
#define TRY_TO_GET_OFFSET(data) props.attribsOffsets.data;
#endif

		inline int GetColorOffset() const { TRY_TO_GET_OFFSET(color); }

		inline int GetPosOffset() const { TRY_TO_GET_OFFSET(pos); }

		inline int GetNormalOffset() const { TRY_TO_GET_OFFSET(normal); }


		inline bool HasNormals() const { return m_props.attribsPos.normal != int8_t(-1); }

		inline bool Is3D() const { return m_props._3d; }

	protected:
		template <typename T>
		inline const T& GetData(size_t vertex, size_t attrib_offset) const { return *(T*)(m_data->VertData(vertex * GetVertexSize() + attrib_offset)); }

		template <typename T>
		inline void SetData(size_t vertex, size_t attrib_offset, const T& data) { *(T*)(m_data->VertData(vertex * GetVertexSize() + attrib_offset)) = data; }


		inline const math::vec4& GetColor(size_t vertex) const { return GetData<math::vec4>(vertex, GetColorOffset()); }
		inline void SetColor(size_t vertex, const math::vec4& color) { SetData(vertex, GetColorOffset(), color); }

	public:
		void SetColor(const math::vec4& color);

		virtual void Transform(const math::mat3f& transform) = 0;
	};


	class Geometry2D : public Geometry, public Object2D
	{
		math::vec2 m_pos;
		math::vec2 m_scale;

	public:
		Geometry2D();

		Geometry2D(const Geometry2D& geometry);

		Geometry2D& operator=(const Geometry2D& geometry);

		void CreateRect(const math::vec2& size);

		void CreateLine(const math::vec2& start, const math::vec2& end, float width, float border_radius, size_t border_sections);

		void CreateLine(float length, float width, float border_radius, size_t border_sections);

		void CreateShape(const uint8_t* vertices, size_t vert_size, gl::AttribLayout input_layout, const uint32_t* indices, size_t ind_count);



		const math::vec2& GetPos() const override { return m_pos; }

		void SetPos(const math::vec2& new_pos) override;

		const math::vec2& GetScale() const override { return m_scale; }

		void SetScale(const math::vec2& new_scale) override;

		void Rotate(const math::vec2& center, float angle);


		inline const math::vec2& GetPos(size_t vertex) const { return GetData<math::vec2>(vertex, GetPosOffset()); }
		inline void SetPos(size_t vertex, const math::vec2& pos) { SetData(vertex, GetPosOffset(), pos); }


		void Transform(const math::mat2f& transform);

		void Transform(const math::mat3f& transform) override;
	};

	class Geometry3D : public Geometry, public Object3D {
		math::vec3 m_pos;
		math::vec3 m_scale;

	public:
		Geometry3D();

		Geometry3D& operator=(const Geometry3D& geometry);

		void CreateBox(const math::vec3& size);


		const math::vec3& GetPos() const override { return m_pos; }

		void SetPos(const math::vec3& new_pos) override;

		const math::vec3& GetScale() const override { return m_scale; }

		void SetScale(const math::vec3& new_scale) override;


		inline const math::vec3& GetPos(size_t vertex) const { return GetData<math::vec3>(vertex, GetPosOffset()); }
		inline void SetPos(size_t vertex, const math::vec3& pos) { SetData(vertex, GetPosOffset(), pos); }

		inline const math::vec3& GetNormal(size_t vertex) { return GetData<math::vec3>(vertex, GetNormalOffset()); }
		inline void SetNormal(size_t vertex, const math::vec3& normal) { SetData(vertex, GetNormalOffset(), normal); }

		void ShadeSmooth(float distance_threshold);

		void Transform(const math::mat3f& transform) override;

		void Transform(const math::mat4f& transform);

	};


	struct Geometry2DColor : public Geometry2D{
		Geometry2DColor();
	};


	struct GeometryWithNormals : public Geometry3D {
		GeometryWithNormals();
	};

}
