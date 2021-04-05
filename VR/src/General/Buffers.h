#pragma once

//These buffers are usually used to keep and fill vertices. 
//Need of these buffers is due to the need to change certain
//amount of bytes in buffer

namespace VR
{
    template<int SIZE>
    class UlsStaticBuffer
    {
    public:
        template<typename DataT>
        inline void Add(const DataT& data)
        {
            static_assert(std::is_standard_layout<DataT>(), "Cannot add data with non-standart layout to StaticBuffer");

            if (sizeof(data) + m_iter > SIZE)
                assert("VR::StaticBuffer subscript out of range");
            *(DataT*)(m_data + m_iter) = data;
            m_iter += sizeof(data);
        }

        template<typename DataT>
        inline void Repeat(const DataT& data, size_t period, size_t offset = 0)
        {
            static_assert(std::is_standard_layout<DataT>(), "Cannot add data with non-standart layout to StaticBuffer");
            for (int i = offset; i + sizeof(data) <= SIZE; i+= period)
            {
                *(DataT*)(m_data + i) = data;
            }
        }

        inline uint8_t* Get() { return m_data; }

        inline void Skip(size_t bytes) { m_iter += bytes; }

    private:
        uint8_t m_data[SIZE];
        size_t m_iter = 0;
    };


    class UlsDynamicBuffer
    {
    public:
        UlsDynamicBuffer(size_t size = 0);

        template<typename DataT>
        inline void Add(const DataT& data)
        {
            static_assert(std::is_standard_layout<DataT>(), "Cannot add data with non-standart layout to DynamicBuffer");

            if (sizeof(data) + m_iter > m_size)
                assert("VR::DynamicBuffer subscript out of range");
            *(DataT*)(m_data + m_iter) = data;
            m_iter += sizeof(data);
        }

        template<typename DataT>
        inline void Repeat(const DataT& data, size_t period, size_t offset = 0)
        {
            static_assert(std::is_standard_layout<DataT>(), "Cannot add data with non-standart layout to DynamicBuffer");

            for (int i = offset; i + sizeof(data) <= m_size; i += period)
            {
                *(DataT*)(m_data + i) = data;
            }
        }

        inline uint8_t* Get() { return m_data; }

        void Reserve(size_t new_capacity);

        inline void Skip(size_t bytes) { m_iter += bytes; }

    private:
        uint8_t* m_data;
        size_t m_size = 0;
        size_t m_iter = 0;
    };
}