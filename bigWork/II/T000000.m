% �ڶ���ĵ�һ��ͼƬ
clear;clc;
I = imread('../photo/II/³A88888.jpg');
subplot(331);imshow(I);title("ԭͼ");


% 2 �ҶȻ�
I1 = rgb2gray(I);
subplot(332);imshow(I1);title("�Ҷ�ͼ");


% %  ��
I1 = imadjust(I1,[],[],0.5); % ٤��任
% I1 = histeq(I1); % ���⻯
subplot(337);imhist(I1);title("��ֵͼ��");
subplot(338);imshow(I1);title("��ֵͼ��");

subplot(338);imshow(I1);title("��ֵͼ��");

edge('')
% ��ֵͼ��
I2 = imbinarize(I1,0.64);
subplot(333);imshow(I2);title("��ֵͼ��");

% ȥ����������

I3 = bwareaopen(I2,100);
subplot(334);imshow(I3);title('ȥ����������');
% ȥ���߿�
I4=remove_sx_border(I3);
% I4 = I4(4:size(I4,1),:);
I4=remove_extra_region(I4);
subplot(335);imshow(I4);title('ȥ�����±߿�');
I5 = remove_extra_region(I4);
I5 = remove_zy_null(I5);
I5 = I5(:,1:size(I5,2)-4);
subplot(336);imshow(I5);title('ȥ�����ұ߿�');

I6 = I5;
[height, width] = size(I6);
projection = sum(I6, 1);
subplot(339);stem(projection,'.',...
    'MarkerFaceColor','w',...
    'MarkerEdgeColor','w');
title('�ַ���ֱ����ͶӰ');

% figure();
% subplot(1,7,1);imshow(I6(:,1:28));
% subplot(1,7,2);imshow(I6(:,28:55));
% subplot(1,7,3);imshow(I6(:,75:102));
% subplot(1,7,4);imshow(I6(:,102:129));
% subplot(1,7,5);imshow(I6(:,134:161));
% subplot(1,7,6);imshow(I6(:,164:191));
% subplot(1,7,7);imshow(I6(:,191:width));

