#ifndef telExceptionH
#define telExceptionH
#include <exception>
#include <string>
#include "telExporter.h"

using std::string;
using std::exception;

namespace tlp
{

class RRP_DECLSPEC Exception : public std::exception
{
    protected:
        string mMessage;   //Exception message

    public:
        //string& Message;
                                Exception(const string& desc);
        virtual                ~Exception() throw();
        virtual const char*     what() const throw();
        string                  Message() const;
        string                  getMessage() const;
};

class RRP_DECLSPEC BadHandleException : public Exception
{
    public:
        BadHandleException(const string& msg);
        BadHandleException(const string& msg1, const string& msg2);
};

}//namepsace rr
#endif
