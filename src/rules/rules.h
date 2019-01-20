#pragma once


#include <array>
#include <initializer_list>
#include <utility>

#include <alias.h>
#include <exception.h>


namespace ws::lexer {
    class Rules {
        using entries_t = std::array<Rule, 256>;
        using size_type = entries_t::size_type;


        using init_pair = std::pair<const char*, const Rule>;
        using init_list = std::initializer_list<init_pair>;


        private:

            entries_t entries = {{nullptr}};


        public:
            // Map initializer list onto entries.
            constexpr Rules(
                const init_list& entries_,
                const Rule r
            ) {
                for (auto& x: entries)
                    x = r;


                for (const auto& x: entries_) {
                    const auto& [chars, rule] = x;

                    size_type i = 0;

                    for (auto p = chars[i]; p != '\0'; p = chars[i++])
                        _at(static_cast<size_type>(p)) = rule;
                }
            }


            // Iterators.
            constexpr auto begin() const noexcept { return entries.begin(); }
            constexpr auto end()   const noexcept { return entries.end();   }


        // Element access.
        private:

            constexpr Rule& _at(size_type i) {
                return entries.at(i);
            }


        public:

            constexpr const Rule& at(size_type i) const {
                return entries.at(i);
            }


            constexpr const Rule& operator[](size_type i) const {
                return entries[i];
            }


            constexpr const Rule& at(char i) const {
                return entries.at(static_cast<size_type>(i));
            }


            constexpr const Rule& operator[](char i) const {
                return at(i);
            }
    };
}