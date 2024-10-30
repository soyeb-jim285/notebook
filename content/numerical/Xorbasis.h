/**
 * Author: Farhan
* Description: Xor basis
*/
int basis[d] = {0};
int sz = 0;
void insertVector(int mask) {
	for (int i = 0; i < d; i++) {
		if ((mask & (1 << i)) == 0) continue;
		if (!basis[i]) {
			basis[i] = mask;
			++sz;
			return;
		}
		mask ^= basis[i];
	}
}
