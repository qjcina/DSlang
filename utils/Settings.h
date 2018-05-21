//
// Created by qj on 21.05.18.
//

#ifndef PROJECT_SETTINGS_H
#define PROJECT_SETTINGS_H


#include <vector>
#include "ArgumentParser.h"

class Settings {
private:
    const ArgumentParser* args;
    void onInitArgs();
public:
    Settings(ArgumentParser* argumentParser);
};


#endif //PROJECT_SETTINGS_H
