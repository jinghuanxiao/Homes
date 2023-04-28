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
    // ��ȡ����ʵ��
    static ProcessMonitor& getInstance();
    ProcessMonitor(const ProcessMonitor&) = delete;
    ProcessMonitor& operator=(const ProcessMonitor&) = delete;

    // ע��Ҫ��صĽ���
    void registerProcess(const std::string& process_name, const std::string& command);
    // ��ؽ���״̬����������Ҫ��������
    void monitor();

private:
    // ���캯����������������Ϊ˽��
    ProcessMonitor() = default;
    ~ProcessMonitor() = default;

    // ������Ϣ�ṹ��
    struct ProcessInfo {
        std::string process_name;
        std::string command;
        int epoll_fd;
        pid_t pid;
    };

    // ��������
    void startProcess(std::shared_ptr<ProcessInfo> process_info);
    // ��������
    void restartProcess(std::shared_ptr<ProcessInfo> process_info);

    // �洢������Ϣ������
    std::unordered_map<std::string, std::shared_ptr<ProcessInfo>> processes;
    std::mutex processes_mutex;
};


