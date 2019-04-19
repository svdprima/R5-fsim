#ifndef AUX_HPP
#define AUX_HPP

#include <exception>
#include <stdint.h>

#define MAX_INSTR 10000000000

class FinishException: public std::exception
{
private:
    const char* message;
public:
    FinishException (const char* msg)
    {
        message = msg;   
    };
    const char* what()
    {
        return message;
    }
};
class DummyException: public std::exception
{
private:
    const char* message;
public:
    DummyException (const char* msg)
    {
        message = msg;   
    };
    const char* what()
    {
        return message;
    }
};
class CalcException: public std::exception
{
private:
    const char* message;
public:
    CalcException (const char* msg)
    {
        message = msg;   
    };
    const char* what()
    {
        return message;
    }
};
class RegException: public std::exception
{
private:
    const char* message;
public:
    RegException (const char* msg)
    {
        message = msg;   
    };
    const char* what()
    {
        return message;
    }
};
class OutOfMemException: public std::exception
{
private:
    const char* message;
    uint64_t pa;
public:
    OutOfMemException (const char* msg, uint64_t pa_)
    {
        message = msg;
        pa = pa_;
    };
    const char* what()
    {
        return message;
    }
    uint64_t GetPa()
    {
    	return pa;
    }
};
class UnalignException: public std::exception
{
private:
    const char* message;
    uint64_t pa;
public:
    UnalignException (const char* msg, uint64_t pa_)
    {
        message = msg;
        pa = pa_;
    };
    const char* what()
    {
        return message;
    }
    uint64_t GetPa()
    {
    	return pa;
    }
};
class PageFaultException: public std::exception
{
private:
    const char* message;
    uint32_t pte;
    uint64_t pte_addr;

public:
    PageFaultException (const char* msg, uint32_t pte_, uint64_t pte_addr_)
    {
        message = msg;
        pte = pte_;
        pte_addr = pte_addr_;
    };
    const char* what()
    {
        return message;
    }
    uint32_t GetPte()
    {
    	return pte;
    }
    uint64_t GetPteAddr()
    {
    	return pte_addr;
    }
};

#endif
