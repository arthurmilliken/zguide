#!/home/arthur/venv/py39/bin/python
#
# Hello World server
# Binds REP socket to tcp://*:5555
# Expects b"Hello" from client, replies with b"World"
#

import time
import zmq

from logger import log

ADDRESS = 'tcp://*:5555'

def main():
    context = zmq.Context()
    socket = context.socket(zmq.REP)
    socket.bind(ADDRESS)
    log.info(f'listening on {ADDRESS}')

    try:
        while True:
            # Receive next request from client
            message = socket.recv_json()
            log.info(f'Received request: "{message}"')

            # Do some 'work'
            time.sleep(0.1)
            reply = {
                'name': message.get('name', 'unknown'),
                'msg': 'World'
            }
            log.info(f'Completed work: "{reply}"')

            # Send reply back to client
            socket.send_json(reply)
    except KeyboardInterrupt:
        log.critical('KeyboardInterrupt detected. Exiting.')
    finally:
        socket.close()
        context.term()

if __name__ == '__main__':
    main()
