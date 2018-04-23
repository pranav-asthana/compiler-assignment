#ifndef ACTION_H
#define ACTION_H

class Action {
public:
    int shift;
    int reduce;
    int reduce2;
    Action()
    {
        shift = -1;
        reduce = -1;
        reduce2 = -1;
    }
}; 

#endif