# team wild dogges

from rlglue.agent.Agent import Agent
from rlglue.agent import AgentLoader as AgentLoader
from rlglue.types import Action
from rlglue.types import Observation

import qnn
import time


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
		self.last_observation = None
		self.num_states = 4 * (9 + 2 + 1)

		params = {
			"num_actions": 10,
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

		return outAction
	
	# (double, Observation) -> Action
	def agent_step(self, reward, observation):
		outAction = Action()
		outAction.intArray = [10, 10, 10, 10]
		
		return outAction
	
	# (double) -> void
	def agent_end(self, reward):
		pass
	
	# () -> void
	def agent_cleanup(self):
		pass

	# (string) -> string
	def agent_message(self, message):
		pass


if __name__=="__main__":
	AgentLoader.loadAgent(team_agent())