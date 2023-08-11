#include "logger.hpp"

#include <chrono>

namespace rsl {

    const static inline std::chrono::time_point<std::chrono::high_resolution_clock> genesis = std::chrono::high_resolution_clock::now();

    void logger::genesis_formatter_flag::format([[maybe_unused]] const spdlog::details::log_msg& msg, [[maybe_unused]] const std::tm& tm_time, spdlog::memory_buf_t& dest)
    {
        //get seconds since engine start
        const auto time_since_genesis = std::chrono::high_resolution_clock::now() - genesis;
        const auto seconds = std::chrono::duration_cast<std::chrono::duration<float32, std::ratio<1, 1>>>(time_since_genesis).count();

        //convert to "--s.ms---"
        const auto str = std::to_string(seconds);

        //append to data
        dest.append(str.data(), str.data() + str.size());
    }
}
