#include <iostream>
#include <vector>
#include <string>
#include <algorithm> // �� sort �ϥ�
#include "Header.h"
using namespace std;

void powerset(const string& s, int index, string current, vector<string>& result) {
    // �N��e�l���[�J���G
    result.push_back(current);

    // �q��e���޶}�l�A���j�K�[�C�Ӥ���
    for (int i = index; i < s.length(); i++) {
        current += s[i]; // �]�t��e����
        powerset(s, i + 1, current, result); // ���j�B�z�Ѿl����
        current.pop_back(); // �^���A������e�����H���դU�@�ӲզX
    }
}

int main() {
    string s;
    cout << "Enter the set elements (e.g., 'abc'): ";
    cin >> s;

    vector<string> result;
    powerset(s, 0, "", result);

    // �N���G���r��ǱƧ�
    sort(result.begin(), result.end());

    // ��X�Ҧ��l���A�ϥγr�����j����
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