void count_sort(vector<pli> &b, int bits) {
	int mask = (1 << bits) - 1;
	rep(it, 0, 2) {
		int shift = it * bits;
		vi q(1 << bits), w(sz(q) + 1);
		rep(i, 0, sz(b)) q[(b[i].first >> shift) & mask]++;
		partial_sum(q.begin(), q.end(), w.begin() + 1);
		vector<pli> res(sz(b));
		rep(i, 0, sz(b)) res[w[(b[i].first >> shift) & mask]++] = b[i];
		swap(b, res);
	}
}

struct SuffixArray {
	vi a; string s;
	SuffixArray(const string &str) : s(str + '\0') {
		int N = sz(s), q = 8;
		while ((1 << q) < N) q++;
		vector<pli> b(N);
		a.resize(N);
		rep(i, 0, N) b[i] = {s[i], i};

		for (int moc = 0;; moc++) {
			count_sort(b, q);
			rep(i, 0, N) a[b[i].second] = (i && b[i].first == b[i - 1].first) ? a[b[i - 1].second] : i;
			if ((1 << moc) >= N) break;
			rep(i, 0, N) {
				b[i] = {(ll)a[i] << q, i + (1 << moc) < N ? a[i + (1 << moc)] : 0};
				b[i].second = i;
			}
		}
		rep(i, 0, N) a[i] = b[i].second;
	}
	vi lcp() {
		int n = sz(a), h = 0;
		vi inv(n), res(n);
		rep(i, 0, n) inv[a[i]] = i;
		rep(i, 0, n) if (inv[i]) {
			int p0 = a[inv[i] - 1];
			while (s[i + h] == s[p0 + h]) h++;
			res[inv[i]] = h;
			if (h) h--;
		}
		return res;
	}
};
