#include "Subfunctions.h"

#include <algorithm>
#include <cctype>
#include <functional>
#include <locale>
#include <regex>
#include <sstream>
#include <string>
#include <vector>

std::vector<std::string> Split(const char& delimiter, const std::string& input)
{
    std::stringstream ss(input);
    std::vector<std::string> result;
    std::string item;
    while (std::getline(ss, item, delimiter))
    {
        result.push_back(item);
    }
    return result;
}

std::vector<std::string> SplitExamFile(const std::string& delimiters, const std::string& input)
{
    std::vector<std::string> resultIntermediary;
    std::vector<std::string> result;

    if (input.size() == 0)
    {
        return resultIntermediary;
    }

    size_t prevRes = 0;
    size_t res = input.find_first_of(delimiters);
    while (res != std::string::npos)
    {
        resultIntermediary.push_back(input.substr(prevRes, res - prevRes));
        prevRes = res++;
        res = input.find_first_of(delimiters, res);
    }
    resultIntermediary.push_back(input.substr(prevRes));

    for_each(
        resultIntermediary.begin(),
        resultIntermediary.end(),
        [&](std::string& s)
        {
            s.erase(0, s.find_first_not_of(delimiters));
            s.erase(s.find_last_not_of(delimiters) + 1);
            if (s.find_first_of(delimiters) == std::string::npos && s != "")
            {
                result.push_back(s);
            }
        });

    return result;
}