#pragma once


#include <string>
#include <optional>

#include "../constant.h"
#include "../exception.h"
#include "../rules/rules.h"
#include "../stringiter/stringiter.h"

// #include <libs/logger.h>


namespace ws::lexer {

	template <typename T>
    std::optional<Token> get_next_token(
        const Rules& rules,
        ws::lexer::StringIter& iter,
        T& tokens
    ) {
        auto size = tokens.size();

        rules.at(iter.peek()) (iter, tokens);
        iter.incr();

        if (size != tokens.size())
            return tokens.back();

        return {};
    }


	template <typename T>
    void consume(
        const Rules& rules,
        ws::lexer::StringIter& iter,
        T& tokens
    ) {
        rules.at(iter.peek()) (iter, tokens);
        iter.incr();
    }


	template <typename T>
    void lexer(
        const Rules& rules,
        ws::lexer::StringIter& iter,
        T& tokens
    ) {
        while (not iter.is_end())
            consume(rules, iter, tokens);
    }

}
