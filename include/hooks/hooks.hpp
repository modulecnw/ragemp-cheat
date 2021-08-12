#pragma once
#include "imports.hpp"
#include "virtual-table.hpp"
#include <memory/scanner.hpp>
#include <memory/memory.hpp>


using namespace std;
class Hooks : public Singleton<Hooks>
{
private:
    void Thread();
public:
    std::unique_ptr<hooks::virtual_table_hook> vthDirectHook;
    Memory::script_thread_tick_t original_native_thread = nullptr;
    bool MH_Initialized = false;

    void Render();
    void Initialize();
};