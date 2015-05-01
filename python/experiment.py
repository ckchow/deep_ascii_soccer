#!/usr/bin/env /usr/bin/python

import rlglue.RLGlue as RLGlue
import sys

episode = 0
EPOCHS = 100

def runEpisode(stepLimit):
	global episode
	terminal = RLGlue.RL_episode(stepLimit)
	totalSteps = RLGlue.RL_num_steps()
	totalReward = RLGlue.RL_return()

	print "Episode {}\t {} steps\t {} total reward\t {} natural end"\
			.format(episode, totalSteps, totalReward, terminal)

	episode += 1

if __name__ == "__main__":
	RLGlue.RL_init()

	print "\n\nStarting training."
	
	for i in xrange(EPOCHS):
		runEpisode(10000)
		sys.stdout.flush()
		sys.stderr.flush()