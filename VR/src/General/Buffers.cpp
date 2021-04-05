#include "pch.h"
#include "Buffers.h"

VR::UlsDynamicBuffer::UlsDynamicBuffer(size_t size)
	:m_size(size), m_data(new uint8_t[size])
{
}

void VR::UlsDynamicBuffer::Reserve(size_t new_capacity)
{
	uint8_t* src = m_data;
	m_data = new uint8_t[new_capacity];
	memcpy(m_data, src, m_size);
	delete[] src;
	m_size = new_capacity;
}
