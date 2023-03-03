from sklearn.neighbors import KNeighborsClassifier
from sklearn import metrics
import numpy as np

X = np.array([  [175, 33],
                [180, 35],
                [160, 27],
                [170, 31]])
Y = np.array(['m','m','f','f'])

# 학습 단계
knn = KNeighborsClassifier(n_neighbors=3)
knn.fit(X, Y)

# 아직 보지 못한 새로운 데이터를 제시해보자. 

y_predict = knn.predict([[165, 28]])

print(y_predict)
