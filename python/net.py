import lasagne
import theano.tensor as T
import theano
import numpy as np

LEARNING_RATE = 0.01
MOMENTUM = 0.9
NUM_EPOCHS = 100

class Net(object):
	def __init__(self, input_dim, output_dim):
		self._output = build_model(input_dim, output_dim)
		functions = create_functions(self._output)

		self._train = functions["train"]
		self._test = functions["test"]
		self._predict = functions["predict"]
		self._score = functions["score"]

	def propagate(self, state):
		return self._score(state)

	def propagateAndUpdate(self, state, action):
		"""
		Dummy function for doing training.
		"""
		return self._train(state, action)

	def update(self, x, y):
		"""
		Backprop error from prediction. Single step of SGD.
		"""
		return self._train(x, y)

	def predict(self, state):
		
		state = np.array(state, dtype=np.float32)

		return self._predict(state)

	def get_params(self):
		return lasagne.layers.get_all_param_values(self._output)

	def set_params(self, params):
		lasagne.layers.set_all_param_values(self._output, params)




def build_model(input_dim, output_dim):
	"""
	Create a representation of a neural net with the dimensions specified.
	"""

	l_in = lasagne.layers.InputLayer(
		shape=(1, input_dim)
		)

	l_hidden1 = lasagne.layers.DenseLayer(
		l_in, 
		num_units=512,
		nonlinearity=lasagne.nonlinearities.rectify
		)

	l_hidden1_dropout = lasagne.layers.DropoutLayer(
		l_hidden1)

	l_hidden2 = lasagne.layers.DenseLayer(
		l_hidden1_dropout,
		num_units=512,
		nonlinearity=lasagne.nonlinearities.rectify
		)
	l_hidden2_dropout = lasagne.layers.DropoutLayer(
		l_hidden2)

	l_out = lasagne.layers.DenseLayer(
		l_hidden2_dropout, 
		num_units=output_dim,
		nonlinearity=lasagne.nonlinearities.softmax)

	return l_out

# there's two ways to optimize Q, batchwise with experience replay or with single updates
def create_functions(output_layer, 
					 learning_rate=LEARNING_RATE):
	X = T.fvector('x')
	Y = T.ivector('y')

	objective = lasagne.objectives.Objective(output_layer,
		loss_function=lasagne.objectives.categorical_crossentropy)

	loss_train = objective.get_loss(X, target=Y)
	loss_eval = objective.get_loss(X, target=Y, deterministic=True)

	pred = T.argmax(
		output_layer.get_output(X, determinstic=True), axis=1)

	accuracy = T.mean(T.eq(pred, Y), dtype=theano.config.floatX)

	all_params = lasagne.layers.get_all_params(output_layer)

	# updates = lasagne.updates.nesterov_momentum(
	# 	loss_train, all_params, learning_rate, momentum)

	updates = lasagne.updates.adadelta(loss_train, all_params,
					learning_rate=learning_rate)

	train = theano.function(
		[X, Y], loss_train,
		updates=updates,
		)

	predict = theano.function(
		[X], pred)

	test = theano.function(
		[X, Y], [loss_eval, accuracy]
		)

	score = theano.function(
		[X], output_layer.get_output(X, deterministic=True))

	return {
		"train": train,
		"test": test,
		"predict": predict,
		"score": score
	}