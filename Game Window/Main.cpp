#include "pch.h"

int main()
{

    MAIN_WINDOW.WindowInit(150,40,"Window Name");

    while (RENDER_STATE.running)
    {
        MAIN_WINDOW.WindowBuffer();
        BUTTON.Button();

        if(BUTTON.button_state || RENDER_STATE.changed_buffer)
        {
            RENDER_STATE.changed_buffer = false;
            std::string message =   "WIDTH: " +
                                    std::to_string(RENDER_STATE.screen_width) + " MIN: " +
                                    std::to_string(RENDER_STATE.screen_min_width) + " HEIGHT: " +
                                    std::to_string(RENDER_STATE.screen_height)+ " MIN: " +
                                    std::to_string(RENDER_STATE.screen_min_height);
            MAIN_WINDOW.Text(MAIN_WINDOW.Center(0,0,message),0,message);
        }
    }

    return 0;
}