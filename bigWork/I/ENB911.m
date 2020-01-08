
% figure()
I = imread('../photo/I/川A99999.jpg');
subplot(331);imshow(I);title("原图");


% 2 灰度化，旋转处理
I1 = rgb2gray(I);
subplot(332);imshow(I1);title("灰度图");

% 二值图像
I2 = imbinarize(I1,0.3);
subplot(333);imshow(I2);title("二值图像");

% 去除孤立噪声

I3 = bwareaopen(I2,35);
subplot(334);imshow(I3);title('未进行边框处理的二值图片');

% 去除边框
I4=remove_sx_border(I3);
% I4 = I4(4:size(I4,1),:);
I4=remove_extra_region(I4);
subplot(335);imshow(I4);title('去除上下边框');
I5 = remove_extra_region(I4);
I5 = remove_zy_null(I5);
I5 = I5(:,1:size(I5,2)-4);
subplot(336);imshow(I5);title('去除左右边框');

I6 = I5;
[height, width] = size(I6);
Cwidth = width*45/409;  % 单一字符宽度
Cspace = width*12/409;  % 字符间距
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

