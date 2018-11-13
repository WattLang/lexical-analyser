#include "stringiter.h"


#include <constant.h>


namespace ws::lexer {
    // Check if next character is expected and advance.
    bool StringIter::match(char expect) {
        if (is_end() or peek(1) != expect)
            return false;


        incr(2);
        return true;
    }


    // Skip over characters until a certain condition is met.
    void StringIter::next_while(alias::WhilePred pred) {
        while (true) {
            // If the next char is not valid, break and return builder.

            // The size is offset because the predicate must look forward by size + 1 in the case of the final character which would lead to an exception.

            // (Expression order is important here.)
            if (is_end(-1) or not pred(*this, peek(1)))
                break;

            incr();
        }
    }


    const std::string StringIter::read_while(alias::WhilePred pred) {
        const char *begin = current;
        std::size_t length = 1;


        while (true) {
            // If the next char is not valid, break and return builder.

            // The size is offset because the predicate must look forward by size + 1 in the case of the final character which would lead to an exception.

            // (Expression order is important here.)
            if (is_end(-1) or not pred(*this, peek(1)))
                break;


            incr();
            ++length;
        }

        return std::string(begin, length);
    }

}