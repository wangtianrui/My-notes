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

* ##### Attention

  > BathdanauAttention

  ```python
  """
  def __init__(self,
      num_units,
      memory,
      memory_sequence_length=None,
      normalize=False,
      probability_fn=None,
      score_mask_value=None,
      dtype=None,
      name="BahdanauAttention"):
  """
  BahdanauAttention(hp.attention_depth, encoder_outputs)
  """
  numunits：神经元节点数，我们知道在计算
  memory：The memory to query; usually the output of an RNN encoder. 即解码时用到的上文信息，维度需要是 [batch_size, max_time, context_dim]
  """
  ```

  > AttentionWrapper   

  wrapper都是RNNCell的实例，该类可以加入attention机制

  ```python
  """
  def __init__(self,
      cell,
      attention_mechanism,
      attention_layer_size=None,
      alignment_history=False,
      cell_input_fn=None,
      output_attention=True,
      initial_cell_state=None,
      name=None):
  """
  # Attention
  attention_cell = AttentionWrapper(
      GRUCell(hp.attention_depth),
      BahdanauAttention(hp.attention_depth, encoder_outputs),
      alignment_history=True,
      output_attention=False)  # [N, T_in, attention_depth=256]
  """
  cell：An instance of RNNCell. RNNCell 的实例，这里可以是单个的 RNNCell，也可以是多个 RNNCell 组成的 MultiRNNCell。
  attention_mechanism：即 AttentionMechanism 的实例，如 BahdanauAttention 对象，另外可以是多个 AttentionMechanism 组成的列表。
  attention_layer_size：是数字或者数字做成的列表，如果是 None（默认），直接使用加权计算后得到的 Attention 作为输出，如果不是 None，那么 Attention 结果还会和 Output 进行拼接并做线性变换再输出。
  """
  ```
