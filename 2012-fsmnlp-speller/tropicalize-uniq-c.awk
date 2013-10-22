BEGIN {if (CS == 0) { 
    print("Corpus size must be > 0, say --assign=CS=NNN");
    exit(1)
    };}
{printf("%s\t%f\n", $2, -log($1/CS));}
