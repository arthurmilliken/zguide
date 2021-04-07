#!/bin/bash
bin/server & SERVER=$!
bin/client
kill -9 $SERVER
