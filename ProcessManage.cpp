#include "ProcessManage.h"

// 获取单例实例
ProcessMonitor& ProcessMonitor::getInstance() {
    static ProcessMonitor instance;
    return instance;
}

// 注册要监控的进程
void ProcessMonitor::registerProcess(const std::string& process_name, const std::string& command) {
    std::lock_guard<std::mutex> lock(processes_mutex);
    auto process_info = std::make_shared<ProcessInfo>();
    process_info->process_name = process_name;
    process_info->command = command;
    process_info->epoll_fd = epoll_create1(0);
    process_info->pid = 0;
    processes[process_name] = process_info;
}

// 启动进程
void ProcessMonitor::startProcess(std::shared_ptr<ProcessInfo> process_info) {
    pid_t pid = fork();
    if (pid == 0) {
        // Child process
        system(process_info->command.c_str());
        exit(0);
    }
    else if (pid > 0) {
        // Parent process
        process_info->pid = pid;
    }
    else {
        // Error
        std::cerr << "Failed to fork process for " << process_info->process_name << std::endl;
    }
}


// 监控进程状态，并根据需要重启进程
void ProcessMonitor::monitor() {
    // 无限循环以持续监控进程状态
    while (true) {
        // 等待1秒，以便每秒检查一次进程状态
        sleep(1);

        // 对进程容器上锁，以避免在检查状态时其他线程对其进行修改
        std::lock_guard<std::mutex> lock(processes_mutex);

        // 遍历已注册的进程信息
        for (auto& kv : processes) {
            auto& process_info = kv.second;

            // 存储waitpid函数返回的状态信息
            int status;

            // 使用WNOHANG选项非阻塞地检查进程状态
            pid_t result = waitpid(process_info->pid, &status, WNOHANG);

            if (result == 0) {
                // 进程仍在运行
                // 在此处可以添加进程负载量的打印逻辑
            }
            else if (result == process_info->pid) {
                // 进程已终止，需要重启
                restartProcess(process_info);
            }
            else {
                // 检查进程状态时发生错误
                std::cerr << "Error checking process status for " << process_info->process_name << std::endl;
            }
        }
    }
}

