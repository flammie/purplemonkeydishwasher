BEGIN {if (CS == 0) { 
    print("Corpus size must be > 0, say --assign=CS=NNN");
    exit(1)
    }
    if (LS == 0) {
        print("Lexicon size must be > 0, say --assign=LS=NNN");
    }
    if (ALPHA == 0) {
        ALPHA=1;
    }
}
{printf("%s\t%f\n", $2, -log( ($1 + ALPHA) / (CS + (LS * ALPHA)) ));}
