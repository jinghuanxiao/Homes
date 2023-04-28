#include "ProcessManage.h"

// ��ȡ����ʵ��
ProcessMonitor& ProcessMonitor::getInstance() {
    static ProcessMonitor instance;
    return instance;
}

// ע��Ҫ��صĽ���
void ProcessMonitor::registerProcess(const std::string& process_name, const std::string& command) {
    std::lock_guard<std::mutex> lock(processes_mutex);
    auto process_info = std::make_shared<ProcessInfo>();
    process_info->process_name = process_name;
    process_info->command = command;
    process_info->epoll_fd = epoll_create1(0);
    process_info->pid = 0;
    processes[process_name] = process_info;
}

// ��������
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


// ��ؽ���״̬����������Ҫ��������
void ProcessMonitor::monitor() {
    // ����ѭ���Գ�����ؽ���״̬
    while (true) {
        // �ȴ�1�룬�Ա�ÿ����һ�ν���״̬
        sleep(1);

        // �Խ��������������Ա����ڼ��״̬ʱ�����̶߳�������޸�
        std::lock_guard<std::mutex> lock(processes_mutex);

        // ������ע��Ľ�����Ϣ
        for (auto& kv : processes) {
            auto& process_info = kv.second;

            // �洢waitpid�������ص�״̬��Ϣ
            int status;

            // ʹ��WNOHANGѡ��������ؼ�����״̬
            pid_t result = waitpid(process_info->pid, &status, WNOHANG);

            if (result == 0) {
                // ������������
                // �ڴ˴�������ӽ��̸������Ĵ�ӡ�߼�
            }
            else if (result == process_info->pid) {
                // ��������ֹ����Ҫ����
                restartProcess(process_info);
            }
            else {
                // ������״̬ʱ��������
                std::cerr << "Error checking process status for " << process_info->process_name << std::endl;
            }
        }
    }
}

