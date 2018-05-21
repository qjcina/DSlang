//
// Created by qj on 21.05.18.
//

#include <iostream>
#include "Settings.h"
#include "Constants.h"
Settings::Settings(ArgumentParser* argumentParser): args(argumentParser) {
    onInitArgs();
}

void Settings::onInitArgs() {
    if(args->isArg('v')){
        std::cout<<"Version: "<<VERSION_MAJOR<<"."<<VERSION_MINOR<<"."<<VERSION_GIT<<std::endl;
    } else if(args->isArg('u')){
        //TODO: update!
    }

}
