```python
def piptrack(y=None, sr=22050, S=None, n_fft=2048, hop_length=None,
             fmin=150.0, fmax=4000.0, threshold=0.1):
	# Check that we received an audio time series or STFT
    # 得出窗的步长
    if hop_length is None:
        hop_length = int(n_fft // 4)
	# 获得频谱图
    S, n_fft = _spectrogram(y=y, S=S, n_fft=n_fft, hop_length=hop_length)

    # Make sure we're dealing with magnitudes
    # 频谱取绝对值，保证研究的是大小
    S = np.abs(S)

    # Truncate to feasible region
    # 划定有效区域，默认是 0 ~ frq/2 ， 因为前半和后半是对称的
    fmin = np.maximum(fmin, 0)
    fmax = np.minimum(fmax, float(sr) / 2)
	
    # 取出每个窗的首地址
    fft_freqs = time_frequency.fft_frequencies(sr=sr, n_fft=n_fft)
	
    # 频域插值是为了保证时域的精度
    # Do the parabolic interpolation everywhere,
    # then figure out where the peaks are
    # then restrict to the feasible range (fmin:fmax)
    # 每个值与前面第二个值的差，除以2可能是因为相差了2个位置
    avg = 0.5 * (S[2:] - S[:-2])
	# 每个值分别减去前后的值（计算峰值）
    shift = 2 * S[1:-1] - S[2:] - S[:-2]

    # Suppress divide-by-zeros.
    # Points where shift == 0 will never be selected by localmax anyway
    # tiny方法是计算输入类型的非0最小正数（就是这个类型能放的最最最最小的值），防止除0
    # shift等于  每个值与前面第二个值的差 除以 每个值与相邻两个值差之和
    shift = avg / (shift + (np.abs(shift) < util.tiny(shift)))
	
    #补全
    shift = np.pad(shift, ([1, 1], [0, 0]), mode='constant')

    # Pre-allocate output
    pitches = np.zeros_like(S)

    # Clip to the viable frequency range
    # 确保坐标在范围内，并且将坐标转化为bool值，shape为[n_fft//2,1]
    freq_mask = ((fmin <= fft_freqs) & (fft_freqs < fmax)).reshape((-1, 1))

    # Compute the column-wise local max of S after thresholding
    # Find the argmax coordinates
    # 保留大于threshold作用后每一列的最大值（同阶的最大值）的值
    # np.argwhere 直接拿出选出的点所对应的坐标，fmask是用于限定范围的，防止越界，里面基本都是true
    idx = np.argwhere(freq_mask &
                      util.localmax(S * (S > (threshold * S.max(axis=0)))))

    # Store pitch and magnitude
    # numpy 点索引， 逗号左边为x坐标集，右边为y坐标集
    # 只有横轴也就是帧方向的坐标才需要插值
    pitches[idx[:, 0], idx[:, 1]] = ((idx[:, 0] + shift[idx[:, 0], idx[:, 1]])
                                     * float(sr) / n_fft)
	# 相当于是返回了所有满足大于threshold*该阶最大值的点的帧的位置加上插值量
    # 最终的Pitches shape 为 [fft深度,n_frame]
   	return pitches


def extract_max(pitches, magnitudes, shape):
    new_pitches = []
    new_magnitudes = []
    for i in range(0, shape[1]):
        new_pitches.append(numpy.max(pitches[:, i]))
        new_magnitudes.append(numpy.max(magnitudes[:, i]))
    return (new_pitches, new_magnitudes)

def smooth(x, window_len=11, window='hanning'):
    if window_len < 3:
        return x
    if not window in ['flat', 'hanning', 'hamming', 'bartlett', 'blackman']:
        raise ValueError("Window is on of 'flat', 'hanning', 'hamming', 'bartlett', 'blackman'")
    #从window_len-1开始往前遍历
    s = numpy.r_[2 * x[0] - x[window_len - 1::-1], x, 2 * x[-1] - x[-1:-window_len:-1]]
    if window == 'flat':  # moving average
        w = numpy.ones(window_len, 'd')
    else:
        w = eval('numpy.' + window + '(window_len)')
    y = numpy.convolve(w / w.sum(), s, mode='same')
    return y[window_len:-window_len + 1]
```

