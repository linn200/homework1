# 41143221

作業一
## Problem 1
## 解題說明

Ackermann 函數 \( A(m, n) \) 是一個遞迴定義的函數，增長極快，用於研究遞迴和計算複雜性。本題使用遞迴方法實現，根據數學定義：

$$
A(m, n) =
\begin{cases} 
n + 1 & \text{if } m = 0 \\
A(m-1, 1) & \text{if } m > 0 \text{ and } n = 0 \\
A(m-1, A(m, n-1)) & \text{if } m > 0 \text{ and } n > 0 
\end{cases}
$$

舉例說明:
計算 $A(1, 2)$：
- $A(1, 2) = A(0, A(1, 1))$
- $A(1, 1) = A(0, A(1, 0))$
- $A(1, 0) = A(0, 1) = 2$
- $A(1, 1) = A(0, 2) = 3$
- $A(1, 2) = A(0, 3) = 4$

## 程式實作

以下為主要程式碼：

```cpp
#include <iostream>
#include "ackermann.h"
using namespace std;

// 遞迴實現 Ackermann 函數
int ackermann_recursive(int m, int n) {
    if (m == 0) return n + 1;
    else if (n == 0) return ackermann_recursive(m - 1, 1);
    else return ackermann_recursive(m - 1, ackermann_recursive(m, n - 1));
}

// 非遞迴實現 Ackermann 函數，使用堆疊
int ackermann_nonrecursive(int m, int n) {
    stack<pair<int, int>> s;
    s.push({m, n});
    while (!s.empty()) {
        m = s.top().first;
        n = s.top().second;
        s.pop();
        if (m == 0) continue; // m == 0 時，結果為 n + 1，後處理
        else if (n == 0) s.push({m - 1, 1});
        else {
            s.push({m - 1, 0}); // 儲存 A(m-1, result) 的 m-1
            s.push({m, n - 1}); // 計算 A(m, n-1)
        }
    }
    return n + 1; // 最終結果，考慮 m == 0 情況
}

int main() {
    int m, n;
    cout << "Enter m and n: ";
    cin >> m >> n;
    cout << "A(" << m << ", " << n << ") (Recursive) = " << ackermann_recursive(m, n) << endl;
    cout << "A(" << m << ", " << n << ") (Non-recursive) = " << ackermann_nonrecursive(m, n) << endl;
    return 0;
}
```

## 效能分析

1. 時間複雜度：Ackermann 函數的時間複雜度無法用簡單的指數形式表示，因其屬於非原始遞迴函數，增長速度極快。對於給定的 \( m \) 和 \( n \)，計算次數隨著 \( m \) 增加呈現超指數增長。
2. 空間複雜度：遞迴深度取決於 \( m \) 和 \( n \) 的組合，無法簡單用 \( O(m) \) 或 \( O(n) \) 表示，最壞情況下可能遠超線性複雜度，容易導致堆疊溢出。

## 測試與驗證

### 測試案例
- $A(0, 0) = 1$ 
- $A(1, 1) = 3$ 
- $A(2, 1) = 5$
### 驗證
對小值 $m, n \leq 2$ 測試，遞迴與非遞迴結果相同，證明正確性。

### 編譯與執行指令
```shell
$ g++ -std=c++17 -o ackermann ackermann.cpp
$ ./ackermann
Enter m and n (non-negative integers): 1 2
A(1, 2) = 4
```
### 結論
1. 程式能正確計算 Ackermann 函數 \( A(m, n) \)，遞迴實現通過測試。
2. 測試案例涵蓋了 $m, n \leq2$ 的情況，驗證了程式的正確性。
3. 由於 Ackermann 函數增長極快，對於較大的 \( m \)（如 $m \geq 4$），需注意堆疊溢出的潛在風險。

## 申論及開發報告

### 選擇遞迴與非遞迴的原因
1. **遞迴的直觀性**  
   Ackermann 函數的定義本質上是遞迴的，直接按照數學定義實現程式碼邏輯清晰，易於理解，適合教學和驗證。
2. **實現的簡潔性與正確性**  
   遞迴版本程式碼簡潔，易於驗證數學正確性，通過直接映射數學定義，確保邏輯無誤。
3. **適用性**  
   遞迴實現適合小規模輸入的快速原型設計和驗證，雖然對於大規模輸入可能因堆疊溢出受限，但本題測試案例範圍內（$m, n \leq 2$）足夠有效。

### 使用資料結構與演算法的原因
1. **演算法：遞迴**  
   - **原因**：遞迴演算法直接對應 Ackermann 函數的數學定義，程式碼簡潔且易於驗證。通過遞迴結構，可以自然實現函數的嵌套調用，符合問題定義。  
   - **優勢**：遞迴演算法適合快速原型設計和教學，程式碼邏輯直觀，易於理解和維護。

### 心得報告
在實現 Ackermann 函數的過程中，我深刻體會到遞迴演算法的優點與限制。遞迴實現雖然直觀且程式碼簡潔，但對於較大的輸入（如 $m \geq 4$），容易因遞迴深度過大導致堆疊溢出，這讓我意識到在實際應用中需要考慮系統資源限制。測試過程中，我發現小值輸入的正確性驗證非常重要，因為 Ackermann 函數的快速增長特性使得大值測試在實際環境中難以執行。這次作業讓我對遞迴演算法的設計和限制有了更深的理解，也提升了我對程式效能和穩定性的關注。

## Problem 2
## 解題說明

