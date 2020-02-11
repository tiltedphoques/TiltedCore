#pragma once

#include <cstdint>

namespace TiltedPhoques
{
    class Initializer {
    public:
        using callback_t = void (*)();

    private:
        Initializer* next_{ nullptr };
        callback_t callback_{ nullptr };

        Initializer(Initializer*& parent, callback_t callback) noexcept;

    public:
        Initializer(callback_t callback) noexcept;
        Initializer(Initializer& parent, callback_t callback) noexcept;

        Initializer(const Initializer&) = delete;
        Initializer(Initializer&&) = delete;

        static Initializer*& ROOT() noexcept;

        static std::size_t RunAll();
    };

    inline Initializer::Initializer(Initializer*& parent,
        callback_t callback) noexcept
        : next_(parent),
        callback_(callback) {
        parent = this;
    }

    inline Initializer::Initializer(callback_t callback) noexcept
        : Initializer(ROOT(), callback) {}

    inline Initializer::Initializer(Initializer& parent,
        callback_t callback) noexcept
        : Initializer(parent.next_, callback) {}

    inline Initializer*& Initializer::ROOT() noexcept {
        static Initializer* root{ nullptr };

        return root;
    }

    inline std::size_t Initializer::RunAll() {
        std::size_t total = 0;

        for (Initializer* i = ROOT(); i;) {
            if (i->callback_) {
                i->callback_();
                i->callback_ = nullptr;

                ++total;
            }

            Initializer* j = i->next_;
            i->next_ = nullptr;
            i = j;
        }

        ROOT() = nullptr;

        return total;
    }
}
