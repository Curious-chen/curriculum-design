from matplotlib import pyplot as plt
import numpy as np
from PIL import Image
import os

from redis import StrictRedis

from Mytools.log import logger

from sklearn.decomposition import PCA

import joblib

from Mytools.sort import heapSort

import tensorflow as tf


# 直方图化
def histeq(im, nbr_bins=256):
    """对一幅灰度图像进行直方图均衡化"""
    im = np.array(im)
    # 计算图像的直方图
    # 在numpy中，也提供了一个计算直方图的函数histogram(),第一个返回的是直方图的统计量，第二个为每个bins的中间值
    imhist, bins = np.histogram(im.flatten(), nbr_bins)
    cdf = imhist.cumsum()  #
    cdf = 255.0 * cdf / cdf[-1]
    # 使用累积分布函数的线性插值，计算新的像素值
    im2 = np.interp(im.flatten(), bins[:-1], cdf)
    return im2.reshape(im.shape)


# 预处理 灰度直方图化
def pre_deal(im, size=(64, 64)):
    # 修改图片大小
    im = im.resize(size)
    # 灰度化
    # im = im.convert('L')
    data = np.array(im).astype(np.float64)
    # histeq(data)
    # # 灰度化，忽略颜色
    # # 分别对三个通道（r,g,b）做直方图均衡化
    data[:, :, 0] = histeq(data[:, :, 0])
    data[:, :, 1] = histeq(data[:, :, 1])
    data[:, :, 2] = histeq(data[:, :, 2])
    return data.flatten()


# 读取图片地址
def readPhotos(dir_path='h:/photo', count=-1):
    if os.path.exists(dir_path):
        droot = os.listdir(dir_path)
        count = count if count != -1 else len(droot)
        for d_name in droot:
            d_path = os.path.join(dir_path, d_name)
            d = os.listdir(d_path)
            for file_name in d[:count]:
                file = os.path.join(d_path, file_name)
                yield d_name, file

    else:
        logger.info(f'目录{dir_path}:不存在')


# 处理，并将结果放入redis
def getData(dir_path='h:/static/photo', train_len=6, size=(64, 64)):
    sr = StrictRedis()
    # 清除
    sr.delete('deal_photos', 'map')
    count = 1
    for v in readPhotos(dir_path, train_len):
        d_name, file = v
        try:
            im = Image.open(file, 'r')
            # 预处理
            data = pre_deal(im, size)
            sr.rpush('deal_photos', data.tostring())
            name = os.path.basename(file)
            sr.rpush('map', os.path.join(d_name, name))
        except Exception as e:
            logger.warning("file:{}    error:{}".format(file, e))
        logger.info("成功处理:{:0>5d}-{}-{}-{}".format(count, d_name, data.shape, data.dtype))
        count += 1


# 读取redis,并使用pca对图片降维
def final_deal():
    # 获得图片矩阵
    sr = StrictRedis()
    res = np.array(list(np.fromstring(i, dtype=np.float64) for i in sr.lrange('deal_photos', 0, -1)))
    logger.info('训练矩阵:{}'.format(res.shape))
    # # pca降维
    pca = PCA(n_components=0.9)
    newX = pca.fit_transform(res)

    sr.delete('final_photos')
    for v in newX:
        sr.rpush('final_photos', v.tostring())
    logger.info("所占特征百分比:{}".format(np.sum(pca.explained_variance_ratio_)))
    logger.info("特征矩阵大小:{}".format(pca.components_.shape))

    path = 'H:/static/model'
    if not os.path.exists(path):
        os.mkdir(path)
    # 保存pca模型
    joblib.dump(pca, os.path.join(path, 'pca.model'))


# 再次处理
def deal_again(start=0, end=-1):
    sr = StrictRedis()
    if start == 0:
        sr.delete('final_photos')
    res = np.array(list(np.fromstring(i, dtype=np.float64) for i in sr.lrange('deal_photos', start, end)))
    logger.info('训练矩阵:{}'.format(res.shape))
    pca = joblib.load('h:/static/model/pca.model')
    newX = pca.transform(res)
    for v in newX:
        sr.rpush('final_photos', v.tostring())

    logger.info("{}》》》{}成功".format(res.shape, newX.shape))


# 接口,获得范围表
def get_range():
    sr = StrictRedis()
    res_photos = sr.lrange('final_photos', 0, -1)

    res_map = sr.lrange('map', 0, -1)

    for p, m in zip(res_photos, res_map):
        path = m.decode('utf-8')
        key = os.path.split(path)[0]
        sr.rpush(key, p)
        sr.rpush('{}_index'.format(key), path)
        logger.info('处理完成》》》{}'.format(path))


