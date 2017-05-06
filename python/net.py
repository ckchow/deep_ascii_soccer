# import lasagne
# import theano.tensor as T
# import theano
import tensorflow.contrib.slim as slim
import tensorflow as tf
import numpy as np

LEARNING_RATE = 0.01
MOMENTUM = 0.9
NUM_EPOCHS = 100

class Net(object):
    def __init__(self, input_dim, output_dim):
        # best actions
        self._labels = tf.placeholder(tf.int32, [None, output_dim], name='label')
        # state inputs
        self._input = tf.placeholder(tf.float32, [None, input_dim], name='state_input')

        self._logits = build_model(self._input, output_dim)

        self._pred_loss = slim.losses.softmax_cross_entropy(self._logits, self._labels)

        self._loss =slim.losses.get_total_loss()

        self._predict = tf.cast(tf.argmax(self._logits, 1), tf.int32)

        self._accuracy = tf.reduce_mean(tf.cast(tf.equal(self._predict, self._labels), tf.float32))

        optimizer = tf.train.MomentumOptimizer(LEARNING_RATE, MOMENTUM)

        self._train = slim.learning.create_train_op(self._loss, optimizer)

        init = tf.initialize_all_variables()


        self.session = tf.Session()

        self.session.run(init)

        # functions = create_functions(self._output)

        # self._train = functions["train"]
        # self._test = functions["test"]
        # self._predict = functions["predict"]
        # self._score = functions["score"]

    def propagate(self, state):
        # return self._score(state)
        retval = self.session.run(self._logits, feed_dict={self._input: state})
        return retval

    def propagateAndUpdate(self, state, action):
        """
        Do training
        """
        # return self._train(state, action)
        out, _ = self.session.run([self._logits, self._train], feed_dict={self._labels: action,
                                                                          self._input: state})
        return out

    def update(self, x, y):
        """
        Backprop error from prediction. Single step of SGD.
        """

        self.session.run(self._train, feed_dict={self._labels: y,
                                                 self._input: x})

        return

    def predict(self, state):

        state = np.array(state, dtype=np.float32)

        retval = self.session.run(self._predict, feed_dict={self._input: state})

        return retval

    # def get_params(self):
    #     return lasagne.layers.get_all_param_values(self._output)

    # def set_params(self, params):
    #     lasagne.layers.set_all_param_values(self._output, params)




def build_model(input, output_dim):
    """
    Create a representation of a neural net with the dimensions specified. (Up to logits)
    """
    model = slim.fully_connected(input, 512, scope='fc1')
    model = slim.dropout(model)
    model = slim.fully_connected(model, 512, scope='fc2')
    model = slim.fully_connected(model, output_dim, scope='output')

    # l_in = lasagne.layers.InputLayer(
    #     shape=(1, input_dim)
    #     )
    #
    # l_hidden1 = lasagne.layers.DenseLayer(
    #     l_in,
    #     num_units=512,
    #     nonlinearity=lasagne.nonlinearities.rectify
    #     )
    #
    # l_hidden1_dropout = lasagne.layers.DropoutLayer(
    #     l_hidden1)
    #
    # l_hidden2 = lasagne.layers.DenseLayer(
    #     l_hidden1_dropout,
    #     num_units=512,
    #     nonlinearity=lasagne.nonlinearities.rectify
    #     )
    # l_hidden2_dropout = lasagne.layers.DropoutLayer(
    #     l_hidden2)
    #
    # l_out = lasagne.layers.DenseLayer(
    #     l_hidden2_dropout,
    #     num_units=output_dim,
    #     nonlinearity=lasagne.nonlinearities.softmax)

    return model

# there's two ways to optimize Q, batchwise with experience replay or with single updates
def create_functions(logits,
                     learning_rate=LEARNING_RATE):
    # X = T.fvector('x')
    # Y = T.ivector('y')

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