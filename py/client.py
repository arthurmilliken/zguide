#!/home/arthur/venv/py39/bin/python
#
# Hello World client
# Connects REQ socket to tcp://localhost:5555
# Sends b"Hello" to server, expects b"World" back

import zmq

from logger import log

ADDRESS = 'tcp://localhost:5555'

def main(name='client'):
    context = zmq.Context()

    # Socket to talk to server
    log.info(f'{name}: Connecting to Hello World server at {ADDRESS}')
    socket = context.socket(zmq.REQ)
    socket.connect(ADDRESS)

    # Do 10 requests, waiting each time for a response
    for idx in range(10):
        msg = {
            'name': name,
            'msg': 'Hello',
        }
        log.info(f'{name}: Sending request {idx}: "{msg}"')
        socket.send_json(msg)

        # Get the reply.
        reply = socket.recv_json()
        log.info(f'{name}: Received reply {idx}: "{reply}"')

    log.info(f'{name}: DONE.')

import sys
if __name__ == '__main__':
    name = 'client'
    if len(sys.argv) > 1:
        name = sys.argv[1]

    main(name)
