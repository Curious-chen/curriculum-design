
clc;clear;
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% 1.预处理 灰度化->反转->二值->去除孤立噪音
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
img = imread("../photo/I/军A00101.jpg");
subplot(331);imshow(img);title('原始图像');
% 灰度化处理 得到一个维度的值即可分析出总体的特征
I = rgb2gray(img);
% 图像反转
I = 255- I;
subplot(332);imshow(I);title('灰度图像');
I1 = imbinarize(I,0.62);
subplot(333);imshow(I1);title('二值图像');
% 去除孤立节点
I2 = bwareaopen(I1,20);
subplot(334);imshow(I2);title('去除孤立噪声');

% 2.去掉上下边框和铆钉（统计跳变次数）
% I3=remove_extra_region(I2);
% subplot(335);imshow(I3);title('去除车牌以外的区域');
I4 = remove_sx_border(I2);
subplot(336);imshow(I4);title('去除上下边框和铆钉')

% 4.去除左右边框（投影法）
I5 = remove_zy_border(I4);
subplot(337);imshow(I5);title('去除左右边框');

% % 5.去除字符左右背景（投影法）
I6 = remove_zy_null(I5);
I6(:,size(I6,2):size(I6,2)+5) = 0;
subplot(338);imshow(I6);title('字符车牌');


%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%% 6.分割字符（垂直投影法）
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
[height, width] = size(I6);
Cwidth = width*46/409;  % 单一字符宽度
Cspace = width*10/409;  % 字符间距
SecThspace = width*34/409;  % 第二个和第三个字符间距
projection = sum(I6, 1);
subplot(339);stem(projection,'.',...
    'MarkerFaceColor','w',...
    'MarkerEdgeColor','w');
title('字符垂直方向投影');


figure;
for i=1:7
    if i == 1
        k = uint8(floor(width - Cwidth)); % 切换到最后一个字符起始列
    else  % 自右向左逐列扫描
        k = uint8(floor(k - Cwidth - Cspace)); % 切换字符的起始列
    end
    
    % 对特殊情况置一处理
    if k <= 0
        k=1;
    end
    
    % 取当前字符
    fprintf("第%d字符起始列的大概位置:%d \n", i,k);
    fprintf("列投影值:%d \n", projection(1, k));
    character = I6(:, k:ceil(k+Cwidth));
    subplot(178-i);imshow(character);
    % 第二个和第三个字符之间的空格特殊处理
    if i == 5
        k = k - SecThspace + Cspace;
    end
end

