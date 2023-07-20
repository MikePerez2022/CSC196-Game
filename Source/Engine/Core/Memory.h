#pragma once
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#include <memory>

#ifdef _DEBUG
#define DEBUG_NEW   new( _CLIENT_BLOCK, __FILE__, __LINE__)
#define new DEBUG_NEW
#endif // _DEBUG

namespace jojo
{
	class MemoryTracker
	{
	public:
		static bool Initialize();
		static void DisplayInfo();
	};
}

//namespace jojo
//{
//	struct MemoryAllocation
//	{
//		void* address;
//		size_t size;
//		MemoryAllocation* next;
//	};
//
//	class MemoryTracker
//	{
//	public:
//		void add(void* address, size_t size);
//		void remove(void* address, size_t size);
//
//		void DisplayInfo();
//
//	private:
//		size_t m_bytesAllocated = 0;
//		size_t m_numAllocations = 0;
//
//	};
//
//	extern MemoryTracker g_memoryTracker;
//}

