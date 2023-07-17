#include "FineGrainedQueue.h"

int main()
{
    FineGrainedQueue o;
    o.addValue(43);
    o.addValue(66);
    o.addValue(23);
    o.addValue(76);
    o.addValue(89);
    o.addValue(43);
    o.show();

    o.insertIntoMiddle(111, 3);
    o.show();

    o.insertIntoMiddle(111, 10);
    o.show();

    o.remove(23);
    o.show();
}
