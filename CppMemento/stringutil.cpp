#include "stringutil.h"
#include <sstream>
#include <iostream>

std::vector<std::string> StringUtil::split(const std::string str, char sep, bool trim) {
    std::vector<std::string> strings;
    std::istringstream f(str);
    std::string s;
    while (std::getline(f, s, sep)) {
        if(trim)
            s = StringUtil::trim(s);
        if(s.length() == 0) continue;
        strings.push_back(s);
    }
    return strings;
}

std::string StringUtil::trim(const std::string& str) {
    size_t first = str.find_first_not_of(" \t\n\r\a");
    if (std::string::npos == first) {
        if(str.length() == 0)
            return "";
        switch(str[0]) {
            case ' ': case '\t': case '\n': case '\r': case '\a':
                return "";
            break;
            default:
            break;
        }
        return str;
    }

    size_t last = str.find_last_not_of(" \t\n\r\a");
    return str.substr(first, (last - first + 1));
}

