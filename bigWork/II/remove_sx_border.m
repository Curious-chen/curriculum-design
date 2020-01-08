%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%Ŀ��:ȥ�����±߿��í����ͳ�����������
%%%%%%     í����������6���������䣨2��í��4��+���ұ߿�2�Σ�
%%%%%%     �ַ�����������16�����䣨7���ַ�����14��+���ұ߿�2��
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
function out = remove_sx_border(I)

% ǰһ�м���һ��,�����ò�ֵѰ�����䴦
diff_row = diff(I,1,2);  
% ͳ��ÿ�еĲ�ֵ�ͣ�����λ�У��ڴ�ֱ�����ϲ���
diff_row_sum = sum(abs(diff_row), 2); 
rows = size(I,1);

%%% ��λ�е���ʼλ��(��1/3������ɨ����)
trows = ceil(rows*(1/3));

j = trows;
for i=1:trows
    if diff_row_sum(j,1)<10
        plate.rowa = j;
        break;
    end
    % ����ɨ��
    j = trows-i;
end
 

%%% ��λ�еĽ���λ��(��2/3������ɨ����)
for i=2*trows:size(diff_row_sum,1)
    if diff_row_sum(i,1)<10
        plate.rowb = i;
        break;
    end
end
% �и�ͼ��ȥ��
out = I(plate.rowa:plate.rowb, :);
