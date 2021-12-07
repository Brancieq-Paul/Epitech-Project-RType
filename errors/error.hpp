/*
** EPITECH PROJECT, 2020
** Errors
** File description:
** Errors
*/

#ifndef ERROR_HPP_
#define ERROR_HPP_

#include <exception>
#include <iostream>
#include <sstream>

class ConcatOnTheFly
{
    public:
        template<class Val> ConcatOnTheFly& operator<<(const Val& val)
        {
            ss_ << val;
            return * this;
        }
        operator std::string () const { return ss_.str().c_str(); }
    private:
        std::stringstream ss_;
};

class Error : public std::exception {
    public:
        Error(std::string msg, const char *file, int line)
            : _msg(msg), _file(file), _line(line) {}
        ~Error() = default;

    const char *what() const noexcept {return _msg.c_str();}
    const char *where() const noexcept {return _file;}
    int on() const noexcept {return _line;}

    private:
        std::string _msg;
        const char *_file;
        int _line;
};

#endif
