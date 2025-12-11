#include "context.hpp"
#include "DeepCore/context.hpp"
#include "DeepCore/term.hpp"

#include "DeepLib/stream/file_stream.hpp"
#include "DeepLib/stream/stream_writer.hpp"

namespace deep
{

    ctx::ctx()
            : m_internal_data(nullptr), m_mem(nullptr)
    {
    }

    ctx::~ctx()
    {
        destroy_internal_ctx();
    }

    bool ctx::destroy_internal_ctx()
    {
        if (!core_ctx::destroy_internal_ctx(m_internal_data))
        {
            return false;
        }

        m_internal_data = nullptr;

        return true;
    }

    bool ctx::init()
    {
        m_internal_data = core_ctx::create_internal_ctx();
        if (m_internal_data == nullptr)
        {
            return false;
        }

        m_mem = static_cast<memory_manager *>(core_mem::alloc(nullptr, sizeof(memory_manager)));
        if (m_mem == nullptr)
        {
            core_ctx::destroy_internal_ctx(m_internal_data);

            return false;
        }

        m_mem->m_internal_context = m_internal_data;

        ref<ctx> context = ref<ctx>(this, this);

        // --- Initialisation du terminal ---

        core_term::set_encoding(m_internal_data, string_encoding::UTF8);

        fd stdout = core_term::get_std_handle(m_internal_data, core_term::std_handle::Output);
        if (stdout != invalid_fd)
        {
            core_term::add_mode(m_internal_data, stdout, core_term::mode::EnableProcessedOutput);
            core_term::add_mode(m_internal_data, stdout, core_term::mode::EnableVirtualTerminalProcessing);
            m_stdout        = ref_cast<stream>(ref<file_stream>(this, mem::alloc_type<file_stream>(m_mem, context, stdout)));
            m_stdout_writer = ref_cast<text_writer>(ref<stream_writer>(this, mem::alloc_type<stream_writer>(m_mem, m_stdout.get())));
        }

        fd stderr = core_term::get_std_handle(m_internal_data, core_term::std_handle::Error);
        if (stderr != invalid_fd)
        {
            core_term::add_mode(m_internal_data, stderr, core_term::mode::EnableProcessedOutput);
            core_term::add_mode(m_internal_data, stderr, core_term::mode::EnableVirtualTerminalProcessing);

            m_stderr        = ref_cast<stream>(ref<file_stream>(this, mem::alloc_type<file_stream>(m_mem, context, stderr)));
            m_stderr_writer = ref_cast<text_writer>(ref<stream_writer>(this, mem::alloc_type<stream_writer>(m_mem, m_stderr.get())));
        }

        return true;
    }

    text_writer &ctx::out()
    {
        return *m_stdout_writer;
    }

    text_writer &ctx::err()
    {
        return *m_stderr_writer;
    }
} // namespace deep
