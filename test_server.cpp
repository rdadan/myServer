#include "./include/spellcorrect/SpellCorrectServer.h"
#include <iostream>

int main(void)
{
    SPELLCORRECT::SpellCorrectServer server;
    
    server.start();
    return 0;
}
