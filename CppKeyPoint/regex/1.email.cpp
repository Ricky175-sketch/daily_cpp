#include <regex>
#include <iostream>

int main() {
    std::string email = "example.email+123@example.com";
    std::regex reg("^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\\.[a-zA-Z]{2,}$");
    std::cout << std::regex_match(email, reg) << std::endl; // 输出 1，匹配成功

    return 0;
}