import matplotlib.pylab as plt
from sklearn import linear_model

reg = linear_model.LinearRegression()
X = [[1930], [1940], [1950], [1965], [1972], [1982], [1992], [2010], [2016]]		
y = [59, 62, 70, 69, 71, 74, 75, 76, 78]	
reg.fit(X,y)
print(reg.predict([[1900]]))

# 학습 데이터와 t 값을 산포도로 그린다.
plt.scatter(X,y, color='black')

# 학습 데이터를 입력으로 하여 예측값을 계산한다.
y_pred = reg.predict(X)

# 학습 데이터와 예측값으로 선그래프로 그린다. 
# 계산된 기울기와 y 절편을 가지는 직선이 그려진다. 
plt.plot(X, y_pred, color='blue', linewidth=3)		
plt.show()