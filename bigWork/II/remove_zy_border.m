%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%% 去除左右边框（投影法）
%%%%%% 定位列，删除左右边框
%%%%%% 判断元素和，是否为0,为0则说明此列无边框点
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

function out=remove_zy_border(I)
% 统计每一列的元素之和,即水平方向上寻找
plate_projection_v = sum(I,1);
% 从第一列开始找，直到列元素和为0，即非边框处
for i=1:size(plate_projection_v, 2)
    if plate_projection_v(1,i) == 0
        plate.cola = i;
        break;
    end
end
% 从最后往前找，直到列元素和为0，即非边框处
for i=1:size(plate_projection_v, 2)
    j = size(plate_projection_v, 2) - i + 1;
    if plate_projection_v(1,j) == 0
        plate.colb = j;
        break;
    end
end
out = I(:,plate.cola:plate.colb);