# def getTrain():
#     # 获得降维后的图片矩阵
#     sr = StrictRedis()
#     res = np.array(list(np.fromstring(i, dtype=np.float64) for i in sr.lrange('final_photos', 0, -1)))
#     logger.info('训练矩阵:{}'.format(res.shape))
#
#     # 获得映射表
#     sr_mapping = sr.lrange('map', 0, -1)
#     mapping = list()
#     target = list()
#     for v in sr_mapping:
#         name = os.path.split(v.decode('utf-8'))[0]
#         if name not in mapping:
#             mapping.append(name)
#         tar = mapping.index(name)
#         target.append(tar)
#     logger.info('映射表:{}'.format(mapping))
#     logger.info("标签:  {}".format(target))
#
#     # 获得训练集
#     x_index = list()
#     label = list()
#
#     for i, k in enumerate(mapping):
#         start = target.index(i)
#         # 取前20张图片
#         for t in range(start, start + 30):
#             # 图片行号
#             x_index.append(t)
#             # 种类编号
#             label.append(i)
#
#     X = np.array(res[x_index])
#     # 打乱
#     from sklearn.model_selection import train_test_split
#     x_train, x_test, y_train, y_test = train_test_split(X, label, test_size=0.3, random_state=42)
#     return x_train, x_test, y_train, y_test
#
#
# # 逻辑回归
# def flowerFind():
#     train_x, test_x, train_y, test_y = getTrain()
#     logger.info('train_x:{}'.format(train_x.shape))
#     logger.info(train_y)
#     # # 逻辑回归预测
#     from sklearn.linear_model import LogisticRegression
#     # model = LogisticRegression()
#     # model.fit(train_x, train_y)
#     # # 保存模型
#     # joblib.dump(model, 'lr.model')
#     model = joblib.load('lr.model')
#     # 计算精确度
#     accuray = model.score(test_x, test_y)
#     logger.info("accuray:{}".format(accuray))
#
#
# # catboost
# def catboost_model():
#     train_x, test_x, train_y, test_y = getTrain()
#
#     from catboost import CatBoostClassifier
#
#     model = CatBoostClassifier(iterations=100, loss_function='MultiClass',task_type='GPU')
#
#     model.load_model()
#     model.fit(train_x, train_y)
#
#
# def use_LR_model(predict):
#     LR = joblib.load('lr.model')
#     predict_people = LR.predict(predict)


from Mytools.math import cosine, euc_distance


# 使用pca模型比较
def use_model(im, pca=None, res=None, mapping=None, key_score=list(), max_score=27, maxlen=20):
    # 预处理
    data = pre_deal(im, size=(64, 64))
    # 转换
    data = pca.transform(np.array([data]))[0]
    result = list()
    for i, v in enumerate(res):
        # 转化为num数组
        v = np.fromstring(v, dtype=np.float64)
        # 计算余弦相似度
        cos = cosine(data, v)
        # score = key_score[i] + max_score * cos
        result.append((i, key_score[i], cos))
    photo_result = [[os.path.split(mapping[r[0]].decode('utf-8')), '{:.4f}'.format(r[1]), '{:.4f}'.format(r[-1])] for r in
                    heapSort(result, lambda x: x[-1], maxlen)]
    return photo_result


# 使用cnn模型选择类别


def getCata(dirpath='H:/static/photo'):
    cata = os.listdir(dirpath)
    sr = StrictRedis()
    sr.sadd('category', *cata)


def get_pcaModel():
    getData('h:/static/baiduPhoto', 20)
    final_deal()


def get_all_pcsR():
    getData('h:/static/baiduPhoto', -1)
    deal_again(0, 2000)
    deal_again(2001, 4000)
    deal_again(4001, 6000)
    deal_again(6001, 8000)
    deal_again(8001, -1)


if __name__ == '__main__':
    get_all_pcsR()
    # getData('h:/static/baiduPhoto', 20)
    # deal_again(0, 5000)
    # deal_again(5001, -1)
    # t = use_model(Image.open('h:/static/baiduPhoto\\散尾葵\\0001.jpg'), maxlen=10)
    # for i in t:
    #     print(i)
    # is_sure()
    # get_all_pcsR()
    # flowerFind()
    # catboost_model()
    get_range()
    pass
