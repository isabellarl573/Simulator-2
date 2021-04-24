BEGIN	{
    while (getline < ARGV[1]) {
        if ($1 == "Currently") {
            print "-1,\n"
        }
        # At time: 57$3 Idle/Thinking : 0 Requesting : 5 Waiting : 0 Eating : 0
        else {
            if ($1 == "Amount") {
                print ""
            }
            else {
                print $3,",",$6,",",$9,",",$12,",",$15,"\n"
            }
        }
    }
}