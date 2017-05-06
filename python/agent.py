#!/usr/bin/env python
# team wild dogges

from rlglue.agent.Agent import Agent
from rlglue.agent import AgentLoader as AgentLoader
from rlglue.types import Action
from rlglue.types import Observation

import numpy as np

import qnn
import time
import random
import argparse
import sys
import cPickle
import collections

NW = 0
N = 1
NE = 2
W = 3
PLAYER = 4
E = 5
SW = 6
S = 7
SE = 8

DIRECTIONS = ('NW', 'N', 'NE', 'W', 'PLAYER', 'E', 'SW', 'S', 'SE')
OCCUPANTS = ('EMPTY', 'GOAL', 'BALL', 'BOUNDARY', 'WEST_PLAYER', 'EAST_PLAYER')
OCCUPANT_LOOKUP = dict(zip(range(len(OCCUPANTS)), OCCUPANTS))

KICK = 9
DO_NOTHING = 10
BIGGEST_ACTION = 10

# players * (occupancy + xy_pos + ball_heading)
NUM_STATES = 4 * (9 + 2 + 1)

# players * (movedir + kick + nothing)
NUM_ACTIONS = 4 * (9 + 1 + 1)

default_params = {
"num_actions": NUM_ACTIONS,
"input_size": NUM_STATES,
"max_experiences": 500,
"gamma": 0.6,
"alpha": 0.2,
"use_sarsa": True
}


class TeamManager(Agent):
    # (string) -> void
    def agent_init(self, taskSpecification):
        print "agent started"
        self.policy_frozen = False
        self.total_steps = 0
        self.trial_start = 0.0
        self.step_number = 0
        self.epsilon = 0.05 # exploration factor
        self.last_action = None
        self.last_state = None
        self.num_states = NUM_STATES

        # self.Q = [qnn.QNN(**default_params) for _ in xrange(4)]
        self.Q = qnn.QNN(**default_params)
        self.savedir = None

        self.dump_state = False


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

        if self.dump_state:
            print observation.intArray

        if self.step_number % 50 == 0:

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
        sys.stdout.flush()
        sys.stderr.flush()

    # (string) -> string
    def agent_message(self, message):
        if message.startswith("freeze_learning"):
            self.policy_frozen=True
            return "agent: policy frozen"
        if message.startswith("unfreeze_learning"):
            self.policy_frozen=False
            return "agent: policy unfrozen"
        if message.startswith("set_exploring"):
            splitString=message.split(" ")
            self.epsilon = float(splitString[1])
            return "agent: setting exploration factor to {}"\
                .format(self.epsilon)
        if message.startswith("save_policy"):
            splitString=message.split(" ")
            self.save(splitString[1])
            print "agent: policy saved"
            return "agent: saving policy"
        if message.startswith("load_policy"):
            splitString=message.split(" ")
            self.load(splitString[1])
            print "agent: policy loaded"
            return "agent: loading policy"
        if message.startswith("use_impactful_experiences"):
            self.Q.use_impactful = True
            return "agent: using impactful experiences"
        if message.startswith("use_all_experiences"):
            self.Q.use_impactful = False
            return "agent: using all experiences"
        if message.startswith("reset_q"):
            self.Q = qnn.QNN(**default_params)
            return "agent: reseting q-function"
        if message.startswith("dump_states_enable"):
            self.dump_state = True
            return "agent: dumping all states to log"

        if message.startswith("dump_states_disable"):
            self.dump_state = False
            return "agent: stopped dumping states to log"



    def qnnAction(self, observation):

        # epsilon-greedy
        if (random.random() > self.epsilon):
            s = observation.intArray
            act = Action()
            # act.intArray.extend([self.Q[i].predict(s) for i in xrange(4)])
            act.intArray = self.Q.predict(s[np.newaxis, :])
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

        self.Q.RememberExperience(ls, la, reward, s, a)

    def random_action(self):
        act = Action()
        act.intArray.extend([random.randint(0,10) for _ in xrange(4)])

        # print act.intArray

        return act

    def save(self, filename):
        # params = [self.Q[i].NN.get_params() for i in xrange(4)]
        #
        # with open(filename, "w") as pfile:
        #     cPickle.dump(params, pfile)
        print 'save disabled you fooool'


    def load(self, filename):
        # with open(filename, "r") as pfile:
        #     params = cPickle.load(pfile)
        #
        # [self.Q[i].NN.set_params(params[i]) for i in xrange(4)]
        print 'loading disabled for now'

# for looking at states
def decompress_state(state):
    # x y neighborhood(9) ball direction
    for player_index in range(4):
        s = state[player_index * 12:]

        x = s[0]
        y = s[1]

        occupant_list = []

        for i, direction in enumerate(DIRECTIONS):
            occupant = s[i + 2] # skip the position states
            if (OCCUPANT_LOOKUP[occupant] != 'EMPTY'):
                occupant_list.append((OCCUPANT_LOOKUP[occupant], direction))

        ball_direction = DIRECTIONS[s[11]]

    return 'x: {}, y: {}'

if __name__=="__main__":
    agent = TeamManager()

    AgentLoader.loadAgent(agent)
