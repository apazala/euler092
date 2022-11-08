#include <stdio.h>
#include <inttypes.h>
#include <string.h>


#define HAPPY 1
#define UNHAPPY -1
#define MOD 1000000007


int memo[8][9 * 9 * 7 + 1];
int ishappy[9 * 9 * 7 + 1];

int next(int n)
{
	int sum = 0;
	while(n)
	{
		int d = n % 10;
		sum += d*d;
		n /= 10;
	}
	return sum;
}

int happy(int i)
{
	int sol = ishappy[i];
	if (sol) return sol;

	sol = happy(next(i));

	ishappy[i] = sol;
	return sol;
}

int solve(int k, int x)
{
	if (x < 0) return 0;
	int sol = memo[k][x];
	if (sol != -1) return sol;

	sol = 0;

	for(int i = 0; i <= 9; i++)
	{
		sol += solve(k - 1, x - i*i);
		sol = (sol >= MOD ? sol - MOD : sol);
	}

	memo[k][x] = sol;
	return sol;
}


void init()
{
	ishappy[1] = HAPPY;
	ishappy[89] = UNHAPPY;


	memset(memo, -1, sizeof(memo));
	memset(memo[1], 0, sizeof(memo[1]));

	for(int i = 1; i <= 9; i++)
	{
		memo[1][i*i] = 1;
	}
}

int main()
{
	init();

	int k = 7;

	int ans = 0;

	int lim = 9 * 9 * k;
	for (int i = 2; i <= lim; i++)
	{
		if(happy(i) == UNHAPPY)
		{
			for(int n = 1; n <= k; n++)
			{
				ans += solve(n, i);
				ans = (ans >= MOD ? ans - MOD : ans);
			}
		}

	}

	printf("%d\n", ans);

    return 0;
}
