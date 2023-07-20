#include "Memory.h"
#include <iostream>

using namespace std;

namespace jojo
{
	bool MemoryTracker::Initialize()
	{
		_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

		return true;
	}

	void MemoryTracker::DisplayInfo()
	{
		_CrtMemDumpAllObjectsSince(NULL);
	}
}


//
//
//inline void* operator new (size_t size)
//{
//	
//	void* p = std::malloc(size);
//
//	jojo::g_memoryTracker.add(p, size);
//
//		
//	return p;
//}
//
//inline void operator delete (void* address, size_t size)
//{
//	jojo::g_memoryTracker.remove(address, size);
//
//	std::free(address);
//
//}
//
//namespace jojo
//{
//	MemoryTracker g_memoryTracker;
//
//	void jojo::MemoryTracker::add(void* address, size_t size)
//	{
//		m_bytesAllocated += size;
//		m_numAllocations++;
//	}
//
//	void jojo::MemoryTracker::remove(void* address, size_t size)
//	{
//		m_bytesAllocated -= size;
//		m_numAllocations--;
//	}
//
//	void jojo::MemoryTracker::DisplayInfo()
//	{
//		cout << "Current bytes allocated: " << m_bytesAllocated << endl;
//		cout << "Current number allocations: " << m_numAllocations << endl;
//	}
//}


