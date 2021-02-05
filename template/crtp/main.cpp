
#include "crtp.h"

int main(void) {
    ConfigYAML cfgyaml(3.3);
    cfgyaml.show();

    ConfigAct cfgact;
    cfgact.show();

    Vehicle *car = new Car();
    Vehicle *plane = new Plane();
    Vehicle *fighterplane = new FighterPlane();

    car->describe();
    plane->describe();
    fighterplane->describe();

    Vehicle *vehicleUnknown = plane->clone();

    vehicleUnknown->describe();
}