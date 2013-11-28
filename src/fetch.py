#!/usr/bin/env python

from __future__ import print_function

from sys import argv, stderr
from os.path import isfile
from time import sleep

from requests import get
from requests.exceptions import ConnectionError

URL = "http://10.0.0.82/"
AUTH = ("api", "secret")

addr_to_loc = {}

timeout = float(argv[1]) if len(argv) >= 2 else 2

if isfile("map_addr.txt"):
    with open("map_addr.txt") as f:
        # the file should contain lines starting with sensor address in HEX
        # followed by string which will be used as the sensor's name
        for line in f.readlines():
            addr, location = line.split(maxsplit=1)
            addr_to_loc[addr] = location.strip()

while True:
    try:
        r = get(URL, auth=AUTH)
    except ConnectionError:
        exit("connection timed out")

    if r.status_code != 200:
        print("status code was {} instead of 200".format(r.status_code),
              file=stderr)
        exit(1)

    sensors = r.json()['sensors']

    for sensor in sensors:
        addr, temp = list(sensor.items())[0]

        addr = addr_to_loc.get(addr, addr)

        print("temperature at {} is {:.2f}".format(addr, temp));
    print()

    if not timeout:
        exit()

    sleep(timeout);
