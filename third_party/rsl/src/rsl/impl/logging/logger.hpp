#pragma once

#include "spdlog_include.hpp"

#include "../util/primitives.hpp"

namespace rsl
{
    struct logger {
        class genesis_formatter_flag : public spdlog::custom_flag_formatter
        {
        public:
            void format(const spdlog::details::log_msg& msg, const std::tm& tm_time, spdlog::memory_buf_t& dest) override;

            //generates a new formatter flag
            [[nodiscard]] std::unique_ptr<custom_flag_formatter> clone() const override { return spdlog::details::make_unique<genesis_formatter_flag>(); }
        };

        class logger_name_formatter : public spdlog::custom_flag_formatter
        {
        public:
            void format(const spdlog::details::log_msg& msg, [[maybe_unused]] const std::tm& tm_time, spdlog::memory_buf_t& dest) override
            {
                //append to data
                dest.append(msg.logger_name.begin(), msg.logger_name.end());
            }

            //generates a new formatter flag
            [[nodiscard]] std::unique_ptr<custom_flag_formatter> clone() const override
            {
                return spdlog::details::make_unique<logger_name_formatter>();
            }
        };

        class thread_name_formatter_flag : public spdlog::custom_flag_formatter
        {
            void format([[maybe_unused]] const spdlog::details::log_msg& msg, [[maybe_unused]] const std::tm& tm_time, spdlog::memory_buf_t& dest) override
            {
                ////std::string thread_ident;
                //thread_local static std::string* thread_ident;

                //if (!thread_ident)
                //{
                //    auto& inst = impl::get();
                //    //async::readonly_guard guard(inst.threadNamesLock);

                //    if (inst.threadNames.count(std::this_thread::get_id()))
                //    {
                //        thread_ident = &inst.threadNames.at(std::this_thread::get_id());
                //    }
                //    else
                //    {
                //        std::ostringstream oss;
                //        oss << std::this_thread::get_id();
                //        {
                //            //async::readwrite_guard wguard(inst.threadNamesLock);
                //            thread_ident = &inst.threadNames[std::this_thread::get_id()];
                //        }
                //        *thread_ident = oss.str();
                //    }
                //}

                //dest.append(thread_ident->data(), thread_ident->data() + thread_ident->size());
            }

            std::unique_ptr<custom_flag_formatter> clone() const override
            {
                return spdlog::details::make_unique<thread_name_formatter_flag>();
            }
        };

    };
}

