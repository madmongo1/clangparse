//
// Copyright (c) 2000 Richard Hodges (hodges.r@gmail.com)
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/CPPAlliance/clangparse
//

#ifndef CLANGPARSE_TRANSLATION_UNIT_HPP
#define CLANGPARSE_TRANSLATION_UNIT_HPP

#include "index.hpp"
#include <algorithm>
#include <stdexcept>
#include <string>
#include <vector>

namespace program
{
struct translation_unit {
    translation_unit(index &i,
                     std::string const &filename,
                     std::vector<std::string> const &cmd_line_args,
                     std::vector<CXUnsavedFile> unsaved_files,
                     CXTranslationUnit_Flags flags);

    translation_unit(translation_unit const &) = delete;

    translation_unit &
    operator=(translation_unit const &) = delete;

    translation_unit(translation_unit &&b) noexcept;

    translation_unit &
    operator=(translation_unit &&b) noexcept;

    ~translation_unit() noexcept;

    CXTranslationUnit native_handle() const noexcept { return native_handle_; }
private:
    inline void
    dispose(CXTranslationUnit handle);

    CXTranslationUnit native_handle_;
};

} // namespace program

#endif // CLANGPARSE_TRANSLATION_UNIT_HPP
