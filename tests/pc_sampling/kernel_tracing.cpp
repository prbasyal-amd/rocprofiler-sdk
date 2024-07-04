// MIT License
//
// Copyright (c) 2024 ROCm Developer Tools
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

// undefine NDEBUG so asserts are implemented
#ifdef NDEBUG
#    undef NDEBUG
#endif

/**
 * @file samples/pc_sampling_library/client.cpp
 *
 * @brief Example rocprofiler client (tool)
 */

#include "utils.hpp"

#include <rocprofiler-sdk/external_correlation.h>
#include <rocprofiler-sdk/fwd.h>
#include <rocprofiler-sdk/rocprofiler.h>

#include <atomic>
#include <iostream>
#include <memory>

namespace client
{
namespace kernel_tracing
{
constexpr size_t BUFFER_SIZE_BYTES = 8192;
constexpr size_t WATERMARK         = (BUFFER_SIZE_BYTES / 4);

rocprofiler_buffer_id_t kernel_tracing_buffer;

void
kernel_tracing_buffered(rocprofiler_context_id_t /*context*/,
                        rocprofiler_buffer_id_t /*buffer_id*/,
                        rocprofiler_record_header_t** /*headers*/,
                        size_t /*num_headers*/,
                        void* /*user_data*/,
                        uint64_t /*drop_count*/)
{}

void
configure_kernel_tracing_service(rocprofiler_context_id_t context)
{
    ROCPROFILER_CHECK(rocprofiler_create_buffer(context,
                                                BUFFER_SIZE_BYTES,
                                                WATERMARK,
                                                ROCPROFILER_BUFFER_POLICY_LOSSLESS,
                                                kernel_tracing_buffered,
                                                nullptr,
                                                &kernel_tracing_buffer));

    ROCPROFILER_CHECK(rocprofiler_configure_buffer_tracing_service(
        context, ROCPROFILER_BUFFER_TRACING_KERNEL_DISPATCH, nullptr, 0, kernel_tracing_buffer));
}

}  // namespace kernel_tracing
}  // namespace client
