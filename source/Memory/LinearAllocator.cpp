#include "LinearAllocator.h"
#include "Assert.h"
#include "BasicTypes.h"

/*
 * https://en.wikipedia.org/wiki/Data_structure_alignment
 *
 *  ---- pseudo-code: computing padding ----
 * padding = (align - (offset mod align)) mod align
 * new offset = offset + padding = offset + (align - (offset mod align)) mod align
 */

namespace DE {

LinearAllocator::LinearAllocator() : Allocator(){

}

LinearAllocator::~LinearAllocator(){

}

void LinearAllocator::init(u32 size){
    Allocator::init(size);
}

void* LinearAllocator::allocate(u32 size){
    LinearAllocator::allocate(size, 1);
}

void* LinearAllocator::allocate(u32 size, u32 alignment){
    return Allocator::allocateAlignedAddress(mStart + Allocator::getAllocated(), size, alignment);
}

void LinearAllocator::free(const void* pointer){
    // ASSERT(false, "LinearAllocator can't use free(void* pointer), use reset().");
}

void LinearAllocator::reset(){
    Allocator::reset();
}

} /* namespace DE */
