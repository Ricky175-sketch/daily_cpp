#ifndef THREAD_H
#define THREAD_H
#include <thread>

class Thread
{
public:
    Thread(); // ���캯��
    virtual ~Thread(); // ��������
    bool start();
    void stop();
    bool isAlive() const; // �߳��Ƿ���.
    std::thread::id id() { return _th->get_id(); }
    std::thread* getThread() { return _th; }
    void join();  // �ȴ���ǰ�߳̽���, �����ڵ�ǰ�߳��ϵ���
    void detach(); //���ڵ�ǰ�߳��ϵ���
    static size_t CURRENT_THREADID();
protected:
    static void threadEntry(Thread* pThread); // ��̬����, �߳����
    virtual void run() = 0; // ����
protected:
    bool  _running; //�Ƿ�������
    std::thread* _th;
};

#endif // THREAD_H
