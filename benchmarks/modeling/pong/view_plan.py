#!/usr/bin/python3
import sys
import os
import argparse

def parse_arguments() :

    parser = argparse.ArgumentParser( description = "View Pong Plan Execution" )
    parser.add_argument( "--field", required=True, help="Either 'small' or 'atari2600'" )
    args = parser.parse_args()

    if arg.field not in ('small', 'atari2600') :
        print("Pong field '{}' not supported".format(args.field))
        raise SystemExit()

    return args, instance

def main() :
    from PyQt5 import QtWidgets
    from viz.main import ViewerMainWindow


    cmd_line_args, instance = parse_arguments()

    app = QtWidgets.QApplication(sys.argv)
    app.lastWindowClosed.connect(app.quit)
    window = ViewerMainWindow( instance )
    window.show()
    app.exec_()


if __name__ == '__main__' :
    main()
