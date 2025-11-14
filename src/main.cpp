#include <iostream>
#include <string>

// Include command headers
#include "init.h"
#include "add.h"
#include "commit.h"
#include "status.h"
#include "log.h"
#include "config.h"
#include "remote.h"
#include "push.h"
#include "pull.h"

int main(int argc, char* argv[]){
    if(argc<2){
        std::cout << "Usage: ada <command> [options]\n";
        std::cout << "Commands:\n";
        std::cout << "  init             Initialize a new ada repository\n";
        std::cout << "  add <file>       Add file to staging area\n";
        std::cout << "  commit           Create a new commit\n";
        std::cout << "  status           Show working tree status\n";
        std::cout << "  log              Show commit history\n";
        std::cout << "  config           Get and set repository or global options\n";
        std::cout << "  remote           Manage remote repositories\n";
        std::cout << "  push             Push commits to remote repository\n";
        std::cout << "  pull             Pull commits from remote repository\n";
        return 1;
    }

    std::string command = argv[1];

    if(command == "init"){
        ada_init();
    }
    else if(command == "add"){
        if(argc < 3){
            std::cerr << "Usage: ada add <file>\n";
            return 1;
        }
        std::string filePath = argv[2];
        ada_add(filePath);
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
    else if(command == "config"){
        ada_config(argc, argv);
    }
    else if(command == "remote"){
        ada_remote(argc, argv);
    }
    else if(command == "push"){
        ada_push();
    }
    else if(command == "pull"){
        ada_pull();
    }
    else if(command == "--version" || command == "-v"){
        std::cout << "ada version 1.0.0\n";
        std::cout << "A simple version control system\n";
    }
    else if(command == "--help" || command == "-h"){
        std::cout << "Ada Version Control System\n\n";
        std::cout << "Usage: ada <command> [options]\n\n";
        std::cout << "Getting Started:\n";
        std::cout << "  ada init                              Initialize repository\n";
        std::cout << "  ada config --global user.name <name>  Set your name\n";
        std::cout << "  ada config --global user.email <email> Set your email\n\n";
        std::cout << "Basic Commands:\n";
        std::cout << "  ada add <file>                        Add file to staging\n";
        std::cout << "  ada commit                            Create a commit\n";
        std::cout << "  ada status                            Show status\n";
        std::cout << "  ada log                               Show commit history\n\n";
        std::cout << "GitHub Integration:\n";
        std::cout << "  ada config --global github.token <token>    Set GitHub token\n";
        std::cout << "  ada config --global github.username <user>  Set GitHub username\n";
        std::cout << "  ada remote add origin <url>                 Add remote\n";
        std::cout << "  ada push                                     Push to GitHub\n";
        std::cout << "  ada pull                                     Pull from GitHub\n";
    }
    else{
        std::cout << "Unknown command: " << command << "\n";
        std::cout << "Run 'ada --help' for usage information.\n";
    }

    return 0;

}

