#include <iostream>
#include <vector>
#include <thread>
#include <chrono>
#include <omp.h>
#include <string>
#include <fstream>
#include <sstream>

class App {
public:
    int id;
    int iterations;
    int sleep_time; 

    App(int id, int iters = 100, int sleep_ms = 100) : id(id), iterations(iters), sleep_time(sleep_ms) {}

    void execute() {
        for (int i = 0; i < iterations; ++i) {
            std::this_thread::sleep_for(std::chrono::milliseconds(sleep_time));
        }
        std::cout << "App " << id << " completed."<<std::endl;
    }
};

std::vector<App> tasks;

void add_task(int id, int iterations = 100, int sleep_time = 100) {
    tasks.emplace_back(id, iterations, sleep_time);
}

void loadTasksFromFile(const std::string& filePath) {
    int task_counter = 1;  
    std::ifstream file(filePath);
    std::string line;
    while (getline(file, line)) {
        if (line.empty()) continue;  

        std::istringstream iss(line);
        std::string taskId;
        iss >> taskId;
        if (taskId == "0" || taskId == "exit") {
            break;
        } else if (taskId == "1" || taskId == "2") {
            int iterations = 31, sleep_time = 120;
            if (taskId == "2") {
                iterations = 41;
                sleep_time = 140;
            }
            #pragma omp parallel sections
            {
                #pragma omp section
                {
                    add_task(task_counter++, iterations, sleep_time);
                    tasks.back().execute();
                }
            }
        }
    }
    file.close();
    std::cout << "Exiting..."<<std::endl;
}

void handleTasksFromConsole() {
    int task_counter = 1;  
    std::string taskId;

    std::cout << "Enter commands (1 = first task, 2 = second task, 0 or 'exit' to quit): "<<std::endl;
    while (true) {
        std::cin >> taskId;
        if (taskId == "0" || taskId == "exit") {
            break;
        } else if (taskId == "1" || taskId == "2") {
            int iterations = 31, sleep_time = 120;
            if (taskId == "2") {
                iterations = 41;
                sleep_time = 140;
            }
            #pragma omp parallel sections
            {
                #pragma omp section
                {
                    add_task(task_counter++, iterations, sleep_time);
                    tasks.back().execute();
                }
            }
        }
    }
    std::cout << "Exiting..."<<std::endl;
}

int main(int argc, char* argv[]) {
    if (argc > 1) {
        std::string arg1 = argv[1];
        if (arg1 == "-cmd") {
            handleTasksFromConsole();
        } else if (arg1 == "-file" && argc > 2) {
            loadTasksFromFile(argv[2]);
        } else {
            std::cerr << "Invalid arguments. Usage:\n"
                      << "./TaskManager -cmd\n"
                      << "./TaskManager -file file_path"<<std::endl;
            return 1;
        }
    } else {
        std::cerr << "No arguments provided. Usage:\n"
                  << "./TaskManager -cmd\n"
                  << "./TaskManager -file file_path"<<std::endl;
        return 1;
    }
    return 0;
}