#pragma once
#include <unordered_map>
#include <vector>
#include <memory>

#include <rsl/primitives>
#include <rsl/logging>

namespace rythe::core
{
    class Program;

    class Engine
    {
    private:
        Program* programPtr = nullptr;
        rsl::id_type engineId = 0;
    public:
        Engine(rsl::id_type id) : engineId(id) {}

        void setup(Program* ptr)
        {
            rsl::log::debug("Engine[{}] Instance initialized", engineId);
            programPtr = ptr;
        }

        void update()
        {
            rsl::log::debug("Engine[{}] Update", engineId);
        }

        void shutdown()
        {
            rsl::log::debug("Engine[{}] Shutdown", engineId);
        }
    };

    class Program
    {
    private:
        std::unordered_map<rsl::id_type, std::unique_ptr<Engine>> m_engines;
        rsl::id_type m_lastIdx = 0;
        bool m_running = false;
    public:
        void initialize()
        {
            rsl::log::debug("Initializing Program Instance");
            for (auto& [id, engine] : m_engines)
            {
                engine->setup(this);
            }
            m_running = true;
        }

        void update()
        {
            //In the final version the updates will be handled by a process chain
            rsl::log::debug("Program Update");
            for (auto& [id, engine] : m_engines)
            {
                engine->update();
            }
        }

        void shutdown()
        {
            rsl::log::debug("Program Shutdown");
            for (auto& [id, engine] : m_engines)
            {
                engine->shutdown();
            }
        }

        bool isRunning()
        {
            return m_running;
        }

        void stop()
        {
            m_running = false;
        }

        void addEngineInstance()
        {
            m_engines.emplace(m_lastIdx, std::make_unique<Engine>(Engine{ m_lastIdx++}));
        }
    };
}
