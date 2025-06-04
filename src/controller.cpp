#include "controller.h"
#include "view/gl_view.h"

Controller *Controller::default_controller() {
    auto view = new GL_View();
    auto model = Model::default_model(view->get_size(), view->get_bird_size(), view->get_pipe_size());
    return new Controller(view, model);
}

Controller::Controller(View *view, Model *model): view(view), model(model) {

}

void Controller::run() {
    model->init();
    while (view->is_alive()) {
        auto action = view->get_action();
        auto state = model->update(action);
        view->show_state(state);
    }
}

Controller::~Controller() {
    delete model;
    delete view;
}
