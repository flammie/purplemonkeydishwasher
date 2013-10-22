BEGIN {times = 0; results = 0;}
{results += 1; times += $0;}
END {printf("%.2f\n", times / results);}
