% ������ĵ�һ��ͼƬ

% ��λ
function out = Location(img)
%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%% Ԥ����
%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% �ҶȻ�
grayimg = rgb2gray(img); 
% ��˹ģ��
H = fspecial('gaussian',5,3); 
blurred = imfilter(grayimg,H,'replicate'); 
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%% 2.��ֱ��Ե������̬ѧ����
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% ��ֱ��Ե���
bw = edge(blurred,'sobel','vertical'); 
se1 = strel('rectangle',[30,18]);
bw_close=imclose(bw,se1);
se2 = strel('rectangle',[21,19]);
bw_open = imopen(bw_close, se2);
% �Ƴ�С����
bw_close = bwareaopen(bw_open,1000);  
se3 = strel('rectangle',[25,17]);
bw_dilate = imdilate(bw_close,se3);
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%% 3.ȡ���ƺ�ѡ���򲢻��ڻ��������ȷ��λ����������
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
stats = regionprops(bw_dilate,'BoundingBox','Centroid');
index_area = area_judge(stats);

% ѡ����ɫ����ռ�ȴ���%70�ķ�������
index_color = color_judge(stats,img);
index_ratio = ratio_judge(stats);
index1 = intersect(index_area,index_color);
index = intersect(index1, index_ratio);

bb = stats(index).BoundingBox; 
I=img(floor(bb(2))+1:floor(bb(2)+bb(4)),floor(bb(1))+1:floor(bb(1)+bb(3)),:);
% subplot(339);imshow(I); title("����")
out = I;




