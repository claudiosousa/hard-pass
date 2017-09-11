pip install -r requirements.txt
pip install git+https://github.com/pyinstaller/pyinstaller.git
pyinstaller --console --onefile --clean bridge.py --name bridge-win-x64
rd /s /q build
del /f /q bridge-win-x64.spec
