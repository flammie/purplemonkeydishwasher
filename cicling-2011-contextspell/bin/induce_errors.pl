#! /usr/bin/perl

# This program is used to add spelling errors to a text where
# exh line conists of five words separated by spaces. The
# program appends 'xx' to roughly ten percent of the middle
# word in lines and 'x' to the rest. 

# From the input
#   "don't eat the blue ones yet"
# the program produces the output
#   "xthe	the	don't eat * blue ones yet"
# or
#   "xxthe	the	don't eat * blue ones yet"

# This program was used to create juha_excerpt_with_errors.txt
# from juha_excerpt.txt.

$percent_of_double_errors = 10;

while (<>)
{
    chomp();

    @fields = split(/ /,$_);

    $random_number = rand(100);

    $correct_word = $fields[2];
    $misspelled_word = $fields[2];

    if ($random_number > 10)
    {
	$misspelled_word = "x$misspelled_word";
    }
    else
    {
	$misspelled_word = "xx$misspelled_word";
    }
    
    $fields[2] = "*";

    $context = join(' ',@fields);
    print "$misspelled_word\t$correct_word\t$context\n";
}
