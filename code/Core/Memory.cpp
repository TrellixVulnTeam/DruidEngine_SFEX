#include "Core/Memory.hpp"

SMap<SStr, i32> Memory::mAllocationsCounter;

void Memory::init()
{
}

void Memory::terminate()
{
    ECHO("-------- MEM SUMMARY --------")
    FOR_MAP(it, Memory::mAllocationsCounter)
    {
        std::cout << it->first << ": " << it->second << std::endl;
    }
    ECHO("-----------------------------")
}