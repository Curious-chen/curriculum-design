
clc;clear;
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% 1.Ԥ���� �ҶȻ�->��ת->��ֵ->ȥ����������
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
img = imread("../photo/I/��A00101.jpg");
subplot(331);imshow(img);title('ԭʼͼ��');
% �ҶȻ����� �õ�һ��ά�ȵ�ֵ���ɷ��������������
I = rgb2gray(img);
% ͼ��ת
I = 255- I;
subplot(332);imshow(I);title('�Ҷ�ͼ��');
I1 = imbinarize(I,0.62);
subplot(333);imshow(I1);title('��ֵͼ��');
% ȥ�������ڵ�
I2 = bwareaopen(I1,20);
subplot(334);imshow(I2);title('ȥ����������');

% 2.ȥ�����±߿��í����ͳ�����������
% I3=remove_extra_region(I2);
% subplot(335);imshow(I3);title('ȥ���������������');
I4 = remove_sx_border(I2);
subplot(336);imshow(I4);title('ȥ�����±߿��í��')

% 4.ȥ�����ұ߿�ͶӰ����
I5 = remove_zy_border(I4);
subplot(337);imshow(I5);title('ȥ�����ұ߿�');

% % 5.ȥ���ַ����ұ�����ͶӰ����
I6 = remove_zy_null(I5);
I6(:,size(I6,2):size(I6,2)+5) = 0;
subplot(338);imshow(I6);title('�ַ�����');


%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%% 6.�ָ��ַ�����ֱͶӰ����
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
[height, width] = size(I6);
Cwidth = width*46/409;  % ��һ�ַ����
Cspace = width*10/409;  % �ַ����
SecThspace = width*34/409;  % �ڶ����͵������ַ����
projection = sum(I6, 1);
subplot(339);stem(projection,'.',...
    'MarkerFaceColor','w',...
    'MarkerEdgeColor','w');
title('�ַ���ֱ����ͶӰ');


figure;
for i=1:7
    if i == 1
        k = uint8(floor(width - Cwidth)); % �л������һ���ַ���ʼ��
    else  % ������������ɨ��
        k = uint8(floor(k - Cwidth - Cspace)); % �л��ַ�����ʼ��
    end
    
    % �����������һ����
    if k <= 0
        k=1;
    end
    
    % ȡ��ǰ�ַ�
    fprintf("��%d�ַ���ʼ�еĴ��λ��:%d \n", i,k);
    fprintf("��ͶӰֵ:%d \n", projection(1, k));
    character = I6(:, k:ceil(k+Cwidth));
    subplot(178-i);imshow(character);
    % �ڶ����͵������ַ�֮��Ŀո����⴦��
    if i == 5
        k = k - SecThspace + Cspace;
    end
end

