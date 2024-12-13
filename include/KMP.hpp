// KMP.hpp
#ifndef KMP_HPP
#define KMP_HPP

#include <vector>
#include <string>
#include <algorithm>

/**
 * @class KMP
 * @brief 实现KMP字符串匹配算法的类
 */
class KMP {
public:
    /**
     * @brief 构造函数
     * @param pattern 要搜索的模式字符串
     * @param caseSensitive 是否大小写敏感
     */
    KMP(const std::string& pattern, bool caseSensitive = true)
        : pattern(pattern), caseSensitive(caseSensitive) {
        if (!caseSensitive) {
            std::transform(this->pattern.begin(), this->pattern.end(), this->pattern.begin(), ::tolower);
        }
        buildLPS();
    }

    /**
     * @brief 搜索文本中的模式字符串
     * @param text 要搜索的文本
     * @return 包含所有匹配起始索引的向量
     */
    std::vector<int> search(const std::string& text) const {
        std::vector<int> result;
        if (pattern.empty() || text.empty()) return result;

        std::string processedText = text;
        if (!caseSensitive) {
            std::transform(processedText.begin(), processedText.end(), processedText.begin(), ::tolower);
        }

        int m = pattern.size();
        int n = processedText.size();
        int i = 0; // index for text
        int j = 0; // index for pattern

        while (i < n) {
            if (pattern[j] == processedText[i]) {
                j++;
                i++;
            }
            if (j == m) {
                result.push_back(i - j);
                j = lps[j - 1];
            } else if (i < n && pattern[j] != processedText[i]) {
                if (j != 0) {
                    j = lps[j - 1];
                } else {
                    i++;
                }
            }
        }
        return result;
    }

private:
    std::string pattern; ///< 模式字符串
    std::vector<int> lps; ///< 部分匹配表（LPS数组）
    bool caseSensitive; ///< 是否大小写敏感

    /**
     * @brief 构建部分匹配表（LPS数组）
     */
    void buildLPS() {
        int m = pattern.size();
        lps.resize(m, 0);
        int len = 0;
        int i = 1;

        while (i < m) {
            if (pattern[i] == pattern[len]) {
                len++;
                lps[i] = len;
                i++;
            } else {
                if (len != 0) {
                    len = lps[len - 1];
                } else {
                    lps[i] = 0;
                    i++;
                }
            }
        }
    }
};

#endif // KMP_HPP
