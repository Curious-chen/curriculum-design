% ��һ����

% ��һ��ĵ�һ��ͼƬ
clear;clc;
I = imread('../photo/I/KW507.jpg');
subplot(331);imshow(I);title("ԭͼ");

% 2 �ҶȻ�����ת����
I1 = rgb2gray(I);
subplot(332);imshow(I1);title("�Ҷ�ͼ");

% ��ֵͼ��
I2 = imbinarize(I1,0.45);
subplot(333);imshow(I2);title("��ֵͼ��");

% ȥ����������

I3 = bwareaopen(I2,500);
subplot(334);imshow(I3);title('ȥ����������');

% ȥ���߿�
I4=remove_sx_border(I3);
subplot(335);imshow(I4);title('ȥ�����±߿�');
I5 = I4(:,200:size(I4,2)-100);
I5 = remove_zy_null(I5);
subplot(336);imshow(I5);title('ȥ�����ұ߿�');

% �ָ�ͼ��
I6 = I5;
[height, width] = size(I6);
Cwidth = width*45/250;  % ��һ�ַ����
Cspace = width*12/250;  % �ַ����
SecThspace = width*34/250;  % �ڶ����͵������ַ����
projection = sum(I6, 1);
subplot(339);stem(projection,'.',...
    'MarkerFaceColor','w',...
    'MarkerEdgeColor','w');
title('�ַ���ֱ����ͶӰ');
figure();
subplot(1,6,1);imshow(I6(:,1:360));
subplot(1,6,2);imshow(I6(:,360:760));
subplot(1,6,3);imshow(I6(:,1000:1400));
subplot(1,6,4);imshow(I6(:,1400:1760));
subplot(1,6,5);imshow(I6(:,1760:width));



