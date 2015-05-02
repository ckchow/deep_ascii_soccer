#!/usr/bin/env /usr/bin/python

import rlglue.RLGlue as RLGlue
import sys
import argparse
import os

episode = 0
EPOCHS = 100

def runEpisode(stepLimit):
	global episode
	terminal = RLGlue.RL_episode(stepLimit)
	totalSteps = RLGlue.RL_num_steps()
	totalReward = RLGlue.RL_return()

	print "{}\t{}\t{}\t{}"\
			.format(episode, totalSteps, totalReward, terminal)

	episode += 1

if __name__ == "__main__":
	parser = argparse.ArgumentParser(description="Experiment runner for deep_ascii_soccer.")
	parser.add_argument('logdir', type=str, help="directory to save and load models")
	args = parser.parse_args()

	if not os.path.isdir(args.logdir):
		raise IOError("output directory doesn't exist")

	model_fname = os.path.join(args.logdir, "model.pkl")
	print model_fname

	RLGlue.RL_init()

	print "generating test states"
	print RLGlue.RL_agent_message("set_exploring 1.0")
	print RLGlue.RL_agent_message("freeze_learning")
	print RLGlue.RL_agent_message("dump_states")

	print "\nStarting training."

	print "Episode\tTotal Steps\tTotal Reward\tTerminated Naturally"
	
	for i in xrange(EPOCHS):
		runEpisode(10000)
		sys.stdout.flush()
		sys.stderr.flush()

	print "Dumping models"
	resp = RLGlue.RL_agent_message("save_policy {}".format(model_fname))
	print resp

	