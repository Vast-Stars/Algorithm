function run_SONAR()
fprintf '��ʼ����SONAR���ݼ���';
SONAR = import2Matrix('SONAR.csv', 1, 208);
%%����Y  ǰ97����Rock���� Ĭ��Ϊ1
Y=[repmat([1],97,1);repmat([2],111,1)];

[SONAR,Y,Index]=K_Cross_Validation(SONAR,Y,10);

%��1Ϊ����  2Ϊ����
TP=0;FP=0;FN=0;TN=0;
INDEX=1:10;
for i=1:10
    index=INDEX;
    index(i)=[];
    [w,w0]=Fisher(SONAR(Index(index,:),:),Y(Index(index,:),:));
    %%�ر�ע�� ����(ǿ�Ҳ�����)����ʹ��reshape!!!
    %[w,w0]=Fisher(SONAR(Index(index,:),:),Y(
    %reshape(Index(index,:)',[9*21,1])));
   
    Y_=SONAR(Index(i,:),:)*w'-w0;
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