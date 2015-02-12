

int loop(int x, int n)
{
		int result = -1;
		int mask;
		for(mask = 1 ; mask != result; mask = mask<<1){
			result ^= mask;
		}
	return result;
}
