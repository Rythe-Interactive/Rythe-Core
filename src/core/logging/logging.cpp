#include <core/logging/logging.hpp>


namespace rythe::core::log
{
    impl& impl::get()
    {
        static impl m_instance;
        return m_instance;
    }

}
