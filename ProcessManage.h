#pragma once
#include <iostream>
#include <memory>
#include <unordered_map>
#include <vector>
#include <string>
#include <mutex>
#include <sys/epoll.h>
#include <sys/wait.h>
#include <unistd.h>

class ProcessMonitor {
public:
    // 获取单例实例
    static ProcessMonitor& getInstance();
    ProcessMonitor(const ProcessMonitor&) = delete;
    ProcessMonitor& operator=(const ProcessMonitor&) = delete;

    // 注册要监控的进程
    void registerProcess(const std::string& process_name, const std::string& command);
    // 监控进程状态，并根据需要重启进程
    void monitor();

private:
    // 构造函数和析构函数设置为私有
    ProcessMonitor() = default;
    ~ProcessMonitor() = default;

    // 进程信息结构体
    struct ProcessInfo {
        std::string process_name;
        std::string command;
        int epoll_fd;
        pid_t pid;
    };

    // 启动进程
    void startProcess(std::shared_ptr<ProcessInfo> process_info);
    // 重启进程
    void restartProcess(std::shared_ptr<ProcessInfo> process_info);

    // 存储进程信息的容器
    std::unordered_map<std::string, std::shared_ptr<ProcessInfo>> processes;
    std::mutex processes_mutex;
};


