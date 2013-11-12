BEGIN {FS="\t"; rss_max = 0;  results = 0}
NF > 5 {rss_max += $5; utimes += $3; stimes += $4; results += 1;}
END {
    if (results > 0) {
        if (rss_max > 1000000) {
            printf("%.1f GiB\n", (rss_max / (1024*1024)) / results);
        }
        else
        {
            printf("%.1f MiB\n", (rss_max / 1024) / results);
        }
    }
    else {
        print "---";
    }
}

