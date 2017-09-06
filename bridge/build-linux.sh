#!/bin/bash
sudo -H pip3 install -r requirements.txt
sudo -H pip3 install git+https://github.com/pyinstaller/pyinstaller.git
pyinstaller --console --onefile --clean bridge.py --name bridge-linux-x64
rm -rf build
rm bridge-linux-x64.spec