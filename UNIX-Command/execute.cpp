#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>

// Compiled with: g++ --std=c++11

std::string execute(std::string command)
{
    /* Execute passed command as a string and returns output */

    std::string data;
    FILE * stream;
    char buffer[256];
    command.append(" 2>&1");

    stream = popen(command.c_str(), "r");
    if (stream)
    {
        while (!feof(stream))
            if (fgets(buffer, 256, stream) != NULL) data.append(buffer);
                pclose(stream);
        }
    return data;
}

int main()
{
    std::string name = execute("whoami");           // get user name
    std::cout<<name<<std::endl;
    return 0;
}
