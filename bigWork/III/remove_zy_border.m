%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%% ȥ�����ұ߿�ͶӰ����
%%%%%% ��λ�У�ɾ�����ұ߿�
%%%%%% �ж�Ԫ�غͣ��Ƿ�Ϊ0,Ϊ0��˵�������ޱ߿��
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

function out=remove_zy_border(I)
% ͳ��ÿһ�е�Ԫ��֮��,��ˮƽ������Ѱ��
plate_projection_v = sum(I,1);
% �ӵ�һ�п�ʼ�ң�ֱ����Ԫ�غ�Ϊ0�����Ǳ߿�
for i=1:size(plate_projection_v, 2)
    if plate_projection_v(1,i) == 0
        plate.cola = i;
        break;
    end
end
% �������ǰ�ң�ֱ����Ԫ�غ�Ϊ0�����Ǳ߿�
for i=1:size(plate_projection_v, 2)
    j = size(plate_projection_v, 2) - i + 1;
    if plate_projection_v(1,j) == 0
        plate.colb = j;
        break;
    end
end
out = I(:,plate.cola:plate.colb);