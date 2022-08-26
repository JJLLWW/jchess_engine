#!/usr/bin/python3

import subprocess as sp
import os
import webbrowser

# for now use stockfish to see if automation is even possible.
# the intial cargo build should be done in CMake to avoid inconsistent behaviour.
sf_exe = os.path.join(os.getcwd(), 'third_party', 'tmp_win_stockfish', 'stockfish.exe')
lichess_dir = os.path.join(os.getcwd(), 'third_party', 'external-engine', 'remote-uci')

# subprocess.run() waits for command to finish so should use subprocess.Popen()
p = sp.Popen(
    cwd=lichess_dir ,args=['cargo', 'run', '--', '--engine', sf_exe], 
    stdout= sp.PIPE,
    # stderr= sp.PIPE,
    text=True,
    bufsize=1    
)

url = p.stdout.readline()
print(f'got url "{url}"')
# TODO: error handling
webbrowser.open(url, new=1)
input("press any key to quit")
p.kill()