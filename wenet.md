# 这篇文章主要介绍Wenet的脚本模块干了些啥（自己过一遍）

## run.sh

主脚本。

```shell
. ./path.sh || exit 1; #导包
```

```shell
export CUDA_VISIBLE_DEVICES="0,1,2,3,4,5,6,7" #GPU选择
export NCCL_DEBUG=INFO #nccl配置
```

```shell
stage=0  # 后面一共有6个步骤
stop_stage=6

num_nodes=1
node_rank=0
```

```shell
data=/export/data/asr-data/OpenSLR/33/ # 数据存放位置
data_url=www.openslr.org/resources/33 # 下载位置

nj=16  # 线程数
feat_dir=raw_wav # 处理后的特征是原始语音（不做处理）
dict=data/dict/lang_char.txt #dict存放位置
```

```shell
train_set=train  # 指定训练集的目录名
# Optional train_config
# 1. conf/train_transformer.yaml: Standard transformer
# 2. conf/train_conformer.yaml: Standard conformer
# 3. conf/train_unified_conformer.yaml: Unified dynamic chunk causal conformer
# 4. conf/train_unified_transformer.yaml: Unified dynamic chunk transformer
train_config=conf/train_conformer.yaml # 选择网络配置
cmvn=true # 是否做中心均值归一化？
dir=exp/conformer # 结果存放位置
checkpoint=   

# use average_checkpoint will get better result
average_checkpoint=true # 是否启用参数均值化
decode_checkpoint=$dir/final.pt 
average_num=30
decode_modes="ctc_greedy_search ctc_prefix_beam_search attention attention_rescoring" # decode的模式
```

```shell
. tools/parse_options.sh || exit 1;  # 检查输入的参数是不是对的
```

```shell
if [ ${stage} -le -1 ] && [ ${stop_stage} -ge -1 ]; then    #如果没有数据，就下载。
    echo "stage -1: Data Download"
    local/download_and_untar.sh ${data} ${data_url} data_aishell
    local/download_and_untar.sh ${data} ${data_url} resource_aishell
fi

if [ ${stage} -le 0 ] && [ ${stop_stage} -ge 0 ]; then # 开始准备数据
    # Data preparation
    local/aishell_data_prep.sh ${data}/data_aishell/wav ${data}/data_aishell/transcript
fi
```

