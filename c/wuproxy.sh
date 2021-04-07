#!/bin/bash
bin/wuserver & SERVER=$!
bin/wuproxy & PROXY=$!
bin/wuclient 10001 tcp://localhost:5556 &
bin/wuclient 90210 tcp://localhost:5556 &
bin/wuclient 90731 tcp://localhost:5557 &
bin/wuclient 91762 tcp://localhost:5557
sleep 2
kill -9 $SERVER
kill -9 $PROXY
