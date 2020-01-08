"""
    flask 接口
"""
from flask_cors import CORS
from PIL import Image

from flask import Flask, request, send_file, url_for
from Mytools.log import logger
from Mytools.sort import heapSort
from Search.handle import use_model
import json
import joblib
from redis import StrictRedis

import os

os.environ["CUDA_VISIBLE_DEVICES"] = "-1"
import tensorflow as tf
import numpy as np

# 定义静态资源文件夹路径
app = Flask(__name__, static_folder='h:/static')

# # 加载模型
pca = joblib.load('h:/static/model/pca.model')

# 加载redis数据
sr = StrictRedis()

##############
### 定义cnn网络
##############
model_path = '../classification/model/image_model'

# 定义Placeholder，存放输入和标签
datas_placeholder = tf.placeholder(tf.float32, [None, 32, 32, 3])

# 存放DropOut参数的容器，训练时为0.25，测试时为0
dropout_placeholdr = tf.placeholder(tf.float32)

# 定义卷积层, 20个卷积核, 卷积核大小为5，用Relu激活
conv0 = tf.layers.conv2d(datas_placeholder, 20, 5, activation=tf.nn.relu)
# 定义max-pooling层，pooling窗口为2x2，步长为2x2
pool0 = tf.layers.max_pooling2d(conv0, [2, 2], [2, 2])

# 定义卷积层, 40个卷积核, 卷积核大小为4，用Relu激活
conv1 = tf.layers.conv2d(pool0, 40, 4, activation=tf.nn.relu)
# 定义max-pooling层，pooling窗口为2x2，步长为2x2
pool1 = tf.layers.max_pooling2d(conv1, [2, 2], [2, 2])

# 将3维特征转换为1维向量
flatten = tf.layers.flatten(pool1)

# 全连接层，转换为长度为100的特征向量
fc = tf.layers.dense(flatten, 400, activation=tf.nn.relu)

# 加上DropOut，防止过拟合
dropout_fc = tf.layers.dropout(fc, dropout_placeholdr)

# 未激活的输出层
logits = tf.layers.dense(dropout_fc, 133)

predicted_labels = tf.arg_max(logits, 1)

sess = tf.Session()
# 如果是测试，载入参数
# 用于保存和载入模型
saver = tf.train.Saver()
saver.restore(sess, model_path)
logger.info("从{}载入模型".format(model_path))


# 自动跳转到静态上传网页
@app.route('/')
def hello_world():
    return send_file('h:/static/update.html')


@app.route('/getPhoto/', methods=['POST', 'GET'])
def get_photo():
    # print(request.headers)
    img = request.files.get('file', None)
    if img:
        im = Image.open(img)
        msg = "{}   {}  {}".format(im.size, im.format, im.mode)
        logger.info(msg)
        data = np.array(im.resize((32, 32))) / 255.0
        datas = np.array([data])
        # 定义输入和Label以填充容器，测试时dropout为0
        test_feed_dict = {
            datas_placeholder: datas,
            dropout_placeholdr: 0
        }
        predicted_index = [(i, v) for i, v in enumerate(sess.run(logits, feed_dict=test_feed_dict)[0])]
        three_index = heapSort(predicted_index, key=lambda x: x[-1], count_num=10)
        labels = [(sr.lindex('cnn_mapping', int(_[0])).decode('utf-8'), _[1]) for _ in three_index if _[1] > 5]
        logger.info("可能的种类:{}".format(labels))
        if not labels:
            return ''
        # 读取图片以及索引
        res = list()
        mapping = list()
        key_score = list()
        max_score = 0
        for label in labels:
            key, score = label
            if max_score < score:
                max_score = max_score
            photos = sr.lrange(key, 0, -1)
            res.extend(photos)
            key_score.extend(score for _ in range(len(photos)))
            mapping.extend(sr.lrange('{}_index'.format(key), 0, -1))
        # 计算pca相似度
        result = []
        for v in use_model(im, pca, res, mapping, key_score, max_score):
            paths, kind_score, cos_score = v
            path = url_for('static', filename='baiduPhoto/{}/{}'.format(*paths))
            logger.info(paths)
            result.append({'kind_name': paths[0], 'url': path, 'kind_score': kind_score, 'cos_score': cos_score})
        return json.dumps(result, ensure_ascii=False)
    return ''


@app.route('/getHtml/', methods=['get', 'post'])
def get_html():
    return 'context'


if __name__ == '__main__':
    CORS(app, supports_credentials=True)
    app.run(host='0.0.0.0')
