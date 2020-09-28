```python
import tensorflow as tf
import numpy as np
import matplotlib.pyplot as plt
import pickle
from tinghua_voice.r_cnn.net import cnn_1
import os

# param
param = {
    "bs": 32,
    "lr": 0.001,
    "x_shape": (1000, 26),
    "y_shape": 1000,
    "log_save": "./logs/",
    "max_step": 100000
}

logs = {
    "train_loss": [],
    "test_loss": []
}

# tf config
config = tf.ConfigProto()
config.gpu_options.per_process_gpu_memory_fraction = 0.6
my_global_step = tf.Variable(0, name="global_step", trainable=False)
# holders
x_holder = tf.placeholder("float", [param['bs'], param["x_shape"][0], param["x_shape"][1]])
x_reshape = tf.reshape(x_holder, shape=[param['bs'], param["x_shape"][0], param["x_shape"][1], 1])
y_holder = tf.placeholder("float", [param['bs'], param['y_shape']])
rate_holder = tf.placeholder("float")
drop_holder = tf.placeholder("float")
# input net
logist = cnn_1.net(x_reshape, drop_holder)
# loss
mse_loss = tf.reduce_sum(tf.square(y_holder - logist))
tf.add_to_collection("losses", mse_loss)
loss = tf.add_n(tf.get_collection("losses"))
# train step
train_step = tf.train.GradientDescentOptimizer(rate_holder).minimize(loss, global_step=my_global_step)
# init
init = tf.global_variables_initializer()
sess = tf.Session(config=config)
sess.run(init)
saver = tf.train.Saver(tf.global_variables())
# get datas
train_datas = []
train_labels = []
test_datas = []
test_labels = []
# start train
for step in range(param["max_step"]):
    index_random = np.random.choice(len(train_datas), param["bs"], replace=False)
    batch_x = train_datas[index_random]
    batch_y = train_labels[index_random]
    sess.run(train_step,
             feed_dict={
                 x_holder: batch_x, y_holder: batch_y, rate_holder: param["lr"], drop_holder: 0.5
             })
    if step % 500 == 0:
        test_index = np.random.choice(len(test_datas), param["bs"], replace=False)
        test_x = test_datas[test_index]
        test_y = test_labels[test_index]
        train_lo = sess.run(loss,
                            feed_dict={
                                x_holder: batch_x, y_holder: batch_y, rate_holder: 0,
                                drop_holder: 1
                            })
        test_lo = sess.run(loss,
                           feed_dict={
                               x_holder: test_x, y_holder: test_y, rate_holder: 0,
                               drop_holder: 1
                           })
        logs["train_loss"].append(train_lo)
        logs["test_loss"].append(test_lo)
        print("step:%d,train loss :%f ; test Loss:%f" % (step, train_lo, test_lo))
    if step % 5000 == 0:
        plt.plot(range(len(logs["train_loss"])), logs["train_loss"])
        plt.plot(range(len(logs["test_loss"])), logs["test_loss"])
        plt.savefig('./plots/loss%d.svg' % step, dpi=600)
        plt.show()
    if step % 5000 == 0 or step == param["max_step"] - 1:
        try:
            checkpoint_path = os.path.join(param["log_save"], "model.ckpt")
            saver.save(sess, checkpoint_path, global_step=my_global_step)
        except Exception:
            print("save error")

```

```python
import tensorflow as tf


def weight(shape):
    initial = tf.random_normal(shape=shape)
    var = tf.Variable(initial)
    tf.add_to_collection("losses", tf.contrib.layers.l2_regularizer(0.0005)(var))
    return var


def biases(shape):
    return tf.Variable(tf.constant(0.1, shape=shape)),


def bathNormal(x, training=True):
    return tf.layers.batch_normalization(x, training=training)


def conv2d(x, W):
    return tf.nn.conv2d(x, W, strides=[1, 1, 1, 1], padding="SAME")


def max_pool_2x2(x):
    return tf.nn.max_pool(x, ksize=[1, 2, 2, 1], strides=[1, 2, 2, 1], padding="SAME")


def avg_pool_2x2(x):
    return tf.nn.avg_pool(x, ksize=[1, 2, 2, 1], strides=[1, 2, 2, 1], padding="SAME")

def lstm(x_in,cell_num,name):
    with tf.variable_scope(name):
        lstm_cell = tf.contrib.rnn.BasicLSTMCell(cell_num, state_is_tuple=True)
        init_state = lstm_cell.zero_state(x_in.shape[0], dtype=tf.float32)
        outputs, states = tf.nn.dynamic_rnn(lstm_cell, x_in, initial_state=init_state)
    return outputs
```

```python
# x_in = tf.reshape(x, [-1, 250, 26])
    """
    return :
    outputs = tf.unstack(tf.transpose(outputs, [1, 0, 2]))
    fc_1 = tf.nn.relu(tf.matmul(outputs[-1], weight([256, 512])) + biases([512]))
    
     with tf.variable_scope("lstm_2"):
        lstm_cell = tf.contrib.rnn.BasicLSTMCell(256, state_is_tuple=True)
        init_state = lstm_cell.zero_state(outputs.shape[0], dtype=tf.float32)
        outputs, states = tf.nn.dynamic_rnn(lstm_cell, outputs, initial_state=init_state)
        
         # (bs , 250, 26 ,1)
    reshape = tf.reshape(x, [-1, 250, 26])
    lstm_1 = lstm(reshape, 128, "lstm_1")
    lstm_2 = lstm(lstm_1, 128, "lstm_2")
    outputs = tf.unstack(tf.transpose(lstm_2, [1, 0, 2]))
    """
```

```
conv_1 = max_pool_2x2(tf.nn.relu(bathNormal(
    conv2d(x, weight([5, 5, 1, start])) + biases([start])
)))
fc_2 = tf.nn.sigmoid(tf.matmul(fc_1, weight([512, 20])) + biases([20]))

fc1_drop = tf.nn.dropout(fc1, drop)
```

# restore

```
import tensorflow as tf
config = tf.ConfigProto()
config.gpu_options.per_process_gpu_memory_fraction = 0.6
my_global_step = tf.Variable(0, name="global_step", trainable=False)


param = {
    "bs": 250,
    "x_shape": (1, 26),
    "y_shape": 1,
    "log_save": "./test_logs/",
    "num_class": 2
}

x_holder = tf.placeholder("float", [param['bs'], param["x_shape"][1]])
x_reshape = tf.reshape(x_holder, shape=[param['bs'], param["x_shape"][1], 1])

logist = cnn_1.net(x_reshape)
sess = tf.Session(config=config)
saver = tf.train.Saver(tf.global_variables())
coord = tf.train.Coordinator()
thread = tf.train.start_queue_runners(coord=coord, sess=sess)
ckpt = tf.train.get_checkpoint_state(param["log_save"])
if ckpt and ckpt.model_checkpoint_path:
    saver.restore(sess, ckpt.model_checkpoint_path)
    if coord.should_stop():
        print("error")
    else:
            pass
coord.request_stop()
coord.join(thread)
sess.close()
```