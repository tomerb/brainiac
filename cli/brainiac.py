import brainiac
import sys
import time

if len(sys.argv) != 2:
    sys.exit("Missing configuration file or too many arguments")

brain_instance = brainiac.brain.instance()
brain_instance.start(sys.argv[1])

time.sleep(100)
