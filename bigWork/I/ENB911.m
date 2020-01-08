
% figure()
I = imread('../photo/I/��A99999.jpg');
subplot(331);imshow(I);title("ԭͼ");


% 2 �ҶȻ�����ת����
I1 = rgb2gray(I);
subplot(332);imshow(I1);title("�Ҷ�ͼ");

% ��ֵͼ��
I2 = imbinarize(I1,0.3);
subplot(333);imshow(I2);title("��ֵͼ��");

% ȥ����������

I3 = bwareaopen(I2,35);
subplot(334);imshow(I3);title('δ���б߿���Ķ�ֵͼƬ');

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
Cwidth = width*45/409;  % ��һ�ַ����
Cspace = width*12/409;  % �ַ����
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

