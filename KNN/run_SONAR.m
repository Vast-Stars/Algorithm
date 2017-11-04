function run_SONAR()
fprintf '开始测试SONAR数据集：\n';
X=import2Matrix('SONAR.csv');
Y=[repmat([1],97,1);repmat([2],111,1)];
[X,Y,Index]=K_Cross_Validation(X,Y,10);
INDEX=1:10;
 
for j=1:20
    Right=0;
    for i=1:10
        index=INDEX;index(i)=[];
        Y_=KNN(X(Index(index,:),:),Y(Index(index,:),:),X(Index(i,:),:),j);
        Right=Right+sum(Y_==Y(Index(i,:)));
    end
    accuracy(j)=Right/size(Y,1);
end
fprintf('最高准确率：%f 出现在K=%d 时\n',max(accuracy),find(accuracy==max(accuracy)));
figure();
plot([1:j],accuracy,'-');
xlabel('K');
ylabel('Accuracy');
title('Accuracy - K relationship curve');

end