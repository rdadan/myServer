#ifndef __EDITDISTANCE_H__
#define __EDITDISTANCE_H__
#include <string>
using std::string;
struct MyResult
{
    string _word;
    int _iFreq;
    int _iDist;
};
struct MyCompare
{
    bool operator()(const MyResult &lhs, const MyResult &rhs)
    {
        if (lhs._iDist > rhs._iDist)
        {
            return true;
        }
        else if (lhs._iDist == rhs._iDist &&
                 lhs._iFreq < rhs._iFreq)
        {
            return true;
        }
        else if (lhs._iDist == rhs._iDist &&
                 lhs._iFreq == rhs._iFreq &&
                 lhs._word > rhs._word)
        {
            return true;
        }
        else
            return false;
    }
};

/// 获取一个字节高位开头为1的个数
size_t getBytes(const char ch);

std::size_t length(const std::string &str);

int triple_min(const int &a, const int &b, const int &c);

int getMinEditDistance(const std::string &lhs, const std::string &rhs);

#endif