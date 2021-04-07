#!/bin/bash
bin/taskwork2 &
bin/taskwork2 &
bin/taskwork2 &
bin/taskwork2 &
bin/tasksink2 &
bin/taskvent
sleep 2

# prove that task workers shut themselves down
echo
ps aux | head -n 1 && ps aux | grep bin/task