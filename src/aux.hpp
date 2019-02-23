#ifndef AUX_HPP
#define AUX_HPP

#include <exception>

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
