#!/bin/bash
bin/wuserver & SERVER=$!
bin/wuclient &
bin/wuclient 90210 &
bin/wuclient 90731 &
bin/wuclient 91762
sleep 2
kill -9 $SERVER
