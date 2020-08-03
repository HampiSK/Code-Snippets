#ifndef BUTTON_H_INCLUDED
#define BUTTON_H_INCLUDED

#include "pch.h"

struct Buttons
{
    short unsigned int button_left       = 37;
    short unsigned int button_up         = 38;
    short unsigned int button_right      = 39;
    short unsigned int button_down       = 40;
    short unsigned int button_escape     = 27;
    short unsigned int button_backspace  = 8;
    short unsigned int button_enter      = 13;

    bool left_state                      = false;
    bool up_state                        = false;
    bool right_state                     = false;
    bool down_state                      = false;
    bool confirm_state                   = false;
    bool escape_state                    = false;
    bool backspace_state                 = false;
    bool button_state                    = false;

    void Button()
    {
        int key = 0;
        for(int i = 8; i <= 256; i++)
        {           
            if(GetAsyncKeyState(i) & 0x7FFF)    
            {         
                key = i;
                break;
            }
        }

        if (key == button_left)
        {
            RENDER_STATE.x--;
            button_state = true;  
            left_state = true;          
        }
        else if (key == button_up)
        {
            RENDER_STATE.y--;
            button_state = true;    
            up_state = true;        
        }
        else if (key == button_right)
        {
            RENDER_STATE.x++;
            button_state = true; 
            right_state = true;              
        }
        else if (key == button_down)
        {
            RENDER_STATE.y++;
            button_state = true;   
            down_state = true;          
        }
        else if (key == button_enter)
        {
            confirm_state = true;
            button_state = true;
        }
        else if (key == button_escape)
        {
            escape_state = true;
            button_state = true;
        }
        else if (key == button_backspace)
        {
            backspace_state = true;
            button_state = true;
        }
        else
        {
            left_state      = false;
            up_state        = false; 
            right_state     = false; 
            down_state      = false;  
            backspace_state = false;
            confirm_state   = false;
            escape_state    = false;
            button_state    = false;
        }
    }
};

static Buttons BUTTON;

#endif /* BUTTON_H_INCLUDED */