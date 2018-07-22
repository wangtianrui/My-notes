## Deep learning

#### machine-learning --> deep-learning

| machine-learning                         | deep-learning                            |
| :--------------------------------------- | :--------------------------------------- |
| limited in their ability to process natural data in their raw form | a feature extractor that transformed the raw data (such as the pixel values of an image) into a suitable internalrepresentation or feature vector from which the learning subsystem, often a classifier, could detect or classify patterns in the input. |

* deep-learning can deal raw data by itself (end-to-end)

  1、Representation learning is a set of methods that allows a machine to be fed with raw data and to automatically discover the representations needed for detection or classification.

  2、Deep-learning methods are representation-learning methods with multiple levels of representation, obtained by composing simple but non-linear modules that each transform the representation at one level (starting with the raw input) into a representation at a higher, slightly more abstract level. 

* deep-learning  construction

  1、first layer of representation typically  represent

  2、second layer typically detects motifs

  3、The third layer may assemble motifs into larger combinations that correspond to parts of familiar objects

  4、subsequent layers would detect objects as combinations of these parts.

​    The key aspect of deep learning is that these layers of features are not designed by human engineers: they are learned from data using a general-purpose learning procedure.

​    linear classifiers can only carve their input space into very simple regions.problems such as image and speech recognition require the input–output function to be insensitive to irrelevant variations.

![](https://ws1.sinaimg.cn/large/0067fcixly1ftihkuzumbj30j207htal.jpg)

​    Note how a regular grid (shown on the left) in input space is also transformed (shown in the middle panel) by hidden units. (hidden units can make model more powerful on classify)

#### loss and optimize

​    We compute an objective function that measures the error (or distance) between the output scores and the desired pattern of scores. The machine then modifies its internal adjustable parameters to reduce this error. 

​    (SGD) computing the outputs and the errors, computing the average gradient for those examples

​    A two-class linear classifier computes a weighted sum of the feature vector components.

![](https://ws1.sinaimg.cn/large/0067fcixly1ftihlwxudmj31240eljv7.jpg)

​    At each layer, we first compute the total input z to each unit, which is a weighted sum of the outputs of the units in the layer below. Then a non-linear function f(.) is applied to z to get the output of the unit. 

​    A multilayer neural network (shown by the connected dots) can distort the input space to make the classes of data 

* activate functions

  |      function      |                 formula                  |
  | :----------------: | :--------------------------------------: |
  |        ReLU        |              f(z)= max(0,z)              |
  | hyberbolic tangent | f(z) =(exp(z)− exp(−z))/(exp(z)+ exp(−z)) |
  |       sigmod       |           f(z) =1/(1+ exp(−z))           |

#### CNN - image model

![](https://ws1.sinaimg.cn/large/0067fcixly1ftihsit6z7j30mf0900wf.jpg)

* construction

  raw images (-> conv -> relu -> pool )xN ->  fully-connected layers

|          name          |                 effects                  |
| :--------------------: | :--------------------------------------: |
|      conventional      | The conventional option is to hand design good feature extractors |
|        pooling         | the role of the pooling layer is to merge semantically similar features into one |
| fully-connected layers |                 classify                 |

​    In images, local combinations of edges form motifs, motifs assemble into parts, and parts form objects. 

​    hidden layers of a multilayer neural network learn to represent the network’s inputs in a way that makes it easy to predict the target outputs. 

#### language deep-learning model

* construction

  1、In the first layer, each word creates a different pattern of activations, or word vectors .

  2、the other layers of the network learn to convert the input word vectors into an output word vector for the predicted next word 。

| standard approach to statistical modelling of language |           deep-learning model            |
| :--------------------------------------: | :--------------------------------------: |
| it was based on counting frequencies of occurrences ofshort symbol sequences of length up to N . | convert the input word vectors into an output word vector for the predicted next word |
| cannot generalize across semantically related sequences of words | associate each word with a vector of real valued features |

![](https://ws1.sinaimg.cn/large/0067fcixly1ftiipk3p7oj31d30grwiz.jpg)

* left :  word representations learned for modelling language

  similar words or sequences of words are mapped to nearby representations.

* right : recurrent neural network

  each word and a function that predicts a target quantity such as the next word in a sequence (for language modelling) or a whole sequence of translated words

#### RNNS - machine translation and language model

​    RNNs have been found to be very good at predicting the next character in the text or the next word in a sequence

​    If a particular first word is chosen from this distribution and provided as input to the decoder network it will then output a probability distribution for the second word of the translation and so on until a full stop is chosen.

​    hidden units is a good representation of the thought expressed by the sentence.

​    Instead of translating the meaning of a French sentence into an English sentence, one can learn to ‘translate’ the meaning of an image into an English sentence.

![](https://ws1.sinaimg.cn/large/0067fcixly1ftiiup5wccj30ob09ztjf.jpg)

#### LSTM 

​    the natural behaviour of which is to remember inputs for a long time.

​    Memory networks can be trained to keep track of the state of the world in a setting similar to a text adventure game and after reading a story, they can answer questions that require complex inference.