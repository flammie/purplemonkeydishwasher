#! /usr/bin/perl

@correct_suggestions = (0,0,0,0,0,0,0,0,0,0);

$total_words=0;

while (<stdin>)
{
    ++$total_words;
    
    chomp();

    @fields = split(/\t/,$_);
    
    $correct_word = $fields[0];

    @suggestions = @fields[1 .. 10];

    $position=0;
    $found=0;

    foreach (@suggestions)
    {
	if ($_ eq $correct_word)
	{ 
	    $found=1;
	    last;
	}
	$position = $position + 1;
	
    }

    if ($found==1)
    {
	$correct_suggestions[$position] = $correct_suggestions[$position] + 1;
    }
}

print "$ARGV[0]\t";
$total_corr = 0;
$third_or_less_corr = 0;
$fifth_or_less_corr = 0;
$sixth_or_more_corr = 0;
$pos = 0;
foreach (@correct_suggestions)
{
    if ($pos < 3)
    {
	$third_or_less_corr = $third_or_less_corr + $_;
    }
    if ($pos < 5)
    {
	$fifth_or_less_corr = $fifth_or_less_corr + $_;
    }
    if ($pos > 5)
    {
	$sixth_or_more_corr = $sixth_or_more_corr + $_;
    }


    $total_corr = $total_corr + $_;

    if ($pos < 5)
    {
	printf("& %.4f\\\% ",100*$_/$total_words);
    }
    ++$pos;
}
printf("& %.4f\\\% ",100*$sixth_or_more_corr/$total_words);
printf("& %.4f\\\% ",100*$third_or_less_corr/$total_words);
printf("& %.4f\\\% ",100*$fifth_or_less_corr/$total_words);
printf("& %.4f\\\% ",100*$total_corr/$total_words);
print "\\\\\n";
