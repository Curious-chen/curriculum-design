%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%% 使用投影法移除额外区域
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

function I=remove_extra_region(I2)

% 统计每列的元素和，能定位列，即在水平方向上删除孤立点
projection_h = sum(I2,1);

% 统计每行的元素和，能定位行，即在垂直方向上删除孤立点
projection_v = sum(I2,2);

% 垂直方向上往下找，
for i=1:size(projection_v,1)
    if projection_v(i,1) >= 1
        new.rowa = i;
        break;
    end
end
 
% 垂直方向下往上找，
for i=1:size(projection_v,1)
    j = size(projection_v,1) - i+1;
    if projection_v(j,1) >= 1
        new.rowb = j;
        break;
    end
end
 
% 水平方向上，从左往右找
for i=1:size(projection_h ,2)
    if projection_h(1,i) >= 1
        new.cola = i;
        break;
    end
end
% 水平方向上，从右往左找
for i=1:size(projection_h ,2)
    j = size(projection_h ,2)-i+1;
    if projection_h(1,j) >= 1
        new.colb = j;
        break;
    end
end
I = I2(new.rowa:new.rowb, new.cola:new.colb);
end