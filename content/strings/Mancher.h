/**
* Author: Istahak
* Description: Mancher
*/
struct manacher {
    vector<int> p;
    void run_mancher(string s) {
        int n = s.size(); p.assign(n, 1);
        int l = 1, r = 1;
        for (int i = 1; i < n; i++) {
            p[i] = max(0, min(r - i, p[l + r - i]));
            while (i + p[i] < n and i - p[i] >= 0 and s[i + p[i]] == s[i - p[i]])
                p[i]++;
            if (i + p[i] > r) {
                l = i - p[i],r = i + p[i];
            }
        }
    }
    void build(string s) {
        string t; t.push_back('#');
        for (auto c : s) {
            t.push_back(c);
            t.push_back('#');
        }
        run_mancher(t);
    }
    int getLongest(int c, int odd) {
        int pos = 2 * c + 1 + (!odd);
        return p[pos] - 1;
    }
    bool checkPalindrome(int l, int r) {
        int len = r - l + 1;
        int mxlen = getLongest((l + r) / 2, l % 2 == r % 2);
        return len <= mxlen;
    }
};
