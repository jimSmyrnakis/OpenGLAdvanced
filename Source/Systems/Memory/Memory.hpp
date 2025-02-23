#pragma once

#include <Defs.hpp>

namespace Game{
    

    
    class MemoryManager{
        public:
            enum class MemFlags : u16 {
                Allocated  = 0x0001,
                HasNext    = 0x0002,
                FirstBlock = 0x0004,
                Shared     = 0x0008,
                CountMask  = 0xFFF0
                
            };
        public:
            MemoryManager(void);
            ~MemoryManager(void);

            void SetTotalSize(u64 size);
            /*Set total size of the memory pool that will be created */

            u64  GetFreeSpace(void);
            /*If the maximum size is given , it caculates how much free space will exist for user data 
              otherwise return's the actual size of free space*/
            u64  GetStructureSpace(void);
 
            void Create(void);

            void* Allocate(u64 size , bool Shared = false);

            void  Reference(void* ptr);
            void  Free(void* ptr);


        private:
            u16*  m_MemoryStructure ;
            u64   m_MemoryStructureSize;
            void* m_MemoryBegin     ;
            u64   m_AvailableMenory ;

    };
}