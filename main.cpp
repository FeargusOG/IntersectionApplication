#include <iostream>
#include "IntersectionApplication.hpp"

int main(int argc, char **argv)
{
    if(argc >= 2)
    {
        try
        {
            IntersectionApplication app;
            app.execute(argv[1]);
            
            /* If provided an output file, print to that. */
            if(argc == 3)
            {
               app.printOutputToFile(argv[2]); 
            }
            else
            {
                app.printOutputToConsole();
            }
        }
        catch(const std::exception &ex)
        {
            std::cout<<"Terminating program on Exception."<<std::endl;
            return -1;
        }
    }
    else
    {
        std::cout<<"This program requires at least a json filename as input e.g. IntersectionApplication sample.json"<<std::endl;
    }
    
	return 0;
}