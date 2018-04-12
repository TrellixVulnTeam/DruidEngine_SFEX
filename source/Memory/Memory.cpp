#include "Memory.h"

namespace DE {

FreeListAllocator Memory::smGlobal;

Memory::Memory(){

}

Memory::~Memory(){

}

void Memory::init(){
    u32 GB = 1024*1024*1024;
    smGlobal.init(1*GB);
};

void Memory::init(const u32 size){
    smGlobal.init(size);
};

IAllocator& Memory::getGlobal(){
    return smGlobal;
}

void Memory::free(){
    smGlobal.reset();
}

} /* namespace DE */
