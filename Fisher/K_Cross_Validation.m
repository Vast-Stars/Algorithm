%% Vast Stars (vast2stars@gmail.com)
%% 
%% 2017-10-28
function [X,Y,Index]=K_Cross_Validation(X,Y,K)
%% K��������֤���������������������ʹԭ���ݼ���K����������
%% ����������X Y��������ɲ��ظ����±꣨K�У�N/K�У���
%% ����ʹ��Ӧ�����´��봦��
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