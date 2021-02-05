

#include "../message/messageStream.h"
#include "foldExpression.h"

using namespace FoldExpression;

Msg::Message<Msg::Info, Msg::DelimitSpace, false, false> msg;

int main() {

    msg("--Show--");
    lookup("first line", 2, "third line", 4);
    msg("");

    msg("--Reverse Show--");
    reverseLookup("first line", 2, "third line", 4);
    msg("");

    msg("--Any--");
    msg("1>3, 1==2, 3>2:", any(1 > 3, 1 == 2, 3 > 2) ? "True" : "false");
    msg("1>3, 1==2, 2>2:", any(1 > 3, 1 == 2, 2 > 2) ? "True" : "false");
    msg("");

    msg("--Show if true--");
    firstPred(1, 3, 5, 3, 4);
    msg("");

    msg("--Get first element--");
    msg("first element of [1, 3, 5, 3, 4]:", firstElement(1, 3, 5, 3, 4));
    msg("");

    msg("--Get last element--");
    msg("last element of [1, 3, 5, 3, 4]:", lastElement(1, 3, 5, 3, 4));
    msg("");

    msg("--Get nth element--");
    msg(1, "\b'th element of [3, 5, 6, 4]:", nthElement(1, 3, 5, 6, 4));
    msg(3, "\b'th element of [3, 5, 6, 4]:", nthElement(3, 3, 5, 6, 4));
    msg(2, "\b'th element of [3, 5, 6, 4]:", nthElement(2, 3, 5, 6, 4));
    msg(0, "\b'th element of [3, 5, 6, 4]:", nthElement(0, 3, 5, 6, 4));
    msg("");

    msg("--Get min element--");
    msg("min element of [1, 3, -5, -33, 4]:", minElement(1, 3, -5, -33, 4));
    msg("");

    return 0;
}