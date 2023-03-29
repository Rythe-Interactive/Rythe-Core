#pragma once
#include "feature.hpp"

namespace rythe::core {
    template<typename ProgramT, feature_set_c FeatureSetT>
    class Module {
    public:
        using features = FeatureSetT;
    };

    template<template<typename> typename... ModulesT>
    struct Modules {
        template<typename T>
        using type_sequence = rsl::type_sequence<ModulesT<T>...>;
    };
}
