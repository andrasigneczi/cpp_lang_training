#ifndef __STRINGUTIL_H__
#define __STRINGUTIL_H__
#pragma once

#include <string>
#include <vector>

class StringUtil
{
public:
    static std::string trim(const std::string& str);
    static std::vector<std::string> split(const std::string s, char sep, bool trim);
};

#endif // STRINGUTIL_H
