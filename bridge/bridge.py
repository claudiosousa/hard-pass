#!/usr/bin/env python3

import bottle
from bottle import Bottle, run, request, response
from serial import Serial
import serial.tools.list_ports
import argparse

PAYLOAD_TERMINATOR = b'\n'
KNOWN_DEVICES = {"USB-SERIAL CH340"}


class PayloadTooBigException(BaseException):
    pass

ser = Serial()
app = Bottle()

def find_device_port():
    for port in serial.tools.list_ports.comports():
        for known_device in KNOWN_DEVICES:
            if known_device in port.description:
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

@app.post('/')
@enable_cors
def request_to_serial():
    try:
        payload = request.json()['payload']
        return {'response': payload}
        response = send_payload_to_serial(payload)
        return {'response': response}
    except PayloadTooBigException:
        return {'error': 'payload too big'}


def send_payload_to_serial(payload:str) -> str:
    payload_bytes = bytes(payload, encoding='ascii') + PAYLOAD_TERMINATOR

    if len(payload_bytes) > 128:
        raise PayloadTooBigException()

    ser.write(payload_bytes)
    response_bytes = ser.read_until(PAYLOAD_TERMINATOR)[:-1]
    response = str(response_bytes, encoding='ascii')
    return response


def parse_args():
    arg_parser = argparse.ArgumentParser(description='Forwards 0 terminated messages between HTTP and serial port')
    arg_parser.add_argument('--serialport', '-s', help='Serial port', metavar='PORT', default=find_device_port(), type=str)
    arg_parser.add_argument('--baudrate', '-b', help='Serial baud rate', metavar='RATE', default=115200, type=int)
    return arg_parser.parse_args()


if __name__ == "__main__":
    args = parse_args()

    ser.port = args.serialport
    ser.baudrate = args.baudrate
    ser.open()

    run(app, host='localhost', port=9876)
