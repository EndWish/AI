import matplotlib.pyplot as plt
import numpy as np
from sklearn.cluster import KMeans

X = np.array([
    [2,3],
    [3,1],
    [4,2],
    [11,5],
    [12,4],
    [12,6],
    [7,5],
    [8,4],
    [8,6]
     ])

plt.scatter(X[:,0],X[:,1])
kmeans = KMeans(n_clusters=2, init=np.array([[3,1],[8,4]])) #직접 최초의 중심점을 (3,1)과 (8,4)로 설정할한다.
#kmeans = KMeans(n_clusters=2)
kmeans.fit(X)

print("클러스터링 중심점들 : \n",kmeans.cluster_centers_)

print("각 점의 소속 중심점의 번호:",kmeans.labels_)

plt.scatter(X[:,0],X[:,1], c=kmeans.labels_, cmap='rainbow')
plt.show()