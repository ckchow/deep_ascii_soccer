# team wild dogges

from rlglue.agent.Agent import Agent
from rlglue.agent import AgentLoader as AgentLoader
from rlglue.types import Action
from rlglue.types import Observation


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
	last_action = Action()
	last_observation = Observation()
	num_states = 4 * (9 + 2 + 1)
	num_actions = 4
	value_function = 0

	# (string) -> void
	def agent_init(self, taskSpecification):
		# don't care about the taskstring, it's all hardcoded


		pass
	
	# (Observation) -> Action
	def agent_start(self, observation):
		# debug, just tell everyone to go north
		outAction = Action()
		outAction.intArray = [10, 10, 10, 10]

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