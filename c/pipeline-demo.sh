#!/bin/bash
bin/taskwork & W1=$!
bin/taskwork & W2=$!
bin/taskwork & W3=$!
bin/taskwork & W4=$!
bin/tasksink & S=$!
bin/taskvent
sleep 3
kill $W1
kill $W2
kill $W3
kill $W4
