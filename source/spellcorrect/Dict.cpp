#include "../../include/spellcorrect/Dict.h"
#include <iostream>
#include <fstream>
#include <sstream>
using std::cout;
using std::endl;
namespace SPELLCORRECT
{
    Dict *Dict::_pInstance = nullptr;

    Dict *Dict::getInstance()
    {
        if (_pInstance == nullptr)
            _pInstance = new Dict;
        return _pInstance;
    }

    void Dict::initDict(const char *cn_file_path, const char *en_file_path)
    {
        // 读取字典文件
        readDictFile(en_file_path);

        readDictFile(cn_file_path);

        // 创建索引列表

        for (size_t idx = 0; idx < _vecDict.size(); idx++)
        {
            createWordIndex(idx);
        }
        cout << "_mapIndexTable size: " << _mapIndexTable.size() << endl;
    }

    void Dict::readDictFile(const char *file_path)
    {
        std::ifstream in(file_path);
        if (!in) // 打开文件失败
        {
            cout << "epen dict file err, time: " << __DATE__ << " " << __TIME__
                 << __FILE__ << " " << __LINE__ << endl;
            exit(-1);
        }

        string line;
        while (getline(in, line))
        {
            std::stringstream ss(line);
            string str;
            int val;
            ss >> str >> val;
            _vecDict.push_back(make_pair(str, val));
        }
        in.close();
    }

    void Dict::createWordIndex(int idx)
    {
        std::string key;
        std::string word = _vecDict[idx].first;
        for (std::size_t iidx = 0; iidx != word.size(); ++iidx)
        {
            char ch = word[iidx];
            if (ch & (1 << 7))
            { //存储utf-8编码的中文字符
                if ((ch & 0xF0) == 0xC0 || (ch & 0xF0) == 0xD0)
                {
                    key = word.substr(iidx, 2);
                    ++iidx;
                }
                else if ((ch & 0xF0) == 0xE0)
                {
                    key = word.substr(iidx, 3);
                    iidx += 2;
                }
                else if ((ch & 0xFF) == 0xF0 ||
                         (ch & 0xFF) == 0xF1 ||
                         (ch & 0xFF) == 0xF2 ||
                         (ch & 0xFF) == 0xF3 ||
                         (ch & 0xFF) == 0xF4 ||
                         (ch & 0xFF) == 0xF5 ||
                         (ch & 0xFF) == 0xF6 ||
                         (ch & 0xFF) == 0xF7)
                {
                    key = word.substr(iidx, 4);
                    iidx += 3;
                }
                else if ((ch & 0xFF) == 0xF8 ||
                         (ch & 0xFF) == 0xF9 ||
                         (ch & 0xFF) == 0xFA ||
                         (ch & 0xFF) == 0xFB)
                {
                    key = word.substr(iidx, 5);
                    iidx += 4;
                }
                else if ((ch & 0xFF) == 0xFC)
                {
                    key = word.substr(iidx, 6);
                    iidx += 5;
                }
            }
            else
            {
                key = word.substr(iidx, 1);
            }
            _mapIndexTable[key].insert(idx);
        }
    }
    void Dict::showDict()
    {
        auto iter = _vecDict.begin();
        for (; iter != _vecDict.end(); ++iter)
        {
            std::cout << iter->first << "-->"
                      << iter->second << std::endl;
        }
    }
    void Dict::showWordIndex()
    {
        auto iter = _mapIndexTable.begin();
        for (; iter != _mapIndexTable.end(); ++iter)
        {
            std::cout << iter->first << "-->";
            auto sit = iter->second.begin();
            for (; sit != iter->second.end(); ++sit)
            {
                std::cout << *sit << " ";
            }
            std::cout << std::endl;
        }
    }

    Dict::VecDict Dict::getDict()
    {
        return _vecDict;
    }
    Dict::MapIndexTable Dict::getIndexTable()
    {
        return _mapIndexTable;
    }

} // SPELLCORRECT