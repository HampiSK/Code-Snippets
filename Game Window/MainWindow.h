#ifndef MAINWINDOW_H_INCLUDED
#define MAINWINDOW_H_INCLUDED

#include "pch.h"

struct RenderState
{
    /* Holding data for proper functionality of console window. */

    int screen_width;           // Last known screen width
    int screen_min_width;       // Minimal screen width
    int screen_height;          // Last known screen height
    int screen_min_height;      // Minimal screen height
    int screen_size;            // Last known screen size
    int x = 0;                  // Tracking x line of current cursor position (cursor is changed by the keys not a mouse)
    int y = 0;                  // Tracking y line of current cursor position (cursor is changed by the keys not a mouse)
    bool changed_buffer;        // Changed to true when screen size is changed
    bool running = true;        // Main while loop

    void CursorReset()
    {
        /* Reset cursor to "default" position. */
        x,y = 0;
    }
};

static RenderState RENDER_STATE;

struct MainWindow
{
    int WindowWidth() 
    {
        /* Check and return (int) window width. */

        CONSOLE_SCREEN_BUFFER_INFO csbi;
        int width;

        GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
        width = csbi.srWindow.Right - csbi.srWindow.Left + 1;

        return width;
    }

    int WindowHeight() 
    {
        /* Check and return (int) window height. */

        CONSOLE_SCREEN_BUFFER_INFO csbi;
        int height;

        GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
        height = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;

        return height;
    }

    void ShowConsoleCursor(bool show)
    {
        /* Set the "default" console cursor visibility. */

        HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
        CONSOLE_CURSOR_INFO cursorInfo;
        GetConsoleCursorInfo(out, &cursorInfo);

        // set the cursor visibility
        cursorInfo.bVisible = show; 
        SetConsoleCursorInfo(out, &cursorInfo);
    } 

    void QuickEditMode(bool enable)
    {
        /* Enable/Disable Quick-Edit Mode in console window */

        HANDLE hInput;
        DWORD prev_mode;

        if (enable)
            SetConsoleMode(hInput, prev_mode);
        else
        {       
            hInput = GetStdHandle(STD_INPUT_HANDLE);
            GetConsoleMode(hInput, &prev_mode); 
            SetConsoleMode(hInput, prev_mode & ENABLE_EXTENDED_FLAGS);
        }
    }

    int Center(int pointA, int pointB, std::string text)
    {
        /* Center position of the text between two points. */

        int letters = text.size();
        int half =  (pointA - pointB - letters) / 2;
        return pointB + half + 1;
    }

    int Clamp(int value, int max, int min = 0)
    {
        /* Checking if value is out of range and if it is, return corrected value. Default: min = 0 */

        if (value < min) return min;
        if (value > max) return max;
        return value;
    }

    template< typename TYPE >
    void Text(float x, float y, TYPE message, int color = 7)
    {
        /* Display any type of message on specified cords. Default color = 7 (white) */

        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        COORD coord;

        x += RENDER_STATE.screen_width / 2.f;
        y += RENDER_STATE.screen_height / 2.f;

        coord.X = x;
        coord.Y = y;

        SetConsoleCursorPosition(hConsole, coord); 
        SetConsoleTextAttribute(hConsole, color);
        std::cout << message << std::endl; 
    }

    void Clear(char fill = ' ') 
    { 
        /* Clear window screen */
        
        COORD tl = {0,0};
        CONSOLE_SCREEN_BUFFER_INFO s;
        HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);   
        GetConsoleScreenBufferInfo(console, &s);
        DWORD written, cells = s.dwSize.X * s.dwSize.Y;
        FillConsoleOutputCharacter(console, fill, cells, tl, &written);
        FillConsoleOutputAttribute(console, s.wAttributes, cells, tl, &written);
        SetConsoleCursorPosition(console, tl);
    }

    void SetWindow(int width, int height) 
    { 
        /* Set Window size */

        _COORD coord; 
        coord.X = width; 
        coord.Y = height; 

        _SMALL_RECT Rect; 
        Rect.Top = 0; 
        Rect.Left = 0; 
        Rect.Bottom = height - 1; 
        Rect.Right = width - 1; 

        HANDLE Handle = GetStdHandle(STD_OUTPUT_HANDLE);      // Get Handle 
        SetConsoleScreenBufferSize(Handle, coord);            // Set Buffer Size 
        SetConsoleWindowInfo(Handle, TRUE, &Rect);            // Set Window Size 
    } 

    void WindowInit(int width, int height, std::string window_name) 
    {
        /* Initialize console window */

        Clear();
        HANDLE hOut;
        CONSOLE_SCREEN_BUFFER_INFO SBInfo;
        COORD NewSBSize;

        // Convert string to char
        char new_window_name[window_name.size() + 1];
	    std::copy(window_name.begin(), window_name.end(), new_window_name);
	    new_window_name[window_name.size()] = '\0';

        SetConsoleTitleA(new_window_name);  // Set the window name
        QuickEditMode(false);               // Disable Quick-Edit mode (select, copy, paste....)
        ShowConsoleCursor(false);           // Set the "default" console cursor visibility to false
        SetWindow(width, height);           // Set window size

        RENDER_STATE.screen_min_width = width;
        RENDER_STATE.screen_min_height = height;

        RENDER_STATE.screen_width = WindowWidth();
        RENDER_STATE.screen_height = WindowHeight();          
        RENDER_STATE.screen_size = RENDER_STATE.screen_width * RENDER_STATE.screen_height * sizeof(unsigned int); 

        hOut = GetStdHandle(STD_OUTPUT_HANDLE);

        GetConsoleScreenBufferInfo(hOut, &SBInfo);
        NewSBSize.X = RENDER_STATE.screen_width;
        NewSBSize.Y = RENDER_STATE.screen_height;

        SetConsoleScreenBufferSize(hOut, NewSBSize);
        RENDER_STATE.changed_buffer = true;

    }
    
    void WindowBuffer() 
    {        
        /* Checking if buffer size was changed. */ 

        if (RENDER_STATE.screen_width < RENDER_STATE.screen_min_width || RENDER_STATE.screen_height < RENDER_STATE.screen_min_height )
        {
            Clear();
            RENDER_STATE.changed_buffer = true;
            SetWindow(RENDER_STATE.screen_min_width, RENDER_STATE.screen_min_height);
            RENDER_STATE.screen_width = WindowWidth();
            RENDER_STATE.screen_height = WindowHeight(); 
        }   
        if (RENDER_STATE.screen_width != WindowWidth() || RENDER_STATE.screen_height != WindowHeight())
        {
            Clear();
            RENDER_STATE.changed_buffer = true;
            ShowConsoleCursor(false);  
            
            HANDLE hOut;
            CONSOLE_SCREEN_BUFFER_INFO SBInfo;
            COORD NewSBSize;

            RENDER_STATE.screen_width = WindowWidth();
            RENDER_STATE.screen_height = WindowHeight(); 
            
            hOut = GetStdHandle(STD_OUTPUT_HANDLE);

            NewSBSize.X = RENDER_STATE.screen_width;
            NewSBSize.Y = RENDER_STATE.screen_height;
            SetConsoleScreenBufferSize(hOut, NewSBSize);
        }
    } 
};

MainWindow MAIN_WINDOW;

#endif /* MAINWINDOW_H_INCLUDED */