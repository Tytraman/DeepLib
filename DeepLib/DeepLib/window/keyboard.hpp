#ifndef DEEP_LIB_KEYBOARD_HPP
#define DEEP_LIB_KEYBOARD_HPP

#include "DeepLib/deep_lib_export.h"
#include "DeepCore/vkeys.hpp"
#include "DeepLib/utils/bitset.hpp"
#include "DeepLib/collection/queue.hpp"

namespace deep
{
    template class DEEP_LIB_API bitset<vkeys::KeyCount>;

    class window;

    class DEEP_LIB_API keyboard_event
    {
      public:
        enum class action
        {
            Invalid,
            Press,
            Release
        };

      public:
        keyboard_event() noexcept;
        keyboard_event(action a, vkey key) noexcept;

        bool is_press() const noexcept;
        bool is_release() const noexcept;
        bool is_valid() const noexcept;

        vkey get_key() const noexcept;

      private:
        action m_action;
        vkey m_key;
    };

    class DEEP_LIB_API keyboard
    {
      public:
        using event = keyboard_event;

        friend window;

      public:
        keyboard() = delete;
        keyboard(const ref<ctx> &context) noexcept;

        keyboard(const keyboard &)            = delete;
        keyboard &operator=(const keyboard &) = delete;

        bool key_is_pressed(vkey key) const noexcept;
        event read_key() noexcept;
        bool key_is_empty() const noexcept;
        void clear_key() noexcept;

        native_char read_char() noexcept;
        bool char_is_empty() const noexcept;
        void clear_char() noexcept;

        void clear() noexcept;

        bool is_auto_repeat_enabled() const noexcept;
        void set_auto_repeat(bool enabled) noexcept;

      private:
        bool on_key_pressed(vkey key, bool repeated, window *win) noexcept;
        bool on_key_released(vkey key, window *win) noexcept;
        bool on_text_input(native_char key, window *win) noexcept;
        bool on_lose_focus(window *win) noexcept;

        template <typename Type>
        static void trim_buffer(queue<Type> &buffer) noexcept;

      private:
        static constexpr uint8 BufferSize = 16;

        bool m_auto_repeat_enabled;
        bitset<vkeys::KeyCount> m_key_states;
        DEEP_QUEUE(event, m_event_buffer)
        DEEP_QUEUE(native_char, m_char_buffer)
    };

    template <typename Type>
    inline void keyboard::trim_buffer(queue<Type> &buffer) noexcept
    {
        while (buffer.count() > BufferSize)
        {
            if (!buffer.pop())
            {
                // Sécurité pour éviter une boucle infinie.
                break;
            }
        }
    }

} // namespace deep

#endif
