#include <iostream>
#include <sstream>
#include <string>
#include "Scheduler.h"

int main() {
    Scheduler scheduler;

    std::cout << "Array-based Heap Job Scheduler\n"
              << "Commands:\n"
              << "  add <name> <priority> <duration> [deadline]\n"
              << "  tick <time>\n"
              << "  next\n"
              << "  runall\n"
              << "  cancel <id>\n"
              << "  ready\n"
              << "  done\n"
              << "  stats\n"
              << "  exit\n";

    std::string line;
    while (true) {
        std::cout << "\n> ";
        if (!std::getline(std::cin, line)) break;  // EOF

        if (line.empty()) continue;

        std::istringstream iss(line);
        std::string cmd;
        iss >> cmd;
        if (!iss) continue; 

        if (cmd == "add") {
            std::string name;
            int priority, duration;
            int deadline = -1;

            if (!(iss >> name >> priority >> duration)) {
                std::cout << "Usage: add <name> <priority> <duration> [deadline]\n";
                continue;
            }

            if (iss >> deadline) {

            }

            std::string extra;
            if (iss >> extra) {
                std::cout << "Warning: extra tokens ignored after deadline.\n";
            }

            scheduler.addJob(name, priority, duration, deadline);
        }
        else if (cmd == "tick") {
            int t;
            if (!(iss >> t)) {
                std::cout << "Usage: tick <time>\n";
                continue;
            }
            scheduler.tick(t);
        }
        else if (cmd == "next") {
            scheduler.runNext();
        }
        else if (cmd == "runall") {
            scheduler.runAll();
        }
        else if (cmd == "cancel") {
            int id;
            if (!(iss >> id)) {
                std::cout << "Usage: cancel <id>\n";
                continue;
            }
            scheduler.cancelJob(id);
        }
        else if (cmd == "ready") {
            scheduler.printReadyQueue();
        }
        else if (cmd == "done") {
            scheduler.printCompletedJobs();
        }
        else if (cmd == "stats") {
            scheduler.printStats();
        }
        else if (cmd == "exit") {
            break;
        }
        else {
            std::cout << "Unknown command: " << cmd << "\n";
            std::cout << "Available commands: add, tick, next, runall, cancel, ready, done, stats, exit\n";
        }
    }

    return 0;
}