#!/bin/bash
bin/taskwork >/dev/null & W1=$!
bin/taskwork >/dev/null & W2=$!
bin/taskwork >/dev/null & W3=$!
bin/taskwork >/dev/null & W4=$!
bin/tasksink & S=$!
bin/taskvent
sleep 4
kill $W1
kill $W2
kill $W3
kill $W4
