BEGIN { print "Searching the longest line..." }
{
    if (NF>max) {
	max=NF;
	line=NR;
    }
}
END { printf "The longest line number is %d, it has %d words.\n", line, max }
