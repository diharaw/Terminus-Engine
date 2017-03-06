#pragma once

#ifndef STACKALLOCATOR_H
#define STACKALLOCATOR_H

#include <memory/allocator.h>

namespace terminus
{
    class StackAllocator : public Allocator
    {
    private:
        struct AllocationHeader
        {
            #ifdef _DEBUG
            void* m_PreviousAddress;
            #endif
            uint8 m_Adjustment;
        };
        
        #ifdef _DEBUG
        void* m_PreviousPosition;
        #endif
        void* m_CurrentPosition;
        
    public:
        StackAllocator(size_t _Size, void* _StartAddress);
        ~StackAllocator();
        void* Allocate(size_t _AllocationSize, uint8 _Alignment) override;
        void  Deallocate(void* _Address) override;
    };
}

#endif
