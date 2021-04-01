#!/bin/bash
bin/msgqueue & B=$!
bin/rrworker W1 & W1=$!
bin/rrworker W2 & W2=$!
bin/rrclient C1 &
bin/rrclient C2
sleep 2
kill $W1
kill $W2
kill $B
