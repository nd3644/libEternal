#include "input.h"

Eternal::InputHandle::InputHandle() {
}

Eternal::InputHandle::~InputHandle() {
}

void Eternal::InputHandle::PollInputs() {
    const Uint8 *myKeys = SDL_GetKeyboardState(0);
    myMouse = SDL_GetMouseState(&iMouseX, &iMouseY);

    for(int i = 0;i < 256;i++) {
        bPrevKeyStates[i] = bKeyStates[i];
        bKeyStates[i] = false;
        if(myKeys[i]) {
            bKeyStates[i] = true;
        }
    }
}

bool Eternal::InputHandle::IsKeyDown(Key key) {
    return bKeyStates[key];
}

bool Eternal::InputHandle::IsKeyTap(Key key) {
    return (bKeyStates[key] && !bPrevKeyStates[key]);
}

bool Eternal::InputHandle::IsMouseDown(MouseButtons b) {
    if(myMouse & b) {
        return true;
    }
    return false;
}

int Eternal::InputHandle::GetMouseX() const {
    return iMouseX;
}

int Eternal::InputHandle::GetMouseY() const {
    return iMouseY;
}