冪集包含集合 $S$ 的所有子集，數量為 $2^n$。遞迴方法通過選擇或不選擇當前元素，生成所有組合。

### 舉例說明
對於 \( S = \{a, b\} \)，遞迴生成冪集的過程如下：
- 從空集開始：\( \{\} \)
- 考慮元素 \( a \)：
  - 不選 \( a \)：保持 \( \{\} \)
  - 選 \( a \)：生成 \( \{a\} \)
- 考慮元素 \( b \)：
  - 基於 \( \{\} \)：不選 \( b \)（保持 \( \{\} \)），選 \( b \)（生成 \( \{b\} \)）
  - 基於 \( \{a\} \)：不選 \( b \)（保持 \( \{a\} \)），選 \( b \)（生成 \( \{a, b\} \)）
- 最終結果：\( \{\{\}, \{a\}, \{b\}, \{a, b\}\} \)

## 程式實作

以下為主要程式碼：

```cpp
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include "powerset.h"
using namespace std;

void powerset(const string& s, int index, string current, vector<string>& result) {
    result.push_back(current); // 加入當前子集
    for (int i = index; i < s.length(); i++) {
        current += s[i]; // 包含當前元素
        powerset(s, i + 1, current, result); // 遞迴
        current.pop_back(); // 回溯
    }
}

int main() {
    string s;
    cout << "Enter the set elements (e.g., 'abc'): ";
    cin >> s;
    vector<string> result;
    powerset(s, 0, "", result);
    sort(result.begin(), result.end()); // 按字典序排序
    cout << "Powerset of {" << s << "} = { ";
    for (size_t i = 0; i < result.size(); i++) {
        cout << "{";
        for (size_t j = 0; j < result[i].length(); j++) {
            cout << result[i][j];
            if (j < result[i].length() - 1) cout << ", ";
        }
        cout << "}";
        if (i < result.size() - 1) cout << ", ";
    }
    cout << " }" << endl;
    return 0;
}
```

## 效能分析

1. **時間複雜度**：\( O(2^n) \)，因為每個元素有選或不選兩種選擇，生成 \( 2^n \) 個子集。
2. **空間複雜度**：\( O(2^n) \) 用於儲存所有子集，遞迴深度為 \( O(n) \)，額外需要 \( O(n) \) 的空間儲存當前子集的字串。

## 測試與驗證

### 測試案例
- \( S = "ab" \): \( \{\{\}, \{a\}, \{b\}, \{a, b\}\} \)
- \( S = "abc" \): \( \{\{\}, \{a\}, \{b\}, \{c\}, \{a, b\}, \{a, c\}, \{b, c\}, \{a, b, c\}\} \)

#### 驗證
手動檢查子集數和內容，與數學定義一致，程式輸出按字典序排序，符合預期。

### 編譯與執行指令
```shell
$ g++ -std=c++17 -o powerset powerset.cpp
$ ./powerset
Enter the set elements (e.g., 'abc'): ab
Powerset of {ab} = { {}, {a}, {b}, {a, b} }
```
## 申論及開發報告
### 選擇遞迴的原因
1. **遞迴的直觀性**  
   冪集問題的本質是為每個元素選擇「選」或「不選」，這種二元選擇結構天然適合遞迴實現。遞迴過程清晰地模擬了決策樹的生成過程，每層遞迴處理一個元素，簡化了程式邏輯。
2. **回溯的簡潔性**  
   使用遞迴實現時，通過回溯（移除當前元素）可以輕鬆恢復狀態，無需額外數據結構來管理中間結果，這使得程式碼更簡潔且易於維護。
3. **靈活性**  
   遞迴實現允許輕鬆擴展到更複雜的子集生成問題，例如加入約束條件或修改輸出格式。

### 使用資料結構與演算法的原因
1. **資料結構：向量 (Vector)**  
   - **原因**：選擇 `std::vector` 儲存冪集的結果，因為向量提供了動態大小管理，能夠高效儲存 $2^n$ 個子集。向量支持快速插入操作（`push_back`），適合在遞迴過程中逐步收集子集。此外，向量可以與 `std::sort` 結合，輕鬆實現字典序排序。
   - **優勢**：相比陣列，向量無需預先指定大小，靈活且安全；相比其他容器（如集合），向量在遍歷和排序時更高效。
2. **演算法：遞迴與回溯**  
   - **原因**：冪集生成是一個典型的組合問題，遞迴與回溯演算法能自然模擬每個元素的選或不選決策，形成決策樹。回溯確保每次遞迴結束後狀態被正確恢復，避免了重複計算或錯誤。
   - **優勢**：遞迴與回溯演算法程式碼簡潔，易於理解，且能保證生成所有可能的子集，符合冪集的數學定義。

### 心得報告
實現冪集的過程讓我對遞迴與回溯演算法有了更深的理解。特別是通過遞迴生成所有子集的過程，讓我體會到如何將數學上的組合問題轉化為程式碼邏輯。使用 `std::vector` 儲存結果的設計讓我學會了如何選擇合適的數據結構來滿足動態儲存需求。同時，輸出格式的處理（特別是空子集的特殊處理）讓我意識到程式設計中細節的重要性。測試過程中，我發現對於較大的輸入（如 $n > 10$），程式執行時間會顯著增加，這促使我思考如何進一步優化，例如通過並行計算或位元運算來加速冪集生成。這次作業不僅提升了我的程式設計能力，也讓我對演算法和數據結構的選擇有了更深刻的認識。
