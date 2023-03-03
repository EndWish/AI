import queue
from typing import Dict

# 2018180009 김시인
print("<2018180009 김시인>")

class State:
    visit = dict()  # State의 방문을 처리할 dict 변수
    createdStateNum = 0
    goalCount = 0
    
    def __init__(self, board, depth):
        self.board = board
        self.depth = depth
        State.createdStateNum += 1
        if State.createdStateNum % 1000 == 0:
            print(State.createdStateNum, "...")
    
    def getKey(self):
        key = str()
        for pos in self.board:
            key += str(pos)
        return key
    
    def expand(self):
        result = []
        
        index = len(self.board)
        
        for pos in range(1, State.goalCount + 1):
            # pos 위치에 놓을 수 있는 지 확인하고 놓을 수 있으면 리스트에 추가한다.
            success = True
            for prevIndex, prevPos in enumerate(self.board):
                if prevPos == 0:
                    continue
                if (prevPos == pos) or (index - prevIndex == abs(pos - prevPos)):   # 같은 행에 있거나 or 대각선상에 있을 경우
                    success = False
                    break
            if success:
                newBoard = list(self.board)
                newBoard.append(pos)
                newState = State(newBoard, self.depth + 1)
                result.append(newState)   # "현재 상태에서 pos행에 퀸을 둔 상태"를 추가한다.
        
        return result
    
    def f(self):
        return self.h() + self.g()
    
    def h(self):
        score = 0
        for i in range(len(self.board) - 1):
            if self.board[i] % 2 == self.board[i + 1] % 2:
                score -=1
        return score
    
    def g(self):
        return self.depth * 0.5
    
    def __lt__(self, other):
        return self.f() < other.f()
    
    def __str__(self):
        result = str()
        result += "정답 : " + str(self.board)
        return result
    
State.goalCount = int(input("값을 입력하세요 : "))

pq = queue.PriorityQueue()
start = State([], 0)   #초기 상태
State.visit[start.getKey()] = start.getKey()  # 방문처리한다.
pq.put(start)   # 우선순위 큐에 삽입

# A* 탐색을 시작한다.
possible = False
while not pq.empty():
    # 평가함수 f가 가장 작은 상태를 뽑는다.
    x = pq.get()    
    
    # 뽑은 상태가 목표에 도달했을 경우 반복문을 끝낸다.
    if len(x.board) == State.goalCount:
        print(x)
        possible = True
        break
    
    # 확장한다.
    for state in x.expand():
        if state.getKey() in State.visit:   # 이미 방문했을 경우 건너뛴다.
            continue
        State.visit[state.getKey()] = state.getKey()  # 방문처리한다.
        pq.put(state)   # 우선순위 큐에 삽입

if not possible:
    print( State.goalCount, "X", State.goalCount, "칸에", State.goalCount,"의 퀸을 서로 잡을 수 없도록 놓는 것은 불가능 합니다.")

print( "총" , State.createdStateNum, "개의 상태가 만들어 졌습니다.")
