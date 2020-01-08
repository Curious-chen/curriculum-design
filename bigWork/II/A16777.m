% 第二类的第一张图片
clear;clc;
figure();

% 第一类的第一张图片
clear;clc;

I = imread('../photo/II/蒙A16777.jpg');
subplot(331);imshow(I);title("原图");


% 2 灰度化
I1 = I(:,:,1)*0.299+I(:,:,2)*0.587+I(:,:,3)*0.11;
I1 = 255 -I1;
subplot(332);imshow(I1);title("灰度图");

% 二值图像
I2 = imbinarize(I1,0.6);
subplot(333);imshow(I2);title("二值图像");

% 去除孤立噪声

I3 = bwareaopen(I2,100);
subplot(334);imshow(I3);title('去除孤立噪声');

% 
% 去除边框
I4=remove_sx_border(I3);
% I4 = I4(4:size(I4,1),:);
I4=remove_extra_region(I4);
subplot(335);imshow(I4);title('去除上下边框');
I5 = remove_extra_region(I4);
I5 = remove_zy_null(I5);
I5 = I5(:,1:size(I5,2)-4);
subplot(336);imshow(I5);title('去除左右边框');

% 画出投影并分割
I6 = I5;
[height, width] = size(I6);
projection = sum(I6, 1);
subplot(339);stem(projection,'.',...
    'MarkerFaceColor','w',...
    'MarkerEdgeColor','w');
title('字符垂直方向投影');

figure();
subplot(1,7,1);imshow(I6(:,1:28));
subplot(1,7,2);imshow(I6(:,28:55));
subplot(1,7,3);imshow(I6(:,75:102));
subplot(1,7,4);imshow(I6(:,102:129));
subplot(1,7,5);imshow(I6(:,134:161));
subplot(1,7,6);imshow(I6(:,164:191));
subplot(1,7,7);imshow(I6(:,191:width));

