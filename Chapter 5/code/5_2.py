# 예제 5-2 ) 입력 데이터의 일부를 무작위 변경하는 파이썬 함수와 50글자의 A를 해당 함수에 넣었을 때 변경된 값의 출력 결과
import random

def mutate(data, n=20):
    tmp = [c for c in data]
    for _ in range(n):
        tmp[random.randint(0, len(tmp) - 1)] = chr(random.randint(0, 255))
    return ''.join(tmp)

print(repr(mutate('A' * 50)))
print(repr(mutate('A' * 50)))
print(repr(mutate('A' * 50)))
print(repr(mutate('A' * 50)))
