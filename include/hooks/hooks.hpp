#pragma once
#include "imports.hpp"
#include "virtual-table.hpp"
#include <memory/scanner.hpp>
#include <memory/memory.hpp>


using namespace std;
class Hooks : public Singleton<Hooks>
{
private:
    void Render();
public:
    std::unique_ptr<hooks::virtual_table_hook> vthDirectHook;

    void Initialize();
};