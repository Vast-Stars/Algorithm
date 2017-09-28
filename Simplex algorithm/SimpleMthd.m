%%%%%%%%%%%%%%%%%%%
%%%%Author : Vast  
%%%%  Date : September 24, 2017
%%%%%%%%%%%%%%%%%%%
function [X,Y]=SimpleMthd(C,A,b,N)
%%%
%  min f(X)=CX
%  St AX=b and X>=0
%%%
%  A m*n;
%  C 1*n;
%  b m*1
%  N 1*(n-m)
format rat
clc
[m,n]=size(A);
l=n-m; 
opt=1;step=0;
while opt
    CB=C(N);
    sigma=C-CB*A;%calculate sigma  1*n;
    if sum(sigma>=0)==n;
        fprintf('Find the Optimal X£º');
        X=zeros(1,n);
        X(N)=b
        Y=C*X'
        break;
    end
    if sum( sum(A(:,sigma<0)<0))==m*sum(sigma<0)
        fprintf('No optimal solution£¡');
        break;
    end
    [tem,k]=min(sigma./(sigma<0)); % xk
    theta=b./A(:,k);
    theta(find(A(:,k)<=0))=nan;
    [tem,l]=min(theta);  % xl
    if step==0
        fprintf('Initial table:\n');
    else
        fprintf('%d iterations table:\n',step); 
    end
    fprintf('                                         C:  ');
    disp(C);
    fprintf('       Cb             N              B             ');
    for i=1:n
        fprintf('X%d             ',i);
    end
    fprintf('Theta\n');
    disp([[CB',N',b,A;nan,nan,nan,sigma],[theta;nan]]);
    %%%Generate new table
    A=[A,b];
    tem=1:m;
    tem(l)=[];
    A(l,:)=A(l,:)/A(l,k);
    A(tem,:)=A(tem,:)- A(tem,k)*A(l,:);
    b=A(:,n+1);
    A=A(:,1:n);
    N(l)=k;
    step=step+1;

end

