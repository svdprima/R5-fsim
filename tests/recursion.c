int factorial (int N)
{
    return N > 0 ? N * factorial (N - 1) : 1;
}

int main()
{
    int N = 10;
    int fact = factorial (N);
	return 0;
}
