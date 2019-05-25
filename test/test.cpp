#include "../src/library.h"
#include <iostream>
using namespace std;

int main()
{
    FSM fsm = FSM::builder()
            .transition_range(0, 'b', 'z', 0)
            .transition(0, 'a', 1)
            .transition(1, 'b', 2)
            .transition(1, 'a', 0)
            .transition_range(1, 'c', 'z', 0)
            .transition(2, 'c', 3)
            .transition_range(2, 'a', 'b', 0)
            .transition_range(2, 'd', 'z', 0)
            .transition(3, 'a', 1)
            .transition_range(3, 'b', 'z', 0)
            .final_state(3)
            .build();

    if (fsm.accepts("aslkjdfjfabcabc"))
    {
        cout << "Accept" << endl;
    }
    else
    {
        cout << "Crash" << endl;
    }
}
