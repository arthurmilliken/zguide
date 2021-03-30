#!/bin/bash
bin/taskwork >/dev/null & W1=$!
bin/taskwork >/dev/null & W2=$!
bin/tasksink & S=$!
bin/taskvent
sleep 5
kill $W1
kill $W2
