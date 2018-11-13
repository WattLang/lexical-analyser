#pragma once


#include <string>
#include <string_view>
#include <alias.h>
#include <libs/module.h>


namespace ws::lexer {
    struct StringIter {
        std::string_view buffer;
        const char *current = nullptr;


        StringIter(std::string_view buffer_):
            buffer(buffer_),
            current(buffer.data())
        {}




        // Iterate.
        char next() { return *current++; }
        //char prev() { return *current--; }

        char next(const unsigned i) {
            current += i;
            return *(current - i);
        }

        /*char prev(const unsigned i) {
            current -= i;
            return *(current + i);
        }*/



        void incr() noexcept { current++; }
        //void decr() noexcept { current--; }

        void incr(const unsigned i) noexcept { current += i; }
        //void decr(const unsigned i) noexcept { current -= i; }









        // View characters.
        //char at(const unsigned i)   const { return buffer.at(i);  }
        char peek(const unsigned i) const { return *(current + i); }
        char peek()                 const { return *(current);     }






        // Info.
        std::string::size_type size() const noexcept { return buffer.size(); }

        bool is_end(int offset = 0) const noexcept {
            return current >= ((buffer.data() + size()) + offset);
        }








        // Read N characters.
        /*const std::string read(const std::string::size_type& n) const {
            return buffer.substr(static_cast<unsigned long>(current - buffer.data() + 1), n);
        }*/



        // Check if next character is expected and advance.
        bool match(char expect);


        // Skip over characters until a certain condition is met.
        void next_while(alias::WhilePred pred);

        const std::string read_while(alias::WhilePred pred);
    };
}