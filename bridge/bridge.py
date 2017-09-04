#!/usr/bin/env python3

import bottle
from bottle import Bottle, run, request, response
from serial import Serial
import serial.tools.list_ports
import argparse
import json

PAYLOAD_TERMINATOR = b'\4'
KNOWN_DEVICES = {"USB VID:PID=1A86:7523"}


class PayloadTooBigException(BaseException):
    pass

serial_port = None
baud_rate = None
app = Bottle()

def find_device_port():
    for port in serial.tools.list_ports.comports():
        for known_device in KNOWN_DEVICES:
            if known_device in port.hwid:
                return str(port.device)

def enable_cors(fn):
    def _enable_cors(*args, **kwargs):
        # set CORS headers
        response.headers['Access-Control-Allow-Origin'] = '*'
        response.headers['Access-Control-Allow-Methods'] = 'GET, POST, PUT, OPTIONS'
        response.headers['Access-Control-Allow-Headers'] = 'Origin, Accept, Content-Type, X-Requested-With, X-CSRF-Token'

        if bottle.request.method != 'OPTIONS':
            # actual request; reply with the actual response
            return fn(*args, **kwargs)

    return _enable_cors


@app.route('/', method=['POST', 'OPTIONS'])
@enable_cors
def request_to_serial():
    try:
        body = str(request.body.read(), encoding='ascii')
        payload = json.loads(body)['payload']
        response = send_payload_to_serial(payload)
        return {'payload': response}
    except PayloadTooBigException:
        return {'error': 'payload too big'}


def send_payload_to_serial(payload:str) -> str:
    payload_bytes = bytes(payload, encoding='ascii') + PAYLOAD_TERMINATOR

    if len(payload_bytes) > 128:
        raise PayloadTooBigException()

    with Serial(port=serial_port, baudrate=baud_rate) as ser:
        ser.write(payload_bytes)
        response_bytes = ser.read_until(PAYLOAD_TERMINATOR)[:-1]

    response = str(response_bytes, encoding='ascii')
    return response


def parse_args():
    arg_parser = argparse.ArgumentParser(description='Forwards 0 terminated messages between HTTP and serial port')
    arg_parser.add_argument('--serialport', '-s', help='Serial port', metavar='PORT', default=find_device_port(), type=str)
    arg_parser.add_argument('--baudrate', '-b', help='Serial baud rate', metavar='RATE', default=115200, type=int)
    args = arg_parser.parse_args()
    serial_port = args.serialport
    baud_rate = args.baudrate
    return args


if __name__ == "__main__":
    args = parse_args()
    run(app, host='localhost', port=9876)
