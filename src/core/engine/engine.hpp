#pragma once
#include <map>
#include <vector>
#include <memory>

#include <argh.h>

#include <rsl/type_util>
#include <rsl/logging>
#include <rsl/primitives>

#include "core/engine/module.hpp"
#include "core/async/spinlock.hpp"
#include "core/containers/pointer.hpp"

/**
 * @file engine.hpp
 */

namespace rythe::core
{
    namespace scheduling
    {
        class Scheduler;
    }

    class Engine;

    struct engine_id
    {
        friend class Engine;
    private:
        rsl::id_type m_id;

        engine_id(rsl::id_type id) noexcept : m_id(id) {}

    public:
        RULE_OF_5_NOEXCEPT(engine_id);

        rsl::id_type value() const noexcept { return m_id; }

        operator rsl::id_type() const noexcept { return m_id; }
    };

    template <class CharType, class TraitsType>
    std::basic_ostream<CharType, TraitsType>& operator<<(std::basic_ostream<CharType, TraitsType>& stream, engine_id id) {
        return stream << id.value();
    }

    struct this_engine
    {
        friend class Engine;
        friend class scheduling::Scheduler;
    private:
        thread_local static Engine* m_ptr;

    public:
        static pointer<Engine> get_context();
        static engine_id& id();
        static int& exit_code();
        static argh::parser& cliargs();

        static void restart();
        static void shutdown();
    };

    /**@class Engine
     * @brief Main top level engine abstraction.
     *        This class allows you to setup the engine with all the necessary modules and settings.
     *        This class also contains all the sub managers of the core systems.
     * @ref rythe::core::Module
     * @ref rythe::core::ecs::EcsRegistry
     * @ref rythe::core::scenes::SceneManager
     * @ref rythe::core::scheduling::Scheduler
     */
    class Engine
    {
        friend class rythe::core::scheduling::Scheduler;
    private:
        std::map<rsl::priority_type, std::vector<std::unique_ptr<Module>>, std::greater<>> m_modules;

        std::atomic_bool m_shouldRestart;

        static rsl::size_type m_initializedInstances;
        static async::spinlock m_startupShutdownLock;

        static rsl::id_type generateId();

        [[nodiscard]] static rsl::multicast_delegate<void()>& initializationSequence();
        [[nodiscard]] static rsl::multicast_delegate<void()>& shutdownSequence();

        void shutdownModules();

    public:
        template<typename Func>
        static rsl::byte subscribeToInit(Func&& func);
        template<typename Func>
        static rsl::byte subscribeToShutdown(Func&& func);

        template<typename SubSystem>
        static rsl::byte reportSubSystem();

        engine_id id;

        int exitCode;

        argh::parser cliargs;

        Engine(int argc, char** argv);
        Engine();

        Engine(Engine&&);
        Engine& operator=(Engine&&);

        ~Engine() = default;

        void makeCurrentContext();

        /**@brief Reports an engine module.
         * @tparam ModuleType The module you want to report.
         * @param args The arguments you want to pass to the module constructor.
         * @ref rythe::core::Module
         */
        template <typename ModuleType, typename... Args, rsl::inherits_from<ModuleType, Module> = 0>
        void reportModule(Args&&...args);

        void initialize();
        void uninitialize();

        /**@brief Runs engine loop.
         */
        void run(bool low_power = false, rsl::uint minThreads = 0);

        void restart();

        void shutdown();
    };

#define OnEngineInit(Type, Func) RYTHE_ANON_VAR(rsl::byte, RYTHE_CONCAT(_onInit_, Type)) = rythe::core::Engine::subscribeToInit(Func);
#define OnEngineShutdown(Type, Func) RYTHE_ANON_VAR(rsl::byte, RYTHE_CONCAT(_onShutdown_, Type)) = rythe::core::Engine::subscribeToShutdown(Func);

#define ReportSubSystem(Type) RYTHE_ANON_VAR(rsl::byte, RYTHE_CONCAT(_reportSubSystem_, Type)) = rythe::core::Engine::reportSubSystem<Type>();

}

namespace fmt
{
    template <>
    struct formatter<rythe::core::engine_id>
    {

        constexpr const char* parse(format_parse_context& ctx)
        {
            auto it = ctx.begin(), end = ctx.end();

            if (!it)
                return nullptr;

            if (it != end && *it != '}')
                throw format_error("invalid format");
            return it++;
        }

        template <typename FormatContext>
        auto format(const rythe::core::engine_id& id, FormatContext& ctx)
        {
            return format_to(ctx.out(), "{}", id.value());
        }

    };
}

#include <core/engine/engine.inl>
