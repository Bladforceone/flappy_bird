#include "controller.h"


int main() {
	auto controller = Controller::default_controller();
    controller->run();
    delete controller;
    return 0;
}
