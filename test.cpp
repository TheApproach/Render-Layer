#include "streamtype.h"
#include "xml.h"
#include <vector>

int main() {
    StreamType<std::vector<int>, int, double, char, XML> stream1;
    return 0;
}
