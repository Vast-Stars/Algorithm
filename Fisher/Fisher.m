function [w,w0]=Fisher(X,Y)
%% X m*n Matrix which contains 2 Class 
%% Y m*1 with only 2 value
%%%
%% return Discriminant Function f=X*w-w0;
%% if f>0, we think X ∈ Class 1;
%% if f<0, we think X ∈ Class 2;
y_unique=unique(Y);
Class1=X(Y==y_unique(1),:);
Class2=X(Y==y_unique(2),:);
m1=mean(Class1);
m2=mean(Class2);
n=size(Class1,2);
 %Ñù±¾ÀàÄÚÀëÉ¢¶È¾ØÕóSi
 S1=zeros(n,n);
 S2=zeros(n,n);
for i=1:size(Class1,1)
    tem=(Class1(i,:)-m1);
    if ~isnan(tem)
       S1=S1+tem'*tem;
    end

end

for i=1:size(Class2,1)
    tem=(Class2(i,:)-m2);
     if ~isnan(tem)
          S2=S2+tem'*tem;
    end

end
Sw=S1+S2;%+1e-8;
Sb=(m1-m2)'*(m1-m2);
% w=(m1-m2)/Sw;
% w=inv(Sw)*(m1-m2)';
% w=w';
%a1=size(Class1,1);
%a2=size(Class2,1);

%w0=-1/2*(m1+m2)*inv(Sw)*(m1-m2)'-log(size( Class2,1)/size(Class1,1));
w = (pinv(Sw))*(m1 - m2)';  %%Use pseudo inverse to avoid the problem of irreversible singular matrix
w=w';
mx1 = w*m1';
mx2 = w*m2';
a1=size(Class1,1);
a2=size(Class2,1);
w0 = (mx1*a1 + mx2*a2)/(a1+a2);
%%w0 = (m1*w' +  m2*w')/2;
end