//
// Copyright (c) 2000 Richard Hodges (hodges.r@gmail.com)
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/CPPAlliance/clangparse
//

#ifndef CLANGPARSE_INDEX_HPP
#define CLANGPARSE_INDEX_HPP
#include <clang-c/Index.h>
#include <utility>

namespace program
{

struct index {

    index(bool exclude_pch = false, bool display_diagnostics = false)
        : native_handle_(
              clang_createIndex(static_cast<int>(exclude_pch),
                                static_cast<int>(display_diagnostics)))
    {
    }

    index(index &&b) noexcept
        : native_handle_(std::exchange(b.native_handle_, nullptr))
    {
    }

    index &
    operator=(index &&b) noexcept
    {
        auto tmp = native_handle_;
        native_handle_ = std::exchange(b.native_handle_, nullptr);
        dispose(tmp); // foo
        return *this;
    }


    ~index() { dispose(native_handle_); }

    index(index const &) = delete;

    index &
    operator=(index const &) = delete;

    CXIndex
    native_handle() const noexcept
    {
        return native_handle_;
    }

private:
    static void
    dispose(CXIndex handle) noexcept
    {
        if (handle) clang_disposeIndex(handle);
    }

    CXIndex native_handle_;
};
} // namespace program

#endif // CLANGPARSE_INDEX_HPP
