BEGIN {firsts = 0; rows = 0; seconds = 0; thirds = 0; fourths = 0; fifths = 0; sixths = 0; sevenths = 0; eighths = 0; ninths = 0; tenths = 0; laters = 0; misses = 0; firstten = 0;}
NF < 4 {misses++; rows++;}
NF > 3 {thismiss = 1;
    rows++;
    if ($2 == $3) {firsts++; firstten++; thismiss = 0;}
    else if ($2 == $4) {seconds++;  firstten++; thismiss = 0;}
    else if ($2 == $5) {thirds++;  firstten++; thismiss = 0;}
    else if ($2 == $6) {fourths++;  firstten++; thismiss = 0;}
    else if ($2 == $7) {fifths++;  firstten++; thismiss = 0;}
    else if ($2 == $8) {sixths++;  firstten++; thismiss = 0;}
    else if ($2 == $9) {sevenths++;  firstten++; thismiss = 0;}
    else if ($2 == $10) {eighths++;  firstten++; thismiss = 0;}
    else if ($2 == $11) {ninths++;  firstten++; thismiss = 0;}
    else if ($2 == $12) {tenths++;  firstten++; thismiss = 0;}
    else {
        for (i = 13; i < (NF - 1); i++) {
            if ($2 == $i) {thismiss = 0;}
        }
        if (thismiss == 0) {
            laters++;
        }
        else {
            misses++;
        }
    }
}
END { printf("1st   & 2nd   & 3rd   & 4th   & 5th  & 1-10 \\\\\n");
      printf("%d    & %d    & %d    & %d    & %d    & %d \\\\\n", firsts, seconds, thirds, fourths, fifths, firstten);
      printf("%.1f \\%% & %.1f \\%% & %.1f \\%% & %.1f \\%% & %.1f \\%% & %.1f \\%% \\\\\n", 100*firsts/rows, 100*seconds/rows, 100*thirds/rows, 100*fourths/rows, 100*fifths/rows, 100*firstten/rows);
      
  }
