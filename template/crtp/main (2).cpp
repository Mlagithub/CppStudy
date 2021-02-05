
#include "crtp.h"


int main(void){

    std::shared_ptr<BA> base(A{}.clone());

    std::shared_ptr<Reader> reader(ReaderYAML{}.clone());

    auto rst = std::make_shared<Reader>(ReaderYAML{}.clone());

    return 0;
}