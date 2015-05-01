#!/usr/bin/env /usr/bin/python
# team wild dogges

from rlglue.agent.Agent import Agent
from rlglue.agent import AgentLoader as AgentLoader
from rlglue.types import Action
from rlglue.types import Observation

import qnn
import time
import random
import argparse

import sys

NW = 0
N = 1
NE = 2
W = 3
PLAYER = 4
E = 5
SW = 6
S = 7
SE = 8

KICK = 9
DO_NOTHING = 10
BIGGEST_ACTION = 10

NUM_STATES = 4 * (9 + 2 + 1)

default_params = {
"num_actions": 11,
"input_size": NUM_STATES,
"max_experiences": 500,
"gamma": 0.6,
"alpha": 0.2,
"use_sarsa": True
}


class team_agent(Agent):
	# (string) -> void
	def agent_init(self, taskSpecification):
		print "agent started"
		self.policy_frozen = False
		self.total_steps = 0
		self.trial_start = 0.0
		self.step_number = 0
		self.epsilon = 0.75 # exploration factor
		self.last_action = None
		self.last_state = None
		self.num_states = NUM_STATES

		self.Q = [qnn.QNN(**default_params) for i in xrange(4)]
		self.savedir = None

		def set_savedir(dirname):
			self.savedir = dirname

	# (Observation) -> Action
	def agent_start(self, observation):
		self.step_number = 0
		self.trial_start = time.clock()

		return self.qnnAction(observation)

	# (double, Observation) -> Action
	def agent_step(self, reward, observation):
		self.step_number += 1
		self.total_steps += 1
		act = self.qnnAction(observation)
		
		if not self.policy_frozen:
			self.qnnUpdate(observation, act, reward)

		self.last_state = observation
		self.last_action = act

		if self.step_number % 1000 == 0:
			sys.stdout.flush()
			sys.stderr.flush()

		return act

	# (double) -> void
	def agent_end(self, reward):
		time_elapsed = time.clock() - self.trial_start
		print "AGENT: ended after {} steps".format(self.total_steps)
		print "AGENT: avg {:.2} steps per second".\
		format(self.step_number/time_elapsed)

	# () -> void
	def agent_cleanup(self):
		pass

	# (string) -> string
	def agent_message(self, message):
		if inMessage.startswith("freeze_learning"):
			self.policy_frozen=True
			return "agent: policy frozen"
		if inMessage.startswith("unfreeze_learning"):
			self.policy_frozen=False
			return "agent: policy unfrozen"
		if inMessage.startswith("set_exploring"):
			splitString=inMessage.split(" ")
			self.epsilon = float(splitString[1])
			return "agent: setting exploration factor to {}"\
				.format(self.epsilon)
		if inMessage.startswith("save_policy"):
			splitString=inMessage.split(" ")
			self.save(splitString[1])
			print "agent: policy saved"
			return "agent: saving policy"
		if inMessage.startswith("load_policy"):
			splitString=inMessage.split(" ")
			self.load(splitString[1])
			print "agent: policy loaded"
			return "agent: loading policy"
		if inMessage.startswith("use_impactful_experiences"):
			self.Q.use_impactful = True
			return "agent: using impactful experiences"
		if inMessage.startswith("use_all_experiences"):
			self.Q.use_impactful = False
			return "agent: using all experiences"
		if inMessage.startswith("reset_q"):
			self.Q = [qnn.QNN(**default_params) for i in xrange(4)]
			return "agent: reseting q-function"

	def qnnAction(self, observation):
		# print "qnnAction"

		# epsilon-greedy
		if (random.random() > self.epsilon):
			s = observation.intArray
			act = Action()
			act.intArray.extend([self.Q[i].predict(s) for i in xrange(4)])
			return act
		else:
			return self.random_action()

	def qnnUpdate(self, observation, action, reward):
		if not (self.last_state and self.last_action):
			# must have both pieces
			return

		s = observation.intArray
		ls = self.last_state.intArray
		a = action.intArray
		la = self.last_action.intArray

		[self.Q[i].RememberExperience(ls, la, reward, s, a)
		for i in xrange(4)]

	def random_action(self):
		act = Action()
		act.intArray.extend([random.randint(0,10) for i in xrange(4)])

		# print act.intArray

		return act

	def save(self, filename):
		pass

	def load(self, filename):
		pass

if __name__=="__main__":
	agent = team_agent()

	# TODO set save directories

	AgentLoader.loadAgent(agent)
	print "agent loaded!!!"