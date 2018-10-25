#encoding=utf-8
import numpy as np
import pandas as pd

def main():
    from sklearn import tree
    from sklearn.cross_validation import train_test_split
    from sklearn import metrics
    from sklearn import preprocessing
    #load data
    Data=pd.read_csv("TraData.csv",encoding="utf8")
    fullData=Data.drop(['click'],axis=1)
    fullTarget=Data['click']
        #print(fullData.head(5))
    
    #encoder
    label_encoder=preprocessing.LabelEncoder()
    nAttribute=len(fullData.iloc[0,:])
    for i in range(0,nAttribute):
        encoded=label_encoder.fit_transform(fullData.iloc[:,i])
        fullData.iloc[:,i]=encoded
        #print(fullData.head(5))

    #split train&test
    train_data,test_data,train_target,test_target=train_test_split(fullData,fullTarget,test_size=0.2,random_state=1)
    
    elf=tree.DecisionTreeClassifier(criterion="entropy")
    elf.fit(train_data,train_target)
    y_pred=elf.predict(test_data)

    #calculate accuracy
    print(metrics.accuracy_score(y_true=test_target,y_pred=y_pred))
    print(metrics.f1_score(y_true=test_target,y_pred=y_pred,average='macro'))

    #load test csv
    outputTestData=pd.read_csv("input.csv",encoding="utf8")

    #encoder
    label_encoder=preprocessing.LabelEncoder()
    nAttribute=len(outputTestData.iloc[0,:])
    for i in range(0,nAttribute):
        encoded=label_encoder.fit_transform(outputTestData.iloc[:,i])
        outputTestData.iloc[:,i]=encoded

    
    out_pred=elf.predict(outputTestData)
    print(out_pred[0:5])
    outDataFrame=pd.DataFrame({'click':out_pred})
    print(outDataFrame.head(5))
    #outDataFrame.to_csv("output.csv",sep='\t',encoding="utf8")
    """
    from sklearn.datasets import load_iris
    iris=load_iris()
    #print(iris)
    from sklearn.cross_validation import train_test_split
    train_data,test_data,train_target,test_target=train_test_split(iris.data,iris.target,test_size=0.2,random_state=1)

    from sklearn import tree
    elf=tree.DecisionTreeClassifier(criterion="entropy")
    elf.fit(train_data,train_target)
    y_pred=elf.predict(test_data)

    from sklearn import metrics
    print(metrics.accuracy_score(y_true=test_target,y_pred=y_pred))

    with open("./data/tree.dot","w") as fw:
        tree.export_graphviz(elf,out_file=fw)
    """
if(__name__=="__main__"):
    main()