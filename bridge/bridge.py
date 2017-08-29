#!/usr/bin/env python3

from bottle import Bottle, run, request, HTTPError
from serial import Serial
import argparse

PAYLOAD_TERMINATOR = b'\0'


class PayloadTooBigException(BaseException):
    pass


ser = Serial()
app = Bottle()


@app.post('/')
def request_to_serial():
    try:
        payload = request.forms.get('payload')
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
    arg_parser.add_argument('--serialport', '-s', help='Serial port', metavar='PORT', required=True, type=str)
    arg_parser.add_argument('--baudrate', '-b', help='Serial baud rate', metavar='RATE', default=115200, type=int)
    return arg_parser.parse_args()


if __name__ == "__main__":
    args = parse_args()

    ser.port = args.serialport
    ser.baudrate = args.baudrate
    ser.open()

    run(app, host='localhost', port=8080)
