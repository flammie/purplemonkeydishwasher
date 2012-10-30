# this script dumps all revisions from wikipedia dump into CORPDIR and writes
# to stdout a bash script to delete junk and wdiff interesting ones
#
# Note that this needs to save all revisions since we don't know when we find
# the revision that is the spelling correction until we hit it and we needed
# to diff it to previous revision... It's slow but doing 2-pass version or
# saving a whole lot of data would've been pita too
BEGIN { in_sp = 0;
        if (CORPDIR == "")
        {
            print "assign CORPDIR";
            exit 1;
        }
        print "#!/bin/bash" > "remove-junk.sh";
        print "#!/bin/bash" > "print-wdiffs.sh";
    }
/<title>/ { last_title = gensub("[[:space:][:punct:]]*", "", "g", gensub("<.?title>", "", "g")); }
/<comment>sp<\/comment>/   { in_sp = 2; }
/<comment>spelling<\/comment>/ { in_sp = 2; }
/<timestamp/ { 
        in_sp--;
        this_revision = gensub(" *", "", "g", gensub("<.?timestamp>", "", "g"));
        if (in_sp == 1)
         {
            print "speling in between " last_revision " and " this_revision \
                  "for " last_title;
            print "wdiff -3 " CORPDIR "/texts." last_title ".r" last_revision \
                " " CORPDIR "/texts." last_title ".r" this_revision > "print-wdiffs.sh";
         }
         else if (in_sp < 0)
         {
             print "rm " CORPDIR "/texts." last_title ".r" last_revision > "remove-junk.sh";
             in_sp = -32;
         }
         last_revision = this_revision
    }
/<text/,/<\/text/   { 
        print > CORPDIR"/texts." last_title ".r" last_revision;
     }

