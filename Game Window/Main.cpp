#include "pch.h"

static bool running = true;

std::string mainmenu(int &x, int &y)
{     
    /* Create main menu and return choosen menu */

    const std::vector<std::string> options = {"Campaign","Normal Game","Tutorial","Options","Quit"};
    y = Main_Window.checker(y, options.size());

    int center_y = -10;
    for (unsigned int i = 0; i < options.size(); i++)
    {
        int option_size = options[i].size();
        if (y == i)
        {
            Main_Window.text(0 - option_size / 2, center_y, options[i], 4);
            if(Button.confirm_state)
                return options[i];
        }
        else
            Main_Window.text(0 - option_size / 2, center_y, options[i], 7);
        
        center_y += 5;
    }

    return "none"; 
}

int main()
{
    srand(time(NULL));
    Main_Window.WindowInit();

    while (true)
    {
        Main_Window.WindowBuffer();
        buttons();

        Main_Window.text(0,0,7,7);
    }

    return 0;
}