#include "pch.h"

int main()
{

    MAIN_WINDOW.WindowInit(150,40);

    while (RENDER_STATE.running)
    {
        MAIN_WINDOW.WindowBuffer();
        BUTTON.Button();

        if(BUTTON.button_state)
            RENDER_STATE.running = false;

        std::string message = "Press ANY key to quit.";
        MAIN_WINDOW.Text(MAIN_WINDOW.Center(0,0,message),0,message);
    }

    return 0;
}