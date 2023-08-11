#pragma once
#include <random>

#include "../../defines.hpp"
#include "../../util/primitives.hpp"

namespace rsl::math
{
    class random_number_engine_base
    {
    public:
        virtual ~random_number_engine_base() = default;
        virtual void seed(size_type seed) noexcept = 0;
        virtual void seed(const std::seed_seq& seeds) noexcept = 0;
        [[nodiscard]] virtual uint_max generate() noexcept = 0;
        virtual void discard(size_type n) noexcept = 0;
    };

    template<typename Engine>
    class stl_random_engine : public random_number_engine_base
    {
        static thread_local Engine engine;

    public:
        virtual void seed(size_type seed) noexcept override { engine.seed(seed); };
        virtual void seed(const std::seed_seq& seeds) noexcept override { engine.seed(seeds); };
        [[nodiscard]] virtual uint_max generate() noexcept override { return engine(); };
        virtual void discard(size_type n) noexcept override { engine.discard(n); }
    };

    template<typename Engine>
    thread_local Engine stl_random_engine<Engine>::engine;

    class rythe_default_engine : public random_number_engine_base
    {
        static thread_local uint64 m_seed;

    public:
        virtual void seed(size_type seed) noexcept override;
        virtual void seed(const std::seed_seq& seeds) noexcept override;
        [[nodiscard]] virtual uint_max generate() noexcept override;
        virtual void discard(size_type n) noexcept override;
    };
}
