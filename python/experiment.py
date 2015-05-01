#!/usr/bin/env /usr/bin/python

import rlglue.RLGlue as RLGlue
import sys
import argparse
import os

episode = 0
EPOCHS = 400

def runEpisode(stepLimit):
	global episode
	terminal = RLGlue.RL_episode(stepLimit)
	totalSteps = RLGlue.RL_num_steps()
	totalReward = RLGlue.RL_return()

	print "Episode {}\t {} steps\t {} total reward\t {} natural end"\
			.format(episode, totalSteps, totalReward, terminal)

	episode += 1

if __name__ == "__main__":
	parser = argparse.ArgumentParser(description="Experiment runner for deep_ascii_soccer.")
	parser.add_argument('logdir', type=str, help="directory to save and load models")
	args = parser.parse_args()

	if not os.path.isdir(args.logdir):
		raise IOError("output directory doesn't exist")

	print args.logdir

	RLGlue.RL_init()

	print "\n\nStarting training."
	
	for i in xrange(EPOCHS):
		runEpisode(10000)
		sys.stdout.flush()
		sys.stderr.flush()

	print "Dumping models"
	