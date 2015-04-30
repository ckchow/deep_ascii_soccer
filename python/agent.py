#!/usr/bin/env /usr/bin/python
# team wild dogges

from rlglue.agent.Agent import Agent
from rlglue.agent import AgentLoader as AgentLoader
from rlglue.types import Action
from rlglue.types import Observation

import qnn
import time
import random

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


class team_agent(Agent):
	# (string) -> void
	def agent_init(self, taskSpecification):
		self.policy_frozen = False
		self.total_steps = 0
		self.trial_start = 0.0
		self.step_number = 0
		self.epsilon = 0.75 # exploration factor
		self.last_action = None
		self.last_state = None
		self.num_states = 4 * (9 + 2 + 1)

		params = {
			"num_actions": 11,
			"input_size": self.num_states,
			"max_experiences": 500,
			"gamma": 0.6,
			"alpha": 0.2
		}

		self.Q = [qnn.QNN(params) for i in xrange(4)]
	
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
		pass

	def qnnAction(self, observation):
		# epsilon-greedy
		if (random.random() > self.epsilon):
			act = Action()
			act.intArray.extend([self.Q[i].predict(s) for i in xrange(4)])
			return act
		else:
			return self.random_action()

	def qnnUpdate(self, observation, action, reward):
		if not (self.last_state and self.last_action):
			# must have both pieces
			return

		s = observation
		ls = self.last_state
		a = action
		la = self.last_action

		[self.Q[i].RememberExperience(ls, la, reward, s, a)
			for i in xrange(r)]

	def random_action(self):
		act = Action()
		act.intArray.extend([random.randint(0,10) for i in xrange(4)])
		return act

	def save(self, filename):
		pass

	def load(self, filename):
		pass



if __name__=="__main__":
	AgentLoader.loadAgent(team_agent())