#pragma once

namespace jojo
{
	struct MemoryAllocation
	{
		void* address;
		size_t size;
		MemoryAllocation* next;
	};

	class MemoryTracker
	{
	public:
		void add(void* address, size_t size);
		void remove(void* address, size_t size);

		void DisplayInfo();

	private:
		size_t m_bytesAllocated = 0;
		size_t m_numAllocations = 0;

	};

	extern MemoryTracker g_memoryTracker;
}

