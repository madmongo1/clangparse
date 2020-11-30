#include "index.hpp"
#include "translation_unit.hpp"
#include <fmt/format.h>
#include <iostream>
#include <stdexcept>

std::ostream& operator<<(std::ostream& stream, const CXString& str)
{
  stream << clang_getCString(str);
  clang_disposeString(str);
  return stream;
}

/// @brief Here is my main function.
int
main(int argc, char **argv)
{
    using namespace program;

    try
    {
        if (argc < 2)
            throw std::invalid_argument("must specify an input file");

        auto i = program::index(false, true);

        /*
         * -triple x86_64-unknown-linux-gnu -emit-obj -mrelax-all
         * -disable-free -disable-llvm-verifier -discard-value-names
         * -main-file-name main.cpp -mrelocation-model static -mthread-model
         * posix -mdisable-fp-elim -fmath-errno -masm-verbose
         * -mconstructor-aliases -munwind-tables -fuse-init-array -target-cpu
         * x86-64 -dwarf-column-info -debugger-tuning=gdb -v -resource-dir
         * /usr/lib64/clang/9.0.1 -internal-isystem
         * /usr/lib/gcc/x86_64-redhat-linux/9/../../../../include/c++/9
         * -internal-isystem
         * /usr/lib/gcc/x86_64-redhat-linux/9/../../../../include/c++/9/x86_64-redhat-linux
         * -internal-isystem
         * /usr/lib/gcc/x86_64-redhat-linux/9/../../../../include/c++/9/backward
         * -internal-isystem /usr/local/include -internal-isystem
         * /usr/lib64/clang/9.0.1/include -internal-externc-isystem /include
         * -internal-externc-isystem /usr/include
         *
         * -fdeprecated-macro -fdebug-compilation-dir
         * /home/rhodges/cppalliance/clangparse/cmake-build-debug
         * -ferror-limit 19 -fmessage-length 0 -fobjc-runtime=gcc
         * -fcxx-exceptions -fexceptions -fdiagnostics-show-option
         * -fcolor-diagnostics -faddrsig -o /tmp/main-b05b4e.o -x c++
         */
        std::vector<std::string> options = {};
        /* { "-v",
        "-std=c++17",
        "-I/usr/include/linux", "-I/usr/include/c++/v1"};*/
        auto tu = translation_unit(i,
                                   argv[1],
                                   options,
                                   {},
                                   CXTranslationUnit_None);

        CXCursor cursor = clang_getTranslationUnitCursor(tu.native_handle());
        clang_visitChildren(
            cursor,
            [](CXCursor c, CXCursor parent, CXClientData client_data) {
                std::cout << "Cursor '" << clang_getCursorSpelling(c)
                          << "' of kind '"
                          << clang_getCursorKindSpelling(
                                 clang_getCursorKind(c))
                          << "'\n";
                return CXChildVisit_Recurse;
            },
            nullptr);
    }
    catch (std::exception &e)
    {
        fmt::print(stderr, "clangparse: exception - {}", e.what());
        return 127;
    }
    return 0;
}
