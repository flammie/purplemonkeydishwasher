BEGIN {a=a; b=b;}
NF == 5 {$5=a*$5+b;}
NF == 2 {$2=a*$2+b;}
{print}
