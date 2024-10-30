/**
* Author: Farhan
* Description: SOS DP
*/
vector<vector<int>> dp(1 << n, vector<int>(n));
vector<int> sos(1 << n);
for (int mask = 0; mask < (1 << n); mask++) {
	dp[mask][-1] = a[mask];
	for (int x = 0; x < n; x++) {
		dp[mask][x] = dp[mask][x - 1];
		if (mask & (1 << x)) { dp[mask][x] += dp[mask - (1 << x)][x - 1]; }
	}
	sos[mask] = dp[mask][n - 1];
}
