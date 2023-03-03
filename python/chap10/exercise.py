import matplotlib.pylab as plt
from sklearn import linear_model

reg = linear_model.LinearRegression()
X = [[4], [1], [3], [2], [3], [1], [0], [1], [1]]		
y = [0,30,10,15,5,25,35,40,45]	
reg.fit(X,y)
print(reg.predict([[0]]))

# 학습 데이터와 t 값을 산포도로 그린다.
plt.scatter(X,y, color='black')

# 학습 데이터를 입력으로 하여 예측값을 계산한다.
y_pred = reg.predict(X)

# 학습 데이터와 예측값으로 선그래프로 그린다. 
# 계산된 기울기와 y 절편을 가지는 직선이 그려진다. 
plt.plot(X, y_pred, color='blue', linewidth=3)		
plt.show()