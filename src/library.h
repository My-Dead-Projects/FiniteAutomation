#pragma once

#include <unordered_map>
#include <unordered_set>
#include <string>

typedef int32_t state_t;
typedef std::unordered_map<std::pair<state_t, char>, state_t>
        transition_table_t;
typedef std::unordered_set<state_t> final_state_table_t;

namespace std
{
    template<>
    struct hash<pair<state_t, char>>
    {
        size_t operator()(const pair<state_t, char> &k) const
        {
            size_t h1 = hash<state_t>()(k.first);
            size_t h2 = hash<char>()(k.second);
            return ((h1 ^ h2 << 1) >> 1);
        }
    };
}

class DFA
{
private:
    transition_table_t transition_table;
    final_state_table_t final_state_table;

    explicit DFA(transition_table_t t_table, final_state_table_t f_table) :
            transition_table(move(t_table)), final_state_table(move(f_table))
    {}

public:
    class builder;

    DFA() = delete;

    bool accepts(const std::string &s) const
    {
        state_t state = 0;
        for (char c : s)
        {
            // Find returns an iterator to the appropriate transition
            auto transition = transition_table.find({state, c});

            if (transition != transition_table.end())
            {
                // Transition found.
                // transition->second refers to the "end" state
                state = transition->second;
            }
            else
            {
                // Transition not found. Crash.
                return false;
            }
        }
        // Reached end of string without crashing.
        // If current state is a final state, accept.
        auto final_state = final_state_table.find(state);

        // Find returns iterator to end if the state is not found.
        // If final_state is found, accept.
        // If final_state is not found (it's an iterator to end), crash.

        return final_state != final_state_table.end();
    }
};

class DFA::builder
{
    transition_table_t t_table;
    final_state_table_t f_table;

public:
    builder &transition(state_t start, char c, state_t end)
    {
        t_table[{start, c}] = end;
        return *this;
    }

    builder &transition_range(state_t start, char c_begin, char c_end,
                              state_t end)
    {
        for (char c = c_begin; c <= c_end; c++)
        {
            t_table[{start, c}] = end;
        }
        return *this;
    }

    builder &final_state(state_t f_state)
    {
        f_table.insert(f_state);
        return *this;
    }

    DFA build() const
    {
        return DFA(t_table, f_table);
    }
};
