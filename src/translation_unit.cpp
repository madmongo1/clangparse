//
// Copyright (c) 2000 Richard Hodges (hodges.r@gmail.com)
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/CPPAlliance/clangparse
//

#include "translation_unit.hpp"

namespace program
{

translation_unit::translation_unit(
    index &i,
    const std::string &filename,
    std::vector<std::string> const &cmd_line_args,
    std::vector<CXUnsavedFile> unsaved_files,
    CXTranslationUnit_Flags flags)
    : native_handle_(nullptr)
{
    std::vector<const char *> args;
    args.resize(cmd_line_args.size(), nullptr);
    std::transform(cmd_line_args.begin(),
                   cmd_line_args.end(),
                   args.begin(),
                   [](std::string const &arg) { return arg.c_str(); });

    native_handle_ = clang_parseTranslationUnit(
        i.native_handle(),
        filename.empty() ? nullptr : filename.c_str(),
        args.empty() ? nullptr : args.data(),
        args.size(),
        unsaved_files.empty() ? nullptr : unsaved_files.data(),
        unsaved_files.size(),
        flags);

    if (!native_handle_)
        throw std::invalid_argument("translation_unit: " + filename);
}

translation_unit::translation_unit(translation_unit &&b) noexcept
    : native_handle_(std::exchange(b.native_handle_, nullptr))
{
}

translation_unit &
translation_unit::operator=(translation_unit &&b) noexcept
{
    dispose(std::exchange(native_handle_,
                          std::exchange(b.native_handle_, nullptr)));
    return *this;
}

translation_unit::~translation_unit() noexcept { dispose(native_handle_); }


void
translation_unit::dispose(CXTranslationUnit handle)
{
    if (handle) clang_disposeTranslationUnit(handle);
}

} // namespace program