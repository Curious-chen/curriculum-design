% �ڶ���ĵ�һ��ͼƬ
clear;clc;
figure();
I = imread('../photo/II/��F21696.jpg');
subplot(331);imshow(I);title("ԭͼ");


% 2 �ҶȻ�
I1 = rgb2gray(I);
subplot(332);imshow(I1);title("�Ҷ�ͼ");

% % �˲�,������ֵ�˲�����������
% f = tofloat(I1);
% I1  = medfilt2(f,[2,2],'symmetric');
% subplot(333);imshow(I1);title("ȥ����������");

% ��ֵͼ��
I2 = imbinarize(I1,0.5);
subplot(333);imshow(I2);title("��ֵͼ��");
% ȥ����������

I3 = bwareaopen(I2,20);
subplot(334);imshow(I3);title('ȥ����������');


% ȥ���߿�
I4=remove_sx_border(I3);
I4 = I4(1:size(I4,1),:);
I4=remove_extra_region(I4);
subplot(335);imshow(I4);title('ȥ�����±߿�');
I5 = remove_extra_region(I4);
I5 = I5(:,2:size(I5,2)-2);
I5 = remove_zy_null(I5);

subplot(336);imshow(I5);title('ȥ�����ұ߿�');
% ��ֱͶӰ���ָ�
I6 = I5;
[height, width] = size(I6);
projection = sum(I6, 1);
subplot(339);stem(projection,'.',...
    'MarkerFaceColor','w',...
    'MarkerEdgeColor','w');
title('�ַ���ֱ����ͶӰ');

figure();
subplot(1,7,1);imshow(I6(:,1:16));
subplot(1,7,2);imshow(I6(:,16:31));
subplot(1,7,3);imshow(I6(:,44:59));
subplot(1,7,4);imshow(I6(:,63:78));
subplot(1,7,5);imshow(I6(:,82:97));
subplot(1,7,6);imshow(I6(:,97:112));
subplot(1,7,7);imshow(I6(:,115:width));