import numpy as np
import pandas as pd
from sklearn import tree
from sklearn import metrics
from sklearn import preprocessing
from sklearn.ensemble import RandomForestClassifier
from imblearn.over_sampling import RandomOverSampler
from sklearn.cross_validation import train_test_split

le = preprocessing.LabelEncoder()
clf = RandomForestClassifier(bootstrap=True, criterion = "entropy")
ros = RandomOverSampler()

def preprocess(dataset , test_data):
    print("Preprocessing...")
    data = pd.concat([dataset, test_data])
    data["spaceCat"] = data["spaceCat"].factorize()[0]
    attributes = list(data)
    for attr in attributes:
        le.fit(data.loc[:,attr])
        encoded = le.transform(data.loc[:,attr])
        data_len = len(dataset.loc[:,attr])
        dataset.loc[:,attr] = encoded[0:data_len]
        test_data.loc[:,attr] = encoded[data_len:]

def main():
    
    df = pd.read_csv("TraData.csv")
    print("Reading file...")
    dataset = df.drop(["click"] ,axis=1)
    test_data = pd.read_csv("input.csv")

    preprocess(dataset ,test_data)
    train_X ,valid_X ,train_Y ,valid_Y = train_test_split(dataset ,df["click"] ,test_size=0.3 ,random_state=1)
    X_resampled ,Y_resampled = ros.fit_sample(train_X ,train_Y)
    print("Training model...")
    clf.fit(X_resampled ,Y_resampled)
    hypotheses = clf.predict(valid_X)

    print("Accuracy: ")
    print(metrics.accuracy_score(y_true=valid_Y ,y_pred=hypotheses))
    print("F-1 score: ")
    print(metrics.f1_score(y_true=valid_Y ,y_pred=hypotheses ,average='macro'))

    prediction = clf.predict(test_data)
    output = pd.DataFrame({'click':prediction})
    output.to_csv("output.csv")

if(__name__=="__main__"):
    main()
