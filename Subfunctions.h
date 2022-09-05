#ifndef SUBFUNCTIONS_H
#define SUBFUNCTIONS_H

#include <string>
#include <vector>

std::vector<std::string> Split(const char&, const std::string&);

std::vector<std::string> SplitExamFile(const std::string&, const std::string&);

inline std::string& TrimLeft(const std::string& delimiters, std::string& s)
{
    s.erase(0, s.find_first_not_of(delimiters));
    return s;
}

inline std::string& TrimRight(const std::string& delimiters, std::string& s)
{
    s.erase(s.find_last_not_of(delimiters) + 1);
    return s;
}

#endif // SUBFUNCTIONS_H