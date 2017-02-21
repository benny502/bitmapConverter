#ifndef EXCEPTION_H
#define EXCEPTION_H

namespace BNDecoder{

    class UnknowException{
        public:
            virtual const char* what(){
                return "UnknowException: ";
            }
    };

    class NotSupportException : public UnknowException{
        public:
            virtual const char* what(){
                return "NotSupportException: ";
            }
    };

    class NotBitmapException : public UnknowException{
        public:
            virtual const char* what(){
                return "NotBitmapException: ";
            }
    };

    class OpenFileFailedException : public UnknowException{
        public:
            virtual const char* what(){
                return "OpenFileFailedException: ";
            }
    };
}

#endif