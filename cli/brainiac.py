import brainiac
import sys

if len(sys.argv) != 2:
    sys.exit("Missing configuration file or too many arguments")

brainiac.brain.instance().start(sys.argv[1])
