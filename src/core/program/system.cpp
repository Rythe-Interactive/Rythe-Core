#include "system.hpp"

namespace rythe::core
{
    process_chain_builder process_graph::create_process_chain([[maybe_unused]] rsl::string_view processChainName)
    {
        process_chain_builder result{};
        result.m_processGraph = { this };
        return result;
    }

    process_chain_handle process_graph::find_process_chain([[maybe_unused]] rsl::string_view processChainName)
    {
        return process_chain_handle();
    }

    process_hook_handle process_graph::find_process_hook([[maybe_unused]] const process_hook_description& description)
    {
        return process_hook_handle();
    }
}
