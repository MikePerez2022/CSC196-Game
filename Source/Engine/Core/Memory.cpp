#include "Memory.h"
#include <iostream>

using namespace std;

kiko::MemoryTracker kiko::g_memoryTracker;

void* operator new (size_t size)
{
	void* p = malloc(size);

	kiko::g_memoryTracker.add(p, size);

	
	return p;
}

void operator delete (void* address, size_t size)
{
	kiko::g_memoryTracker.remove(address, size);

	free(address);

}

namespace kiko
{
	void kiko::MemoryTracker::add(void* address, size_t size)
	{
		m_bytesAllocated += size;
		m_numAllocations++;
	}

	void kiko::MemoryTracker::remove(void* address, size_t size)
	{
		m_bytesAllocated -= size;
		m_numAllocations--;
	}

	void kiko::MemoryTracker::DisplayInfo()
	{
		cout << "Current bytes allocated: " << m_bytesAllocated << endl;
		cout << "Current number allocations: " << m_numAllocations << endl;
	}
}


