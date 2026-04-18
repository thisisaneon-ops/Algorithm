#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

// --- 1. 坏字符规则预处理 ---
void getBC(string &t, int bc[]) {
    int m = t.size();
    for (int i = 0; i < 256; i++) bc[i] = m; // 默认跳过整个长度
    for (int i = 0; i < m - 1; i++) {
        bc[(unsigned char)t[i]] = m - 1 - i; // 记录字符距离末尾的距离
    }
}

// --- 2. 好后缀规则预处理 (核心逻辑) ---
// suffix[i] 表示以 i 为边界，与模式串后缀匹配的最大长度
void getSuffix(string &t, int suffix[]) {
    int m = t.size();
    suffix[m - 1] = m;
    for (int i = m - 2; i >= 0; i--) {
        int k = i;
        while (k >= 0 && t[k] == t[m - 1 - (i - k)]) k--;
        suffix[i] = i - k;
    }
}

void getGS(string &t, int gs[]) {
    int m = t.size();
    int suffix[m];
    getSuffix(t, suffix);

    // 情况3：完全没匹配，跳过整个 m
    for (int i = 0; i < m; i++) gs[i] = m;

    // 情况2：模式串前缀 = 模式串后缀的后缀 (你图里的数学推导)
    int j = 0;
    for (int i = m - 1; i >= 0; i--) {
        if (suffix[i] == i + 1) {
            for (; j < m - 1 - i; j++) {
                if (gs[j] == m) gs[j] = m - 1 - i;
            }
        }
    }

    // 情况1：模式串内部有子串等于好后缀
    for (int i = 0; i <= m - 2; i++) {
        gs[m - 1 - suffix[i]] = m - 1 - i;
    }
}

// --- 3. BM 搜索主函数 ---
int BM(string s, string t) {
    int n = s.size(), m = t.size();
    if (m == 0) return 0;

    int bc[256];
    int gs[m];
    getBC(t, bc);
    getGS(t, gs);

    int i = 0;
    while (i <= n - m) {
        int j = m - 1;
        while (j >= 0 && s[i + j] == t[j]) j--; // 从后向前比

        if (j < 0) {
            // 匹配成功，但记得释放或处理位移
            return i;
        } else {
            // 【精华】谁跳得远听谁的
            i += max(gs[j], bc[(unsigned char)s[i + j]] - (m - 1 - j));
        }
    }
    return -1;
}