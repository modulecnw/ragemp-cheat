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
    void Native();
public:
    std::unique_ptr<hooks::virtual_table_hook> vthDirectHook;
    Memory::script_thread_tick_t original_native_thread = nullptr;
    uintptr_t original_entity_set_coords = 0;
    uintptr_t original_entity_set_rotation = 0;
    uintptr_t original_entity_set_velocity = 0;
    uintptr_t original_entity_set_fire = 0;

    void Render();
    void Initialize();
};