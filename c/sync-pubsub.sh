#!/bin/bash
echo "Starting subscribers..."
for ((a=0; a<5; a++)); do
    bin/syncsub &
done
echo "Starting publisher..."
bin/syncpub
