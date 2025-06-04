#ifndef FLAPPY_BIRD_CONTROLLER_H
#define FLAPPY_BIRD_CONTROLLER_H

#include "view/view.h"
#include "model/model.h"

class Controller {
public:
    static Controller* default_controller();

    Controller(View* view, Model* model);

    void run();

    ~Controller();
private:
    View* view;
    Model* model;
};


#endif //FLAPPY_BIRD_CONTROLLER_H
