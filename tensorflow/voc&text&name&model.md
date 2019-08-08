## Text

* #####embedding

```python
# Embeddings
embedding_table = tf.get_variable(
    'embedding', [len(symbols), hp.embed_depth], dtype=tf.float32,
    initializer=tf.truncated_normal_initializer(stddev=0.5)
)
embedded_inputs = tf.nn.embedding_lookup(embedding_table, inputs)  # [N, T_in, embed_depth=256]

```

* ##### 拼接

```python
tf.concat(
    [conv1d(inputs, k, 128, tf.nn.relu, is_training, 'conv1d_%d' % k) for k in range(1, K + 1)],
    axis=-1
)
```



## VOC

## name

## model

* ##### FC

```python
"""
inputs: 该层的输入
units: 输出的大小（维数），整数或long
activation: 使用什么激活函数（神经网络的非线性层），默认为None，不使用激活函数
use_bias: 使用bias为True（默认使用），不用bias改成False即可
"""
dense = tf.layers.dense(x, units=size, activation=tf.nn.relu, name='dense_%d' % (i + 1))
```

* ##### dropout

```python
x = tf.layers.dropout(dense, rate=drop_rate, training=is_training, name='dropout_%d' % (i + 1))
```

* ##### Conv1d

```python
conv1d_output = tf.layers.conv1d(
            inputs,
            filters=channels,
            kernel_size=kernel_size,
            activation=activation,
            padding='same'
)
```

* ##### BN

```python
tf.layers.batch_normalization(conv1d_output, training=is_training)
```

* ##### MaxPool

```python
tf.layers.max_pooling1d(conv_outputs,pool_size=2,strides=1,padding='same')
```

* ##### highway net layer

```python
def highwaynet(inputs, scope, depth):
    with tf.variable_scope(scope):
        H = tf.layers.dense(
            inputs,
            units=depth,
            activation=tf.nn.relu,
            name='H')
        T = tf.layers.dense(
            inputs,
            units=depth,
            activation=tf.nn.sigmoid,
            name='T',
            bias_initializer=tf.constant_initializer(-1.0))
        return H * T + inputs * (1.0 - T)
```

