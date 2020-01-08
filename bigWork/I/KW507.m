% 第一步：

% 第一类的第一张图片
clear;clc;
I = imread('../photo/I/KW507.jpg');
subplot(331);imshow(I);title("原图");

% 2 灰度化，旋转处理
I1 = rgb2gray(I);
subplot(332);imshow(I1);title("灰度图");

% 二值图像
I2 = imbinarize(I1,0.45);
subplot(333);imshow(I2);title("二值图像");

% 去除孤立噪声

I3 = bwareaopen(I2,500);
subplot(334);imshow(I3);title('去除孤立噪声');

% 去除边框
I4=remove_sx_border(I3);
subplot(335);imshow(I4);title('去除上下边框');
I5 = I4(:,200:size(I4,2)-100);
I5 = remove_zy_null(I5);
subplot(336);imshow(I5);title('去除左右边框');

% 分割图像
I6 = I5;
[height, width] = size(I6);
Cwidth = width*45/250;  % 单一字符宽度
Cspace = width*12/250;  % 字符间距
SecThspace = width*34/250;  % 第二个和第三个字符间距
projection = sum(I6, 1);
subplot(339);stem(projection,'.',...
    'MarkerFaceColor','w',...
    'MarkerEdgeColor','w');
title('字符垂直方向投影');
figure();
subplot(1,6,1);imshow(I6(:,1:360));
subplot(1,6,2);imshow(I6(:,360:760));
subplot(1,6,3);imshow(I6(:,1000:1400));
subplot(1,6,4);imshow(I6(:,1400:1760));
subplot(1,6,5);imshow(I6(:,1760:width));



