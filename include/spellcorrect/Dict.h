#ifndef __DICT_H__
#define __DICT_H__

#include <string>
#include <vector>
#include <set>
#include <utility>
#include <map>

using std::map;
using std::pair;
using std::set;
using std::string;
using std::vector;
namespace SPELLCORRECT {
class Dict {
public:
    static Dict *getInstance();
    void initDict(const char *cn_file_path, const char *en_file_path);
    void showDict();
    void showWordIndex();

private:
    Dict() {
    }                                         //构造函数私有化
    void readDictFile(const char *file_path); // 读取字典文件
    void createWordIndex(int idx);            // 创建单词的索引表
public:
    using VecDict = vector<pair<string, int>>; // word frequency
    // w idx,这个inx对应VecDict的下标，表示set里面的所有下标都有元素w
    // VecDict可以直接通过这个下标访问到单词
    using MapIndexTable = map<string, set<int>>;
    VecDict getDict();
    MapIndexTable getIndexTable();

private:
    static Dict *_pInstance;
    VecDict _vecDict;
    MapIndexTable _mapIndexTable;
};

} // namespace SPELLCORRECT

#endif