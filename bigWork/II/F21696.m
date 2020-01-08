% 第二类的第一张图片
clear;clc;
figure();
I = imread('../photo/II/晋F21696.jpg');
subplot(331);imshow(I);title("原图");


% 2 灰度化
I1 = rgb2gray(I);
subplot(332);imshow(I1);title("灰度图");

% % 滤波,进行中值滤波，消除噪音
% f = tofloat(I1);
% I1  = medfilt2(f,[2,2],'symmetric');
% subplot(333);imshow(I1);title("去除椒盐噪音");

% 二值图像
I2 = imbinarize(I1,0.5);
subplot(333);imshow(I2);title("二值图像");
% 去除孤立噪声

I3 = bwareaopen(I2,20);
subplot(334);imshow(I3);title('去除孤立噪声');


% 去除边框
I4=remove_sx_border(I3);
I4 = I4(1:size(I4,1),:);
I4=remove_extra_region(I4);
subplot(335);imshow(I4);title('去除上下边框');
I5 = remove_extra_region(I4);
I5 = I5(:,2:size(I5,2)-2);
I5 = remove_zy_null(I5);

subplot(336);imshow(I5);title('去除左右边框');
% 垂直投影并分割
I6 = I5;
[height, width] = size(I6);
projection = sum(I6, 1);
subplot(339);stem(projection,'.',...
    'MarkerFaceColor','w',...
    'MarkerEdgeColor','w');
title('字符垂直方向投影');

figure();
subplot(1,7,1);imshow(I6(:,1:16));
subplot(1,7,2);imshow(I6(:,16:31));
subplot(1,7,3);imshow(I6(:,44:59));
subplot(1,7,4);imshow(I6(:,63:78));
subplot(1,7,5);imshow(I6(:,82:97));
subplot(1,7,6);imshow(I6(:,97:112));
subplot(1,7,7);imshow(I6(:,115:width));