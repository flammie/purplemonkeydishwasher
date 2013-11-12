#! /usr/bin/perl

$total = 0;
$correct = 0;

while (<>)
{
    ++$total;

    chomp($_);

    @fields = split(/\t/,$_);

    if ($#fields != 1)
    {
	print "Syntax error on line $total";
	exit 1;
    }

    if ($fields[0] eq $fields[1])
    { ++$correct; }
}

print "Totally $total entries. Of these $correct were correct.\n";

$accuracy = $correct * 1.0 / $total;

print "Accuracy: $accuracy\n"
