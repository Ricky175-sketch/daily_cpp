#include <Windows.h>
#include <iostream>

int main()
{
    // 打开共享内存
    HANDLE hMapFile = OpenFileMapping(
        FILE_MAP_ALL_ACCESS,     // 可读可写
        FALSE,                   // 不继承句柄
        TEXT("MySharedMemory"));      // 共享内存名称

    if (hMapFile == NULL)
    {
        std::cerr << "Failed to open shared memory!" << std::endl;
        return 1;
    }

    // 映射共享内存
    LPVOID lpBase = MapViewOfFile(
        hMapFile,                // 共享内存句柄
        FILE_MAP_ALL_ACCESS,     // 可读可写
        0,                       // 偏移量（高位）
        0,                       // 偏移量（低位）
        1024);                   // 映射内存大小

    // 读取共享内存
    char* pData = (char*)lpBase;
    std::cout << pData << std::endl;

    // 解除共享内存映射
    UnmapViewOfFile(lpBase);

    // 关闭共享内存句柄
    CloseHandle(hMapFile);

    return 0;
}