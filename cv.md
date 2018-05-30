###简单的人脸识别

```python
import cv2
import sklearn.svm as svm
def detect(image ,cascade):
    rects = cascade.detectMultiScale(image,scaleFactor=1.3,
                                     minNeighbors=5, minSize=(30, 30), flags = cv2.CASCADE_SCALE_IMAGE)
    if len(rects) == 0:
        return []
    rects[:, 2:] += rects[:, :2]
    print(rects)
    return rects

def draw_rects(img, rects, color):
    for x1, y1, x2, y2 in rects:
        cv2.rectangle(img, (x1, y1), (x2, y2), color, 2)

capture = cv2.VideoCapture(0)
size = (int(capture.get(cv2.CAP_PROP_FRAME_WIDTH)), int(capture.get(cv2.CAP_PROP_FRAME_HEIGHT)))
video = cv2.VideoWriter("VideoTest.avi", cv2.CAP_PROP_FOURCC, 30, size)

print(capture.isOpened())

num = 0

while True:
    ret, img = capture.read()
    video.write(img)
    #cv2.imshow('vedio', img)

    #cv2.imwrite('%s.jpg' % (str(num)), img)
    # 转换为灰度图
    gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
    # 直方图均衡处理
    gray = cv2.equalizeHist(gray)

    # 脸部特征分类地址，里面还有其他E:\\face_detect\\haarcascade_frontalface_default.xml  ，haarcascade_frontalface_alt.xml
    cascade_fn = 'E:/opencv/opencv/sources/data/haarcascades/haarcascade_frontalface_alt.xml'

    # 读取分类器,CascadeClassifier下面有一个detectMultiScale方法来得到矩形
    cascade = cv2.CascadeClassifier(cascade_fn)

    # 通过分类器得到rects
    rects = detect(gray, cascade)

    # vis为img副本
    vis = img.copy()

    # 画矩形
    draw_rects(vis, rects, (0, 255, 0))

    cv2.imshow('facedetect', vis)

    #cv2.waitKey(0)
    key = cv2.waitKey(1)
    #cv2.destroyAllWindows()
    num = num + 1
    if key == ord('q'):
        break
#
video.release()
capture.release()
cv2.destroyAllWindows()

```
