#pragma once
#include <Defs.hpp>

namespace Game{
    class IBuffer{

        public:
            IBuffer(void);
            ~IBuffer(void);

            void SetData(void* data , u32 size);

            void Bind(void) const;
            void Unbind(void) const;

        private:
            u32     m_BufferId;
            void*   m_Data;
            u32     m_Size;
            

    };
}