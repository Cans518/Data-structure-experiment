#include <iostream>
#include "KMP.hpp"

int main() {
    // 测试文本和模式
    std::string text = "ababcababdabcABABABD";
    std::string pattern = "ABABD";
    
    // 创建KMP对象，设置大小写不敏感
    KMP kmp_no_case_sensitive(pattern, false);
    KMP kmp_case_sensitive(pattern, true);
    
    // 执行搜索
    std::vector<int> no_case_sensitive_matches = kmp_no_case_sensitive.search(text);
    std::vector<int> case_sensitive_matches = kmp_case_sensitive.search(text);

    // 输出匹配结果
    std::cout << "Case-insensitive matches: " << std::endl;
    for (int i : no_case_sensitive_matches) {
        std::cout << "Match at index: " << i << std::endl;
    }
    std::cout << "Case-sensitive matches: " << std::endl;
    for (int i : case_sensitive_matches) {
        std::cout << "Match at index: " << i << std::endl;
    }

    return 0;
}
