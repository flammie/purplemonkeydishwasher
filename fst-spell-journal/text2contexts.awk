{for (i = 1; i < NF; i++) {
         printf("%s\t%s\t%s\n", $i, $i, gensub($i, "*", 1));
    }
}

