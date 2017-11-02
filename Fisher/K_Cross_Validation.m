%% Vast Stars (vast2stars@gmail.com)
%% 
%% 2017-10-28
function [X,Y,Index]=K_Cross_Validation(X,Y,K)
%% K倍交叉验证生成器。先随机增添样本使原数据集至K的整数倍。
%% 返回增添后的X Y。随机生成不重复的下标（K行，N/K列）。
%% 后续使用应该如下代码处理：
% INDEX=1:K;
% for i=1:K
%    index=INDEX;
%    index(i)=[]; 
%    Func(X(Index(index,:),:),Y(Index(index,:),:));
% end
%%
[m,n]=size(X);
if rem(m,K)
    index=randi(m,1,K-rem(m,K));
    X=[X;X(index,:)];
    Y=[Y;Y(index)];
    [m,n]=size(X);
end
Index=randperm(m);
Index=reshape(Index,[K,m/K]);
end