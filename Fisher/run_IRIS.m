function run_IRIS()
fprintf '开始测试IRIS数据集(Iris-setosa && Iris-versicolor)：'
DATA=import_IRIS('\IRIS\bezdekIris.data');
X=DATA(:,1:end-1);
Y=DATA(:,end);
X(Y~=1 & Y~=2,:)=[];
Y(Y~=1 & Y~=2)=[];
[X,Y,Index]=K_Cross_Validation(X,Y,10);
TP=0;FP=0;FN=0;TN=0;
INDEX=1:10;
for i=1:10
    index=INDEX;
    index(i)=[];
    [w,w0]=Fisher(X(Index(index,:),:),Y(Index(index,:),:));
    %%特别注意 不能(强烈不建议)在这使用reshape!!!
    %[w,w0]=Fisher(SONAR(Index(index,:),:),Y(
    %reshape(Index(index,:)',[9*21,1])));
    Y_=X(Index(i,:),:)*w'-w0;
    Y_(Y_>=0)=1;
    Y_(Y_<0)=2;
    %sum(Y(Index(i,:))==Y_); %%debug
    TP=TP+sum(Y(Index(i,:),:)==1 & Y_==1);
    FP=FP+sum(Y(Index(i,:),:)==2 & Y_==1);
    FN=FN+sum(Y(Index(i,:),:)==1 & Y_==2);
    TN=TN+sum(Y(Index(i,:),:)==2 & Y_==2);
end
accuracy= (TP+TN)/(TP+FN+FP+TN)
precision=TP/(TP+FP)
recall= TP/(TP+FN)
f1=precision*recall/(precision+recall)

end