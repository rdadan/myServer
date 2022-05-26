#include "./include/spellcorrect/SpellCorrectServer.h"
#include "./include/cache/Cache.h"
#include <iostream>

int main(void)
{
    int threadNum = 2;
    int queSize = 2;
    string cnPath = "/mnt/d/MyProjects/linuxOS/myspellcorrection/file/dict_cn_test.dat";
    string enPath = "/mnt/d/MyProjects/linuxOS/myspellcorrection/file/dict_en_test.dat";
    string cachePath = "/mnt/d/MyProjects/linuxOS/myspellcorrection/file/cache.dat";
    // CACHE::Cache::_filename = cachePath;

    CACHE::Cache cache(threadNum, cachePath);

    SPELLCORRECT::SpellCorrectServer server(threadNum, queSize, cnPath, enPath);

    server.start();
    return 0;
}
