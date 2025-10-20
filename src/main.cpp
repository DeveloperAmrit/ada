#include <iostream>
#include <string>

// Include command headers
#include "init.h"
#include "add.h"
#include "commit.h"
#include "status.h"
#include "log.h"

int main(int argc, char* argv[]){
    if(argc<2){
        std::cout << "Usage: ada <command> [options]\n";
        std::cout << "Commands: init | add | commit | status | log\n";
        return 1;
    }

    std::string command = argv[1];

    if(command == "init"){
        ada_init();
    }
    else if(command == "add"){
        ada_add();
    }
    else if(command == "commit"){
        ada_commit();
    }
    else if(command == "status"){
        ada_status();
    }
    else if(command == "log"){
        ada_log();
    }
    else{
        std::cout << "Unknown command: " << command << "\n";
    }

    return 0;

}

