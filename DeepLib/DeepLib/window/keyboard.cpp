#include "keyboard.hpp"
#include "DeepLib/context.hpp"
#include "DeepLib/window/window.hpp"

namespace deep
{
    keyboard_event::keyboard_event() noexcept
            : m_action(action::Invalid),
              m_key(0)
    {
    }

    keyboard_event::keyboard_event(action a, vkey key) noexcept
            : m_action(a),
              m_key(key)
    {
    }

    bool keyboard_event::is_press() const noexcept
    {
        return m_action == action::Press;
    }

    bool keyboard_event::is_release() const noexcept
    {
        return m_action == action::Release;
    }

    bool keyboard_event::is_valid() const noexcept
    {
        return m_action != action::Invalid;
    }

    vkey keyboard_event::get_key() const noexcept
    {
        return m_key;
    }

    keyboard::keyboard(const ref<ctx> &context) noexcept
            : m_auto_repeat_enabled(false),
              m_event_buffer(context),
              m_char_buffer(context)
    {
    }

    bool keyboard::key_is_pressed(vkey key) const noexcept
    {
        return m_key_states.test(static_cast<usize>(key));
    }

    keyboard::event keyboard::read_key() noexcept
    {
        if (!m_event_buffer.is_empty())
        {
            event e = m_event_buffer.get_front();
            m_event_buffer.pop();

            return e;
        }

        return event();
    }

    bool keyboard::key_is_empty() const noexcept
    {
        return m_event_buffer.is_empty();
    }

    void keyboard::clear_key() noexcept
    {
        m_event_buffer.empty();
    }

    native_char keyboard::read_char() noexcept
    {
        if (!m_char_buffer.is_empty())
        {
            native_char character = m_char_buffer.get_front();
            m_char_buffer.pop();

            return character;
        }

        return 0;
    }

    bool keyboard::char_is_empty() const noexcept
    {
        return m_char_buffer.is_empty();
    }

    void keyboard::clear_char() noexcept
    {
        m_char_buffer.empty();
    }

    void keyboard::clear() noexcept
    {
        m_event_buffer.empty();
        m_char_buffer.empty();
    }

    bool keyboard::is_auto_repeat_enabled() const noexcept
    {
        return m_auto_repeat_enabled;
    }

    void keyboard::set_auto_repeat(bool enabled) noexcept
    {
        m_auto_repeat_enabled = enabled;
    }

    bool keyboard::on_key_pressed(vkey key, bool repeated, window * /*win*/) noexcept
    {
        if (repeated && !m_auto_repeat_enabled)
        {
            return true;
        }

        m_key_states.set(static_cast<usize>(key));

        m_event_buffer.add(event(event::action::Press, key));

        trim_buffer(m_event_buffer);

        return true;
    }

    bool keyboard::on_key_released(vkey key, window * /*win*/) noexcept
    {
        m_key_states.reset(static_cast<usize>(key));

        m_event_buffer.add(event(event::action::Release, key));

        trim_buffer(m_event_buffer);

        return true;
    }

    bool keyboard::on_text_input(native_char key, window * /*win*/) noexcept
    {
        m_char_buffer.add(key);

        trim_buffer(m_char_buffer);

        return true;
    }

    bool keyboard::on_lose_focus(window * /*win*/) noexcept
    {
        m_key_states.clear();

        return true;
    }

} // namespace deep
