#include <iostream>
#include <string>
#include <algorithm>
#include <vector>

std::string LPS_helper(const std::string& X, const std::string& Y)
{
	int m = X.size();
	int n = Y.size();
	std::vector<std::vector<size_t>> L(m + 1, std::vector<size_t>(n + 1));
	for (auto i = 0; i <= m; ++i) {
		for (auto j = 0; j <= n; ++j) {
			if (i == 0 || j == 0) {
				continue;
			}
			else if (X[i - 1] == Y[j - 1]) {
				L[i][j] = L[i - 1][j - 1] + 1;
			}
			else {
				L[i][j] = std::max(L[i - 1][j], L[i][j - 1]);
			}
		}
	}

	int index = L[m][n];
	std::string lcs(index + 1, ' ');
	int i = m;
	int j = n;
	while (i > 0 && j > 0) {
		if (X[i - 1] == Y[j - 1]) {
			lcs[index - 1] = X[i - 1];
			--i;
			--j;
			--index;
		}
		else if (L[i - 1][j] > L[i][j - 1]) {
			--i;
		}
		else {
			--j;
		}
	}
	return lcs;
}

std::string LPS(std::string& str)
{
	std::string rev = str;
	std::reverse(rev.begin(), rev.end());
	return LPS_helper(str, rev);
}

int main()
{
	std::string s = "character";
	std::cout << LPS(s);
}
