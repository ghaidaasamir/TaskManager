# Task Manager 

Implements a simple task manager in C++ that allows users to execute predefined tasks either through console commands or by loading them from a file. Tasks are executed in parallel using OpenMP.

## Building the Project

1. **Clone the repository**.

2. **Navigate to the project directory** where the `CMakeLists.txt` file is located.

3. **Create a build directory**:
   ```bash
   mkdir build && cd build
   ```

4. **Configure the project with CMake**:
   ```bash
   cmake ..
   ```

5. **Build the project**:
   ```bash
   make
   ```

6. The executable will be named `TaskManager` and located in the `build` directory.

## Running the Project

You can run the Task Manager in two modes:

1. **Command Line Mode**: Allows you to enter tasks interactively via the console.
   ```bash
   ./TaskManager -cmd
   ```
   Use commands `1` or `2` to start specific tasks, and `0` or `exit` to quit.

2. **File Mode**: Executes tasks defined in a specified file.
   ```bash
   ./TaskManager -file [file_path]
   ```
   Each line represents a task configuration.
