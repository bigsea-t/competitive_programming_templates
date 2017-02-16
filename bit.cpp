/*
 *
 * Copyright(c) 2017 Taikai Takeda <297.1951@gmail.com> All rights reserved.
 *
 * binary indexed trees implemetation based on https://www.topcoder.com/community/data-science/data-science-tutorials/binary-indexed-trees/
 */


#include <bits/stdc++.h>
using namespace std;

// *** 1-based ***
class BIT {
    vector<int> bit;
    int m;
public:
    BIT(int m): m(m), bit(m+1, 0){};
    BIT(vector<int> & a): m(a.size()+1), bit(a.size()+1, 0){
        for (int i = 1; i < m; i++) {
            add(i, a[i-1]);
        }
    };

    void add(int i, int val){
        if (i <= m){
            bit[i] += val;
            add(i + (- i & i), val);
        }
    };
    int csum(int i){
        if (i <= 0)
            return 0;
        return bit[i] + csum(i - (-i & i));
    };
    // sum of ragne [i, j]
    int sumr(int i, int j){
        return csum(j) - csum(i - 1);
    };
};

int bf_sumr(const vector<int> & a, int k, int l){
    int tot = 0;
    for (int i = k; i <= l; ++i) {
        tot += a[i];
    }
    return tot;
}

// [1, maxnum]
pair<int, int> rand_range(int maxnum){
    int a = rand() % (maxnum) + 1;
    int b = rand() % (maxnum) + 1;

    if (a > b)
        swap(a, b);
    return make_pair(a, b);
}

int main()
{
    int n = 1000;
    vector<int> a(n);
    int max_num = 100;

    for (auto & x: a) {
        x = rand() % (max_num + 1);
    }

    BIT bit(a);

    int n_trial = 1000;
    int n_fail = 0;
    for (int i = 0; i < n_trial; ++i) {
        auto p = rand_range(a.size()+1);

        int idx = rand() % n + 1;
        int val = rand() % (max_num + 1);

        a[idx - 1] += val;
        bit.add(idx, val);

        int bit_res = bit.sumr(p.first, p.second);
        int bf_res = bf_sumr(a, p.first - 1, p.second - 1);

        if (bit_res != bf_res) {
            n_fail++;
        }
    }

    if (n_fail == 0) {
        cout << "all tests passed" << endl;
    } else {
        cout << n_fail << "tests failed" << endl;
    }

    return 0;
}
