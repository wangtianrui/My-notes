from google.colab import files

uploaded = files.upload()





!ls





```
from google.colab import files
import os

dir = os.walk("log2")
names = []
for i , p , f in dir:
    for t in f:
      names.append(t)
      
      
for i in names:
    files.download(i)
```

