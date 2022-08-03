#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int N = 1000001;

int n, m, mod;

class XDS {
   private:
    ll sum[N << 2], lazy[N << 2], mu[N << 2];

   public:
    void init() {
        memset(lazy, 0, sizeof(lazy));
        for (int i = 0; i < N; i++) mu[i] = 1;
        memset(sum, 0, sizeof(sum));
    }
    void build(int x, int l, int r) {
        if (l == r) {
            scanf("%lld", &sum[x]);
            return;
        }
        int mid = (l + r) >> 1;
        build(x * 2, l, mid);
        build(x * 2 + 1, mid + 1, r);
        sum[x] = (sum[x * 2] + sum[x * 2 + 1]) % mod;
    }
    inline void mul(int x, int l, int r, ll v) {
        mu[x] = mu[x] * v % mod;
        sum[x] = sum[x] * v % mod;
        lazy[x] = lazy[x] * v % mod;
    }
    inline void add(int x, int l, int r, ll v) {
        lazy[x] = (lazy[x] + v) % mod;
        sum[x] = (sum[x] + (r - l + 1) * v) % mod;
    }
    void pushdown(int x, int l, int r) {
        if (lazy[x] || mu[x] != 1) {
            mul(x * 2, l, (l + r) >> 1, mu[x]);
            mul(x * 2 + 1, ((l + r) >> 1) + 1, r, mu[x]);
            add(x * 2, l, (l + r) >> 1, lazy[x]);
            add(x * 2 + 1, ((l + r) >> 1) + 1, r, lazy[x]);
            lazy[x] = 0;
            mu[x] = 1;
        }
    }
    void update(int x, int l, int r, int a, int b, ll v) {
        if (a > r || b < l) return;
        if (a <= l && r <= b) {
            add(x, l, r, v);
            return;
        }
        pushdown(x, l, r);
        int mid = (l + r) >> 1;
        update(x * 2, l, mid, a, b, v);
        update(x * 2 + 1, mid + 1, r, a, b, v);
        sum[x] = (sum[x * 2] + sum[x * 2 + 1]) % mod;
    }
    void update_mul(int x, int l, int r, int a, int b, ll v) {
        if (a > r || b < l) return;
        if (a <= l && r <= b) {
            mul(x, l, r, v);
            return;
        }
        pushdown(x, l, r);
        int mid = (l + r) >> 1;
        update_mul(x * 2, l, mid, a, b, v);
        update_mul(x * 2 + 1, mid + 1, r, a, b, v);
        sum[x] = (sum[x * 2] + sum[x * 2 + 1]) % mod;
    }
    ll query(int x, int l, int r, int a, int b) {
        if (a > r || b < l) return 0;
        if (a <= l && r <= b) return sum[x];
        pushdown(x, l, r);
        int mid = (l + r) >> 1;
        return query(x * 2, l, mid, a, b) + query(x * 2 + 1, mid + 1, r, a, b);
    }
} xds;

int main() {
    scanf("%d %d %d", &n, &m, &mod);
    xds.init();
    xds.build(1, 1, n);
    while (m--) {
        int opt, x, y, k;
        scanf("%d %d %d", &opt, &x, &y);
        if (opt == 2) {
            scanf("%d", &k);
            xds.update(1, 1, n, x, y, k);
        } else if (opt == 1) {
            scanf("%d", &k);
            xds.update_mul(1, 1, n, x, y, k);
        } else
            printf("%lld\n", xds.query(1, 1, n, x, y) % mod);
    }
}
