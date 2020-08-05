#include <stdio.h>

int main()
{
	FILE *fp = fopen("large", "w+");
	
	fprintf(fp, "1001\n");
	for(int i = 0; i < 1002; i++)
		fprintf(fp, "%d ", (i + 1) * -1);

	fclose(fp);
	return 0;
}
