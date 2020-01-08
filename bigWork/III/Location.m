% 第三类的第一张图片

% 定位
function out = Location(img)
%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%% 预处理
%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% 灰度化
grayimg = rgb2gray(img); 
% 高斯模糊
H = fspecial('gaussian',5,3); 
blurred = imfilter(grayimg,H,'replicate'); 
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%% 2.垂直边缘检测和形态学处理
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% 垂直边缘检测
bw = edge(blurred,'sobel','vertical'); 
se1 = strel('rectangle',[30,18]);
bw_close=imclose(bw,se1);
se2 = strel('rectangle',[21,19]);
bw_open = imopen(bw_close, se2);
% 移除小对象
bw_close = bwareaopen(bw_open,1000);  
se3 = strel('rectangle',[25,17]);
bw_dilate = imdilate(bw_close,se3);
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%% 3.取车牌候选区域并基于混合特征精确定位出车牌区域
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
stats = regionprops(bw_dilate,'BoundingBox','Centroid');
index_area = area_judge(stats);

% 选择蓝色像素占比大于%70的方形区域
index_color = color_judge(stats,img);
index_ratio = ratio_judge(stats);
index1 = intersect(index_area,index_color);
index = intersect(index1, index_ratio);

bb = stats(index).BoundingBox; 
I=img(floor(bb(2))+1:floor(bb(2)+bb(4)),floor(bb(1))+1:floor(bb(1)+bb(3)),:);
% subplot(339);imshow(I); title("车牌")
out = I;




