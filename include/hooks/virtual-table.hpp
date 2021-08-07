#pragma once
#include <Windows.h>
#include <cstddef>
#include <memory>

namespace hooks
{
	class virtual_table_hook
	{
	public:
		explicit virtual_table_hook() noexcept { }

		explicit virtual_table_hook(std::string name, void* obj, std::size_t num_funcs) :
			m_object(static_cast<void***>(obj)),
			m_num_funcs(num_funcs + 1),
			m_name(name),
			m_original_table(*m_object),
			m_new_table(std::make_unique<void* []>(m_num_funcs))
		{
			std::copy_n(m_original_table - 1, m_num_funcs, m_new_table.get());
		}

		void operator=(virtual_table_hook vmt)
		{
			m_name = vmt.m_name;
			m_object = vmt.m_object;
			m_num_funcs = vmt.m_num_funcs;
			m_original_table = vmt.m_original_table;
			m_new_table = vmt.m_new_table;
		}

		~virtual_table_hook() noexcept
		{
			if (m_hooked)
				disable();

			m_new_table.reset();
		}

		void enable()
		{
			*m_object = m_new_table.get() + 1;
			m_hooked = true;

			Log::Debug(_xor_("[+] Hooks >>"), m_name, _xor_("enabled."));
		}

		void disable()
		{
			if (m_hooked)
			{
				m_hooked = false;
				*m_object = m_original_table;
			}
		}

		void attach(std::size_t index, void* func)
		{
			m_new_table[index + 1] = func;
		}

		void detach(std::size_t index)
		{
			m_new_table[index + 1] = m_original_table[index];
		}

		template<typename type>
		type fetch(type func, int index)
		{
			return static_cast<type>(m_original_table[index]);
		}

	private:
		bool						m_succeed_create = false;
		bool						m_hooked = false;
		std::string					m_name;

		void*** m_object;
		std::size_t					m_num_funcs;

		void** m_original_table;
		std::shared_ptr<void* []>	m_new_table;
	};
}