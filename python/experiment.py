# experiment

import rlglue.RLGlue as RLGlue

episode = 0

def runEpisode(stepLimit):
	global episode
	terminal = RLGlue.RL_episode(stepLimit)
	totalSteps = RLGlue.RL_num_steps()
	totalReward = RLGlue.RL_return()

	print "Episode {}\t {} steps\t {} total reward\t {} natural end".format(episode, totalSteps, totalReward, terminal)

	episode += 1

print "\n\nStarting experiment"
task_spec = RLGlue.RL_init()
print "task spec: " + task_spec

runEpisode(10000)