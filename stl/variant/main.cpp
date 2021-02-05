

#include "variant_get.h"
#include "variant_visit.h"
#include "variant_size.h"
#include "variant_polymoprhism.h"

int main(void) {

    std::cout << "\nTest of get get_if \n";
    variant_get();

    std::cout << "\nTest of visit \n";
    variant_visit();

    std::cout << "\nTest of size \n";    
    variant_size();

    std::cout << "\nTest of polymoprhism \n";
    variant_polymoprhism();
    
    return 0;
}