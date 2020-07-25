#ifndef MAINWINDOW_H_INCLUDED
#define MAINWINDOW_H_INCLUDED

#include "pch.h"

struct RenderState
{
    int width;
    int height;
    int size;
    int x = 0;
    int y = 0;
    bool changed_buffer;

    void cord_clear()
    {
        x,y = 0;
    }
};

static RenderState RENDERSTATE;

struct MainWindow
{
    int window_width() 
    {
        CONSOLE_SCREEN_BUFFER_INFO csbi;
        int width;

        GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
        width = csbi.srWindow.Right - csbi.srWindow.Left + 1;

        return width;
    }

    int window_height() 
    {
        CONSOLE_SCREEN_BUFFER_INFO csbi;
        int height;

        GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
        height = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;

        return height;
    }

    void ShowConsoleCursor(bool showFlag)
    {
        HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
        CONSOLE_CURSOR_INFO cursorInfo;
        GetConsoleCursorInfo(out, &cursorInfo);

        // set the cursor visibility
        cursorInfo.bVisible = showFlag; 

        SetConsoleCursorInfo(out, &cursorInfo);
    } 

    int center(int pointA, int pointB, std::string text)
    {
        int letters = text.size();
        int half =  (pointA - pointB - letters) / 2;
        return pointB + half + 1;
    }

    int clamp(int min, int val, int max)
    {
        if (val < min) return min;
        if (val > max) return max;
        return val;
    }

    template< typename TYPE >
    void text(float x, float y, TYPE message, int color)
    {
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        COORD coord;

        x += RENDERSTATE.width / 2.f;
        y += RENDERSTATE.height / 2.f;

        coord.X = x;
        coord.Y = y;

        SetConsoleCursorPosition(hConsole, coord); 
        SetConsoleTextAttribute(hConsole, color);
        std::cout << message << std::endl; 
    }

    void WindowInit() 
    {
        system("cls");
        HANDLE hOut;
        CONSOLE_SCREEN_BUFFER_INFO SBInfo;
        COORD NewSBSize;

        SetConsoleTitleA("Window Name");
        ShowConsoleCursor(false);   

        RENDERSTATE.width = window_width();
        RENDERSTATE.height = window_height();          
        RENDERSTATE.size = RENDERSTATE.width * RENDERSTATE.height * sizeof(unsigned int); 

        hOut = GetStdHandle(STD_OUTPUT_HANDLE);

        GetConsoleScreenBufferInfo(hOut, &SBInfo);
        NewSBSize.X = RENDERSTATE.width;
        NewSBSize.Y = RENDERSTATE.height;

        SetConsoleScreenBufferSize(hOut, NewSBSize);
    }

    void WindowBuffer() 
    {        
        if (RENDERSTATE.width != window_width() || RENDERSTATE.height != window_height())
        {
            system("cls");
            RENDERSTATE.changed_buffer = true;
            ShowConsoleCursor(false);  

            HANDLE hOut;
            CONSOLE_SCREEN_BUFFER_INFO SBInfo;
            COORD NewSBSize;

            RENDERSTATE.width = window_width();
            RENDERSTATE.height = window_height(); 
            
            hOut = GetStdHandle(STD_OUTPUT_HANDLE);

            NewSBSize.X = RENDERSTATE.width;
            NewSBSize.Y = RENDERSTATE.height;
            SetConsoleScreenBufferSize(hOut, NewSBSize);
        }
    } 

    int checker(int &cord, int size_cord)
    {
        if (cord < 0)
            return cord = 0;       
        else if (cord >= size_cord)
            return cord = size_cord - 1;
        else      
            return cord;
    }   
};

MainWindow Main_Window;

#endif /* MAINWINDOW_H_INCLUDED */// 120 30