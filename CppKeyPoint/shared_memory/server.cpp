#include <Windows.h>

int main()
{
    // 创建共享内存
    HANDLE hMapFile = CreateFileMapping(
        INVALID_HANDLE_VALUE, // 使用无效的句柄作为文件句柄
        NULL,                 // 默认安全级别
        PAGE_READWRITE,       // 可读可写
        0,                    // 内存大小（高位）
        1024,                 // 内存大小（低位）
        L"MySharedMemory");   // 共享内存名称

    // 映射共享内存
    LPVOID lpBase = MapViewOfFile(
        hMapFile,            // 共享内存句柄
        FILE_MAP_ALL_ACCESS, // 可读可写
        0,                   // 偏移量（高位）
        0,                   // 偏移量（低位）
        1024);               // 映射内存大小

    // 写入共享内存
    char *pData = (char *)lpBase;
    strcpy_s(pData, 1024, "Hello, shared memory!");

    // 解除共享内存映射
    UnmapViewOfFile(lpBase);

    // 关闭共享内存句柄
    CloseHandle(hMapFile);

    return 0;
}