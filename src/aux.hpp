#ifndef AUX_HPP
#define AUX_HPP

#include <exception>

#define MAX_INSTR 100000000

class HartException: public std::exception
{
private:
    const char* message;
public:
    HartException (const char* msg)
    {
        message = msg;   
    };
    const char* what()
    {
        return message;
    }
};

#endif
