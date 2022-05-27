#include "../../include/spellcorrect/EditDistance.h"
#include <iostream>
#include <string>
using std::string;

// UTF-8编码  一个字符可能占一个字节也可能占6个字节
// 获取一个字符高位开头为1的个数。1的个数就代表了这个字符占了多少字节
// 一个中午字符占三个字节
size_t getBytes(const char ch) {
    if (ch & (1 << 7)) {
        int nBytes = 1;
        for (int idx = 0; idx != 6; ++idx) {
            if (ch & (1 << (6 - idx))) {
                ++nBytes;
            } else
                break;
        }
        return nBytes;
    }
    return 1;
}
// 获取字符串长度
std::size_t length(const std::string &str) {
    std::size_t ilen = 0;
    for (std::size_t idx = 0; idx != str.size();) {
        int nBytes = getBytes(str[idx]);
        idx += nBytes;
        ++ilen;
    }
    return ilen;
}

int triple_min(const int &a, const int &b, const int &c) {
    return a < b ? (a < c ? a : c) : (b < c ? b : c);
}

int getMinEditDistance(const std::string &lhs, const std::string &rhs) {
    //计算最小编辑距离-包括处理中英文，都按照字符的方式处理
    size_t lhs_len = length(lhs);
    size_t rhs_len = length(rhs);
    int editDist[lhs_len + 1][rhs_len + 1];
    for (size_t idx = 0; idx <= lhs_len; ++idx) { editDist[idx][0] = idx; }

    for (size_t idx = 0; idx <= rhs_len; ++idx) { editDist[0][idx] = idx; }

    std::string sublhs, subrhs;
    for (std::size_t dist_i = 1, lhs_idx = 0; dist_i <= lhs_len;
         ++dist_i, ++lhs_idx) {
        size_t nBytes = getBytes(lhs[lhs_idx]);
        sublhs = lhs.substr(lhs_idx, nBytes);
        lhs_idx += (nBytes - 1);

        for (std::size_t dist_j = 1, rhs_idx = 0; dist_j <= rhs_len;
             ++dist_j, ++rhs_idx) {
            nBytes = getBytes(rhs[rhs_idx]);
            subrhs = rhs.substr(rhs_idx, nBytes);
            rhs_idx += (nBytes - 1);
            if (sublhs == subrhs) {
                editDist[dist_i][dist_j] = editDist[dist_i - 1][dist_j - 1];
            } else {
                editDist[dist_i][dist_j] =
                    triple_min(editDist[dist_i][dist_j - 1] + 1,
                               editDist[dist_i - 1][dist_j] + 1,
                               editDist[dist_i - 1][dist_j - 1] + 1);
            }
        }
    }
    return editDist[lhs_len][rhs_len];
}

// void test()
// {
//     std::string s1 = "中国人";
//     std::string s2 = "abc中国";
//     std::cout << "s1 size: " << s1.size() << std::endl; // 9 都是9个字节
//     std::cout << "s2 size: " << s2.size() << std::endl; // 9

//     std::cout << "s1 length: " << length(s1) << std::endl; // 长度为3
//     std::cout << "s2 size: " << length(s2) << std::endl;   // 长度为5
//     std::cout << "s1 to s2 edit distance: " << getMinEditDistance(s1, s2) <<
//     std::endl;   // s1变为s2, 经过4步
// }