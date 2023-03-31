#include <iostream>
#include <regex>
#include <string>

int main() {
    std::string str = "Hello, world! My email is john@example.com. My phone number is (123) 456-7890.";

    // 匹配邮箱
    std::regex email_regex("[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\\.[a-zA-Z]{2,}");
    std::smatch email_match;
    if (std::regex_search(str, email_match, email_regex)) {
        std::cout << "Email found: " << email_match.str() << std::endl;
    } else {
        std::cout << "Email not found." << std::endl;
    }

    // 匹配电话号码
    std::regex phone_regex("\\(\\d{3}\\)\\s\\d{3}-\\d{4}");
    std::smatch phone_match;
    if (std::regex_search(str, phone_match, phone_regex)) {
        std::cout << "Phone number found: " << phone_match.str() << std::endl;
    } else {
        std::cout << "Phone number not found." << std::endl;
    }

    // 替换字符串
    std::regex replace_regex("world");
    std::string replaced_str = std::regex_replace(str, replace_regex, "C++");
    std::cout << "Replaced string: " << replaced_str << std::endl;

    // 切割字符串
    std::regex split_regex("\\s|,");
    std::sregex_token_iterator it(str.begin(), str.end(), split_regex, -1);
    std::sregex_token_iterator end;
    std::cout << "Splitted string: ";
    for (; it != end; ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    return 0;
}