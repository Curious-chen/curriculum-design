%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%% 去除字符左右背景（投影法）
%%%%%% 保证边框去除的情况下，可以通过找左右两边的字符边界来去除左右两边的空白
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
function out = remove_zy_null(I)

% 统计每一列的元素之和,即水平方向上寻找
ppv1 = sum(I,1);
columns = size(ppv1, 2);
% 从左往右找
for i=1:columns
    if ppv1(1,i) ~= 0
        pl.cola = i;
        break;
    end
end
 % 从右往左找
for i=1:columns
    j = columns - i + 1;
    if ppv1(1,j) ~= 0
        pl.colb = j;
        break;
    end
end
out = I(:,pl.cola:pl.colb);