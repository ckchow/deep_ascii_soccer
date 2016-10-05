#!/usr/bin/env python

import subprocess
import sys
import os
import argparse
import datetime
import time
import signal
import sys
import ntpath
import atexit
import shlex

parser = argparse.ArgumentParser(description="deep soccer evaluator")
parser.add_argument("--glue_port", type=str, default="4096",
                    help="rlglue port (default 4096)")
parser.add_argument('--logdir', type=str, default='./logs',
                    help='dir to keep logs in')
# args = parser.parse_known_args()[0]
args = parser.parse_args()
my_env = os.environ.copy()

my_env["RLGLUE_PORT"] = args.glue_port
my_env['PATH'] = '/usr/local/bin:' + my_env['PATH']

time_dir = os.path.abspath(
            datetime.datetime.now().strftime("{}/log_%Y%m%d(%H:%M:%S)".format(args.logdir))
)

try:
    os.makedirs(time_dir)
except os.error:
    print "directory already exists"
    sys.exit(0)

logfiles = []


def run(cmd, logdir, logfiles):
    cmdname = cmd.split(" ")[0]
    fname = os.path.splitext(ntpath.basename(cmdname))[0]

    logpath = os.path.join(logdir, fname+"_log")
    errpath = os.path.join(logdir, fname+"_err")

    print "cmd:", cmd
    print "logpath:", logpath
    print "errpath:", errpath
    print

    logfile = open(logpath, "w")
    errfile = open(errpath, "w")
    logfiles.append(logfile)
    logfiles.append(errfile)
    runcmd = ['/usr/bin/env', ] + shlex.split(cmd)
    # runcmd = shlex.split(cmd)
    p = subprocess.Popen(runcmd, shell=False, universal_newlines=True,
                         stdout=logfile, stderr=errfile, env=my_env)


    return p

mypath = os.path.dirname(os.path.realpath(__file__))

p_core = run("rl_glue", time_dir, logfiles)
p_agent = run(sys.executable + ' ' + os.path.join(mypath, "python/agent.py"), time_dir, logfiles)
p_experiment = run(sys.executable + ' ' + os.path.join(mypath, "python/experiment.py {}".format(time_dir)),
                    time_dir, logfiles)

p_environment = run(os.path.join(mypath, "soccer"), time_dir, logfiles)

def close(process):
    if process.poll() is None:
        # None if the process is alive
        print 'killing', process
        process.terminate()


@atexit.register
def cleanup():
    global logfiles, p_core, p_agent, p_experiment, p_environment
    print "program exiting"
    for l in logfiles:
        try:
            l.flush()
        except:
            pass

    for p in (p_core, p_agent, p_environment, p_experiment):
        try:
            close(p)
        except:
            pass
    sys.exit(0)

def signal_handler(signal, frame):
    print "caught ctrl-c"
    cleanup()
    sys.exit(0)

signal.signal(signal.SIGINT, signal_handler)



p_core.wait()