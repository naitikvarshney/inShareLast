#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int SEED = 494;
const int N = 100000;
const int L = 1;
const int R = N;

const int INSERTION_SORT_THRESHOLD = 47;
//const int MAX_RUN_LENGTH = 33;
//const int QUICKSORT_THRESHOLD = 286;
//const int MAX_RUN_COUNT = 67;

int MIN_VALUE;
int MAX_VALUE;
const int NO_VALUE = -1;

mt19937 gen(SEED);

inline int rnd(int L, int R) { return uniform_int_distribution<int>(L, R)(gen); }

inline void randomShuffle(int *a, int L, int R) {
    for (int i = 0; i <= R - L; ++i)
        swap(a[L+i], a[L + rnd(0, i)]);
}

inline bool lesss_f(int a, int b) {
    if (a != NO_VALUE && b != NO_VALUE) {
        return a < b;
    }
    if (a == NO_VALUE) {
        return b > MAX_VALUE;
    }
    return a < MIN_VALUE;
}

inline bool greaterr(int a, int b) {
    if (a != NO_VALUE && b != NO_VALUE) {
        return a > b;
    }
    if (a == NO_VALUE) {
        return b < MIN_VALUE;
    }
    return a > MAX_VALUE;
}

void hackedSort(int *a, int* p, int lft, int rght, bool lftmost) {
    int length = rght - lft + 1;

    if (length < INSERTION_SORT_THRESHOLD) {
        for (int i = rght; i >= lft; i--) {
            if (a[i] == NO_VALUE) a[i] = MIN_VALUE++;
        }
        randomShuffle(a, lft, rght);

        if (lftmost) {
            for (int i = lft, j = i; i < rght; j = ++i) {
                int ai = a[i + 1];
                int pi = p[i + 1];
                while (ai < a[j]) {
                    a[j + 1] = a[j];
                    p[j + 1] = p[j];
                    if (j-- == lft) {
                        break;
                    }
                }
                a[j + 1] = ai;
                p[j + 1] = pi;
            }
        } else {
            bool z = false;
            do {
                if (lft >= rght) {
                    return;
                }
            } while ((z = a[lft] >= a[lft - 1]), ++lft, z);


            for (int k = lft; ++lft <= rght; k = ++lft) {
                int a1 = a[k], a2 = a[lft];
                int p1 = p[k], p2 = p[lft];

                if (a1 < a2) {
                    a2 = a1; a1 = a[lft];
                    p2 = p1; p1 = p[lft];
                }
                while (a1 < a[--k]) {
                    a[k + 2] = a[k];
                    p[k + 2] = p[k];
                }
                ++k;
                a[k + 1] = a1;
                p[k + 1] = p1;

                while (a2 < a[--k]) {
                    a[k + 1] = a[k];
                    p[k + 1] = p[k];
                }
                a[k + 1] = a2;
                p[k + 1] = p2;
            }
            int last = a[rght];
            int plast = p[rght];

            while (last < a[--rght]) {
                a[rght + 1] = a[rght];
                p[rght + 1] = p[rght];
            }
            a[rght + 1] = last;
            p[rght + 1] = plast;
        }
        return;
    }

    int seventh = (length >> 3) + (length >> 6) + 1;

    int e3 = (lft + rght) >> 1;
    int e2 = e3 - seventh;
    int e1 = e2 - seventh;
    int e4 = e3 + seventh;
    int e5 = e4 + seventh;

    if (a[e5] == NO_VALUE) a[e5] = MIN_VALUE++;
    if (a[e4] == NO_VALUE) a[e4] = MIN_VALUE++;

    if (a[e1] == NO_VALUE) a[e1] = MAX_VALUE--;
    if (a[e2] == NO_VALUE) a[e2] = MAX_VALUE--;

    if (lesss_f(a[e2], a[e1])) { int t = a[e2]; a[e2] = a[e1]; a[e1] = t;
        int s = p[e2]; p[e2] = p[e1]; p[e1] = s; }

    if (lesss_f(a[e3], a[e2])) { int t = a[e3]; a[e3] = a[e2]; a[e2] = t;
        int s = p[e3]; p[e3] = p[e2]; p[e2] = s;
        if (lesss_f(t, a[e1])) { a[e2] = a[e1]; a[e1] = t;
            p[e2] = p[e1]; p[e1] = s; }
    }
    if (lesss_f(a[e4], a[e3])) { int t = a[e4]; a[e4] = a[e3]; a[e3] = t;
        int s = p[e4]; p[e4] = p[e3]; p[e3] = s;
        if (lesss_f(t, a[e2])) { a[e3] = a[e2]; a[e2] = t;
            p[e3] = p[e2]; p[e2] = s;
            if (lesss_f(t, a[e1])) { a[e2] = a[e1]; a[e1] = t;
                p[e2] = p[e1]; p[e1] = s; }
        }
    }
    if (lesss_f(a[e5], a[e4])) { int t = a[e5]; a[e5] = a[e4]; a[e4] = t;
        int s = p[e5]; p[e5] = p[e4]; p[e4] = s;
        if (lesss_f(t, a[e3])) { a[e4] = a[e3]; a[e3] = t;
            p[e4] = p[e3]; p[e3] = s;
            if (lesss_f(t, a[e2])) { a[e3] = a[e2]; a[e2] = t;
                p[e3] = p[e2]; p[e2] = s;
                if (lesss_f(t, a[e1])) { a[e2] = a[e1]; a[e1] = t;
                    p[e2] = p[e1]; p[e1] = s; }
            }
        }
    }

    int lesss  = lft;
    int great = rght;

    if (a[e1] != a[e2] && a[e2] != a[e3] && a[e3] != a[e4] && a[e4] != a[e5]) {
        int pivot1 = a[e2];
        int pivot2 = a[e4];
        int ppivot1 = p[e2];
        int ppivot2 = p[e4];

        a[e2] = a[lft];
        a[e4] = a[rght];
        p[e2] = p[lft];
        p[e4] = p[rght];

        while (lesss_f(a[++lesss], pivot1));
        while (greaterr(a[--great], pivot2));

        outer:
        for (int k = lesss - 1; ++k <= great; ) {
            int ak = a[k];
            int pk = p[k];
            if (lesss_f(ak, pivot1)) {
                a[k] = a[lesss];
                p[k] = p[lesss];
                a[lesss] = ak;
                p[lesss] = pk;
                ++lesss;
            } else if (greaterr(ak, pivot2)) {
                while (greaterr(a[great], pivot2)) {
                    if (great-- == k) {
                        goto outer;
                    }
                }
                if (lesss_f(a[great], pivot1)) {
                    a[k] = a[lesss];
                    p[k] = p[lesss];
                    a[lesss] = a[great];
                    p[lesss] = p[great];
                    ++lesss;
                } else {
                    a[k] = a[great];
                    p[k] = p[great];
                }
                a[great] = ak;
                p[great] = pk;
                --great;
            }
        }

        a[lft]  = a[lesss  - 1]; a[lesss  - 1] = pivot1;
        a[rght] = a[great + 1]; a[great + 1] = pivot2;
        p[lft]  = p[lesss  - 1]; p[lesss  - 1] = ppivot1;
        p[rght] = p[great + 1]; p[great + 1] = ppivot2;

        hackedSort(a, p, lft, lesss - 2, lftmost);
        hackedSort(a, p, great + 2, rght, false);

        if (lesss < e1 && e5 < great) {
            outer2:
            for (int k = lesss - 1; ++k <= great; ) {
                int ak = a[k];
                int pk = p[k];
                if (ak == pivot1) {
                    a[k] = a[lesss];
                    p[k] = p[lesss];
                    a[lesss] = ak;
                    p[lesss] = pk;
                    ++lesss;
                } else if (ak == pivot2) {
                    while (a[great] == pivot2) {
                        if (great-- == k) {
                            goto outer2;
                        }
                    }
                    if (a[great] == pivot1) {
                        a[k] = a[lesss];
                        p[k] = p[lesss];
                        a[lesss] = pivot1;
                        p[lesss] = ppivot1;
                        ++lesss;
                    } else {
                        a[k] = a[great];
                        p[k] = p[great];
                    }
                    a[great] = ak;
                    p[great] = pk;
                    --great;
                }
            }
        }

        hackedSort(a, p, lesss, great, false);

    }
}

int main()
{
    ios_base::sync_with_stdio(false);
    int n = N;
    int *a = new int[N];
    int *p = new int[N];

    for (int i = 0; i < n; i++) {
        a[i] = NO_VALUE;
        p[i] = i;
    }
    MIN_VALUE = 1;
    MAX_VALUE = n;

    hackedSort(a, p, 0, n - 1, true);

    int *tmp = new int[n];
    for (int i = 0; i < n; ++i)
        tmp[p[i]] = a[i];
    for (int i = 0; i < n; ++i) {
        a[i] = tmp[i];
        p[i] = i;
    }


    cout << 1 << endl;
//long long y=1e9;
    cout <<n<<endl;

    for (int i = 0; i < n; ++i)
        cout << (i ? " " : "") << (a[i] * 713 + rnd(0, 413));
    cout << endl;

    return 0;
}